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

## Config
```text
cpu_limit 4       # maximum CPU count to use (for non-blocking servers)
document_root /var/www/html
default_file index.html
port 80
queue_limit 50
buffer 8000
```

## Tests
```shell
git clone https://github.com/init/http-test-suite.git
cd http-test-suite

./httptest.py
```

## Benchmark
Benchmarks are done with ApacheBench.

### Environment
OC: Ubuntu 20.04 (in Parallels)  
CPU: М1 Apple Silicon
Without dockers

### Parameters
Httpd processes: 2  
Concurrency level: 100   
Requests: 200000  
Document Length: 954824 bytes  

#### Nginx
```text
Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            8080

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      100
Time taken for tests:   23.888 seconds
Complete requests:      200000
Failed requests:        0
Total transferred:      191014200000 bytes
HTML transferred:       190964800000 bytes
Requests per second:    8372.50 [#/sec] (mean)
Time per request:       11.944 [ms] (mean)
Time per request:       0.119 [ms] (mean, across all concurrent requests)
Transfer rate:          7808918.14 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       6
Processing:     0   12   9.5     12     244
Waiting:        0    0   0.7      0      15
Total:          0   12   9.5     12     244
```

#### Httpd
```text
Server Software:        mark-by
Server Hostname:        localhost
Server Port:            80

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      100
Time taken for tests:   24.553 seconds
Complete requests:      200000
Failed requests:        0
Total transferred:      190993000000 bytes
HTML transferred:       190964800000 bytes
Requests per second:    8145.50 [#/sec] (mean)
Time per request:       12.277 [ms] (mean)
Time per request:       0.123 [ms] (mean, across all concurrent requests)
Transfer rate:          7596350.69 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    4  59.2      0    1032
Processing:     1    9   2.7      7      23
Waiting:        0    0   0.5      0      13
Total:          1   12  59.5      7    1045
```

## Benchmark in dockers  

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
