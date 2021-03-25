# Static Server

## Build
```shell
git clone https://github.com/mark-by/http-server
cd http-server
mkdir build
cd build
cmake ..
make
```

## Docker
```shell
docker build -t httpd https://github.com/mark-by/http-server.git
docker run -p 80:80 -v /etc/httpd.conf:/etc/httpd.conf:ro -v /var/www/html:/var/www/html:ro --name httpd -t httpd
```

## Tests
```shell
git clone https://github.com/init/http-test-suite.git
cd http-test-suite

./httptest.py
```

## Benchmark
Benchmark was completed with ApacheBench. Nginx and httpd was in docker container.  

### Environment
OC: macOS  
CPU: М1 Apple Silicon

### Parameters
Httpd processes: 4  
Concurrency level: 10   
Requests: 2000  
Document Length: 954824 bytes  

#### Nginx
```text
Requests per second:    157.84 [#/sec] (mean)                                                                          │
Time per request:       63.355 [ms] (mean)                                                                             │
Time per request:       6.336 [ms] (mean, across all concurrent requests)                                              │
Transfer rate:          147214.01 [Kbytes/sec] received                                                                │
                                                                                                                       │
Connection Times (ms)                                                                                                  │
              min  mean[+/-sd] median   max                                                                            │
Connect:        0    0   0.0      0       0                                                                            │
Processing:    28   63  12.2     59     121                                                                            │
Waiting:        4    9   3.7      8      42                                                                            │
Total:         29   63  12.2     59     121
```

#### Httpd
```text
Requests per second:    149.79 [#/sec] (mean)
Time per request:       66.761 [ms] (mean)
Time per request:       6.676 [ms] (mean, across all concurrent requests)
Transfer rate:          139687.42 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:    37   67  13.3     62     123
Waiting:        4    9   2.5      8      27
Total:         37   67  13.3     62     123
```

## Author
Bykhovets Mark