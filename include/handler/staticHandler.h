#ifndef HIGHLOAD_STATICHANDLER_H
#define HIGHLOAD_STATICHANDLER_H

#include "handler/handler.h"

class StaticHandler: public IHandler {
public:
    StaticHandler(std::string rootDir): rootDir(std::move(rootDir)) {}
    http::Response handle(const http::Request &request) const final;

private:
    std::string rootDir;
};

#endif //HIGHLOAD_STATICHANDLER_H
