g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | perl -pe 's, is void _.. .with T = (.*)\], is \1,g'