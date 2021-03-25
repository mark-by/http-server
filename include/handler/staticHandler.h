#ifndef HIGHLOAD_STATICHANDLER_H
#define HIGHLOAD_STATICHANDLER_H

#include <utility>

#include "handler/handler.h"
#include <filesystem>

class StaticHandler: public IHandler {
public:
    StaticHandler(std::string rootDir, std::string defaultFile):_rootDir(std::move(rootDir)),
                                                                _defaultFile(std::move(defaultFile)) {}
    http::Response handle(const http::Request &request) const final;

private:
    std::string contentType(const std::string& extension) const;

    std::filesystem::path _rootDir;
    std::string _defaultFile;
};

#endif //HIGHLOAD_STATICHANDLER_H
