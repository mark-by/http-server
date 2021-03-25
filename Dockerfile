FROM ubuntu:latest as executor

RUN apt-get update && \
    apt-get -y install --no-install-recommends \
    make \
    g++ \
    curl \
    libcurl4-openssl-dev \
    cmake

WORKDIR /app

COPY . /app

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

WORKDIR /app/build

VOLUME ["/var/www/html"]

ENTRYPOINT [ "/app/build/highload" ]

EXPOSE 80