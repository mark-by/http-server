#include "http/response.h"

#include <boost/date_time/posix_time/posix_time.hpp>

void http::Response::setDate() {
    auto now = boost::posix_time::second_clock::universal_time();
    setHeader("Date", ptimeConverter.convert(now));
}

http::Response::Response(const int &status) : statusCode(status) {
    setDate();
    setHeader("Server", "mark-by");
}

http::Response::~Response() {
    if (_fileDescriptor > 0) {
        close(_fileDescriptor);
    }
}


void http::Response::startLineToStream(std::stringstream & ss) const {
    ss << HTTP_VERSION << " " << statusCode << " " << statusToStr() << "\r\n";
}

std::string http::Response::str() const {
    std::stringstream response;
    startLineToStream(response);
    headersToStream(response);
    response << "\r\n";
    response << body;
    return response.str();
}

http::Response::Response(const std::string &data, const std::string &contentType, const int &status) : statusCode(status) {
    setDate();
    setHeader("Content-Type", contentType);
    setHeader("Server", "mark-by");
    body = data;
    _fileDescriptor = -1;
    setHeader("Content-Length", std::to_string(body.size()));
}

http::Response::Response(int fileDescriptor, size_t size, const std::string &contentType, int status) : statusCode(status) {
    setDate();
    setHeader("Content-Type", contentType);
    setHeader("Server", "mark-by");
    _fileDescriptor = fileDescriptor;
    setHeader("Content-Length", std::to_string(size));
}

void http::Response::headersToStream(std::stringstream & ss) const {
    for (auto &pair : headers) {
        ss << pair.first << ": " << pair.second << "\r\n";
    }
}

void http::Response::setHeader(const std::string &key, const std::string &value) {
    headers.insert({boost::to_lower_copy(key), value});
}

std::string http::Response::statusToStr() const {
    switch(statusCode) {
        case (100): return "Continue";
        case (101): return "Switching Protocol";
        case (102): return "Processing";
        case (103): return "Early Hints";
        case (200): return "OK";
        case (201): return "Created";
        case (202): return "Accepted";
        case (204): return "No Content";
        case (300): return "Multiple Choice";
        case (301): return "Moved Permanently ";
        case (302): return "Found";
        case (304): return "Not Modified";
        case (400): return "Bad Request";
        case (401): return "Unauthorized ";
        case (403): return "Forbidden";
        case (404): return "NotFound";
        case (405): return "Method Not Allowed";
        case (408): return "Request Timeout";
        case (500): return "Internal Server Error";
        case (501): return "Not Implemented";
        case (502): return "Bad Gateway";
        default: return "undefined";
    }
}

http::Response &http::Response::operator=(Response &&other) noexcept {
    headers = other.headers;
    body = other.body;
    statusCode = other.statusCode;
    return *this;
}

void http::Response::setStatus(const int &status) {
    statusCode = status;
}

http::Response::Response(const Response &other) {
    headers = other.headers;
    body = other.body;
    statusCode = other.statusCode;
}
