echo clang++ && clang++ -std=c++11 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo g++ && g++-4.9 -std=c++11 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out