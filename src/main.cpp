#include <iostream>

#include "config/config.h"
#include "handler/staticHandler.h"
#include "server/server.h"

int main() {
    auto config = Config("/etc/httpd.conf");
    auto handler = StaticHandler(config.rootDirectory, config.defaultFile);
    auto server = Server(config);

    server.start(handler);
    return 0;
}
