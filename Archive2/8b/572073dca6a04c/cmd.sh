set -x;
clang++ -std=c++11 -pedantic -Wall -Wextra -stdlib=libc++ main.cpp -lsupc++ && ./a.out