#include "handler/staticHandler.h"

http::Response StaticHandler::handle(const http::Request &request) const {
    std::cout << request.method() << " " << request.path() << std::endl;
    return http::Response("{\"data\": 132}", "application/json");
}