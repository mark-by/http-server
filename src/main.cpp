#include <iostream>

#include "config/config.h"
#include "handler/staticHandler.h"
#include "server/server.h"

std::string getConfigFile(int argc, char *argv[]) {
    if (argc > 1) {
        return std::string(argv[1]);
    }
    return "/etc/httpd.conf";
}

int main(int argc, char *argv[]) {
    auto config = Config(getConfigFile(argc, argv));
    auto handler = StaticHandler(config.rootDirectory, config.defaultFile);
    auto server = Server(config);

    server.start(handler);
    return 0;
}
