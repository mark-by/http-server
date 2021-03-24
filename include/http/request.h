#ifndef HIGHLOAD_REQUEST_H
#define HIGHLOAD_REQUEST_H

#include <string>
#include <iostream>
#include <unordered_map>

namespace http {
    class Request {
    public:
        explicit Request(const std::string &request);
        std::string method() const;
        std::string path() const;
        std::string url() const;

    private:
        std::string _method;
        std::string _url;
        std::string body;
        std::unordered_multimap<std::string, std::string> headers;
        std::unordered_multimap<std::string, std::string> _data;
        std::unordered_map<std::string, std::string> cookies;

        void parseStartLine(const std::string::const_iterator &begin, const std::string::const_iterator &end);
        std::string urlDecode(const std::string::const_iterator &begin, const std::string::const_iterator &end);
        std::string urlDecode(const std::string &url);

        static void replacePlusToSpace(std::string &str);
    };
}

#endif //HIGHLOAD_REQUEST_H
