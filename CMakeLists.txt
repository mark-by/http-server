cmake_minimum_required(VERSION 3.16)
project(highload)

set(CMAKE_CXX_STANDARD 20)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include_directories(include)

add_executable(highload
        src/main.cpp
        include/http/request.h
        include/http/response.h
        include/config/config.h
        src/config/config.cpp
        include/server/client.h
        src/server/client.cpp
        include/http/http.h
        src/http/request.cpp
        src/http/response.cpp
        include/http/regex.h
        include/handler/handler.h
        include/handler/staticHandler.h
        src/handler/staticHandler.cpp
        include/server/server.h
        src/server/server.cpp)

target_link_libraries(highload curl)