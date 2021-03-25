#include "config/config.h"

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>

std::string defaultValue(std::string value, std::string defaultValue) {
    if (value == "") {
        return defaultValue;
    }
    return value;
}

Config::Config(const std::string& filename) {
    std::unordered_map<std::string, std::string> config;

    std::ifstream fin(filename);

    std::string line;
    std::stringstream ss;
    while (!fin.eof()) {
        getline(fin, line);
        line = line.substr(0, line.find('#'));
        ss << line;
        std::string key, value;
        ss >> key >> value;
        config[key] = value;
    }

    cpu = std::stoi(defaultValue(config["cpu_limit"], "4"));
    port = std::stoi(defaultValue(config["port"], "80"));
    limit = std::stoi(defaultValue(config["queue_limit"], "50"));
    bufferSize = std::stoi(defaultValue(config["buffer"], "8000"));
    rootDirectory = defaultValue(config["document_root"], "");
    defaultFile = defaultValue(config["default_file"], "index.html");
}
