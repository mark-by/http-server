#include "config/config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

Config::Config(const std::string& filename) {
    boost::property_tree::ptree root;
    try {
        boost::property_tree::read_json(filename, root);
    } catch (boost::property_tree::json_parser_error& e) {
        std::cout << "[WARN]: Config error: " << e.message() << " => "
        << "Use default values" << std::endl;
    }

    cpu = root.get<int>("cpu", 4);
    port = root.get<int>("port", 8000);
    limit = root.get<int>("limit", 50);
    bufferSize = root.get<int>("bufferSize", 8000);
    rootDirectory = root.get<std::string>("root", "");
    defaultFile = root.get<std::string>("defaultFile", "index.html");
}
