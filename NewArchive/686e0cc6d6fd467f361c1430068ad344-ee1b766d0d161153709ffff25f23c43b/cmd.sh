run() { g++ -o test -std=c++11 -DTHROW_SPEC="$1" -O2 main.cpp ; ./test ; } ; run '/**/' ; run 'throw()' ; run 'noexcept'