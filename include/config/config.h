#ifndef HIGHLOAD_CONFIG_H
#define HIGHLOAD_CONFIG_H

#include <string>

struct Config {
    explicit Config(const std::string& filename);

    int cpu;
    int port;
    int limit;
    int bufferSize;
    std::string rootDirectory;
};

#endif //HIGHLOAD_CONFIG_H
