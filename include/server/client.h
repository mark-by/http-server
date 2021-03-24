#ifndef HIGHLOAD_CLIENT_H
#define HIGHLOAD_CLIENT_H

#include <string>
#include "http/request.h"
#include "http/response.h"
#include "handler/handler.h"

class Client {
public:
    explicit Client(int socket, int buffSize);
    ~Client();

    void serve(const IHandler& handler);

private:
    http::Request read();
    void write(const http::Response& response);

    int _socket;
    int _buffSize;
    char *_buffer;
};

#endif //HIGHLOAD_CLIENT_H
