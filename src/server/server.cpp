#include "server/server.h"
#include "server/client.h"
#include "sys/socket.h"
#include <netinet/in.h>
#include <config/config.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cmath>
#include <unistd.h>
#include <cstring>


Server::Server(const Config& config) {
    _bufferSize = config.bufferSize;
    _cpu = config.cpu;

    _socketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socketDescriptor <= 0) {
        throw std::runtime_error("socket fail: " + std::string(std::strerror(errno)));
    }

    int opt = 1;
    if (setsockopt(_socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        close(_socketDescriptor);
        throw std::runtime_error("setsockopt fail: " + std::string(std::strerror(errno)));
    }

    sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(config.port);

    if (bind(_socketDescriptor, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        close(_socketDescriptor);
        throw std::runtime_error("bind fail: " + std::string(std::strerror(errno)));
    }

    listen(_socketDescriptor, config.limit);
}

std::shared_ptr<Client> Server::accept() {
    sockaddr client{};
    socklen_t clientLen = sizeof(client);

    int clientSocketDescriptor = ::accept(_socketDescriptor, (struct sockaddr*)&client, &clientLen);
    if (clientSocketDescriptor == -1) {
        return std::shared_ptr<Client>();
    }

    return std::make_shared<Client>(clientSocketDescriptor, _bufferSize);
}

Server::~Server() {
    if (_socketDescriptor > 0) {
        close(_socketDescriptor);
    }
}

void Server::start(const IHandler& handler) {
    int * shareable_var = static_cast<int *>(mmap(nullptr, sizeof(int),
                                                  PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    *shareable_var = 0;
    int pid;
    int num_of_forks = ceil( log2( _cpu ) );
    for (int i = 0; i < num_of_forks; i++) {
        pid = fork();
        if (pid == 0) {
            if (*shareable_var < _cpu - 1) {
                *shareable_var += 1;
            } else {
                exit(0);
            }
        }
    }

    for(;;) {
        try {
            auto client = accept();
            client->serve(handler);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
