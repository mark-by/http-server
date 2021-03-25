#include "server/client.h"

#include <string>
#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "http/http.h"
#include "http/request.h"

Client::Client(int socket, int buffSize = 8000) : _socket(socket), _buffSize(buffSize) {
    _buffer = new char[buffSize];
}

Client::~Client() {
    delete [] _buffer;
    if (_socket > 0) {
        close(_socket);
    }
}

void Client::serve(const IHandler& handler) {
    auto request = read();
    auto response = handler.handle(request);
    write(response);
}

http::Request Client::read() {
    std::string result;
    size_t read = 0;
    while (read < _buffSize) {
       auto received = recv(_socket, _buffer + read, _buffSize - read, 0);
       if (received <= 0) {
           throw std::runtime_error("read fail: " + std::string(std::strerror(errno)));
       }

       read += received;
       result.append(_buffer, received);
       if (result.find("\r\n\r\n") != std::string::npos) {
           break;
       }
    }

    return http::Request(result);
}

void Client::write(const http::Response& response) {
    std::string data = response.str();
    size_t left = data.size();
    ssize_t sent = 0;

    while (left > 0) {
        sent = send(_socket, data.c_str() + sent, data.size() - sent, 0);
        if (sent == -1) {
            throw std::runtime_error("write fail: " + std::string(std::strerror(errno)));
        }
        left -= sent;
    }

    if (response.descriptor() > 0) {
        off_t len = 0;
        sendfile(response.descriptor(), _socket, 0, &len, nullptr, 0);
    }
}