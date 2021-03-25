#ifndef HIGHLOAD_RESPONSE_CPP
#define HIGHLOAD_RESPONSE_CPP

#include <unordered_map>
#include <vector>
#include <http/datetime.h>
#include "http/http.h"

#define HTTP_VERSION "HTTP/1.1"

namespace http {
    class Response {
    public:
        explicit Response(const int &status = status::OK);
        explicit Response(const std::string& data, const std::string& contentType, const int &status = status::OK);
        explicit Response(int fileDescriptor, size_t size, const std::string& contentType, int status = status::OK);
        Response& operator=(Response&& other) noexcept ;
        Response(const Response& other);
        ~Response();

        std::string str() const;
        void setHeader(const std::string &key, const std::string &value);
        void setStatus(const int &status);
        size_t contentLength() {return _contentLength;}

        int descriptor() const {return _fileDescriptor;}
    private:
        void setDate();
        std::string statusToStr() const;
        void startLineToStream(std::stringstream & ss) const;
        void headersToStream(std::stringstream & ss) const;

        DateTimeConverter ptimeConverter;
        std::unordered_multimap<std::string, std::string> headers;
        std::string body;
        int _fileDescriptor;
        int statusCode;
        size_t _contentLength;
    };
}

#endif //HIGHLOAD_RESPONSE_CPP
