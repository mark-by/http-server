#ifndef HIGHLOAD_SERVER_H
#define HIGHLOAD_SERVER_H

#include <utility>

#include "handler/handler.h"
#include "config/config.h"
#include "server/client.h"
#include <memory>

class Server {
public:
    Server(const Config& config);
    ~Server();

    void start(const IHandler& handler);
private:
    std::shared_ptr<Client> accept();

    int _socketDescriptor;
    int _bufferSize;
    int _cpu;
};
#endif //HIGHLOAD_SERVER_H
