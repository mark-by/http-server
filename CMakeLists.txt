cmake_minimum_required(VERSION 3.17)
project(highload)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O0 -ggdb3 -DASIO_STANDALONE -lboost_system")

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include_directories(
        include
        /opt/homebrew/Cellar/boost/1.75.0_2/include
)

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
        include/http/datetime.h
        src/http/datetime.cpp
        include/http/regex.h
        include/handler/handler.h
        include/handler/staticHandler.h
        src/handler/staticHandler.cpp
        include/server/server.h
        src/server/server.cpp)

target_link_libraries(highload curl)