#include <iostream>

#include "config/config.h"
#include "handler/staticHandler.h"
#include "server/server.h"

int main() {
    auto config = Config("config.json");
    auto handler = StaticHandler(config.rootDirectory);
    auto server = Server(config);

    server.start(handler);

    return 0;
}
