#ifndef HIGHLOAD_HANDLER_H
#define HIGHLOAD_HANDLER_H

#include "http/response.h"
#include "http/request.h"

class IHandler {
public:
    virtual http::Response handle(const http::Request& request) const = 0;
    virtual ~IHandler() = default;
};

#endif //HIGHLOAD_HANDLER_H
