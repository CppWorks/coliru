set -x
clang++ -S -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && cat main.s