set -x ; g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -I/usr/local/include -L/usr/local/lib -lboost_system -lboost_filesystem && ./a.out