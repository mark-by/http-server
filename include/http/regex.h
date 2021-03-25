#ifndef HIGHLOAD_REGEX_H
#define HIGHLOAD_REGEX_H

namespace http::regex {
    inline std::regex startLine(R"((PUT|GET|POST|HEAD|OPTIONS|PATCH)\s(/[^\n\s\r\t\0]*)\sHTTP/([\d.]+)\r\n)");
}

#endif //HIGHLOAD_REGEX_H
