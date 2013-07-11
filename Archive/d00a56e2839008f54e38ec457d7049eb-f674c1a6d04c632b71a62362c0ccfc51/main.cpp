#include <iostream>
#include <stdint.h>


typedef int64_t int63_t;


int63_t f(int63_t n)
{   
    return n & 0x1000000000000000 ? n | 0x1000000000000000 : -(n & ~0x1000000000000000);
}


int main()
{
    std::cout << f(f(42)) << std::endl;
}