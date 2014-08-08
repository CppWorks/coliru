#include <stdint.h>


typedef uint32_t sum_t;
typedef uint8_t byte_t;


sum_t by_val(byte_t* b, byte_t* e)
{
    uint32_t sum = 0;
    for (byte_t* i = b; i != e; ++i)
    {
        sum += *i;
    }
    return sum;
}


void by_ref(byte_t* b, byte_t* e, sum_t& sum)
{
    auto tmp = sum;
    for (byte_t* i = b; i != e; ++i)
    {
        tmp += *i;
    }
    sum = tmp;
}