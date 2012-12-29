/**
 * The sequence of triangle numbers is generated by adding the natural numbers.
 * So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The
 * first ten terms would be:
 *   1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 * 
 * Let us list the factors of the first seven triangle numbers:
 *   1: 1
 *   3: 1,3
 *   6: 1,2,3,6
 *   10: 1,2,5,10
 *   15: 1,3,5,15
 *   21: 1,3,7,21
 *   28: 1,2,4,7,14,28
 * 
 * We can see that 28 is the first triangle number to have over five divisors.
 * 
 * What is the value of the first triangle number to have over five hundred
 * divisors?
 */
 
 
/**
 * Solution: brute force iteration
 * 
 * Algorithm:
 *  set triangle to 1
 *  loop i from 2 to infinity:
 *      increment triangle with i
 *      if divisor count for triangle > 500 then
 *          print triangle
 *          exit program
 */


#include <iostream>


unsigned divisor_count(unsigned long n)
{
    unsigned result = 0;
    for (unsigned i = 1; i*i <= n; ++i)
    {
        if (n % i == 0)
        {
            result++;
        }
    }
    return result;
}


int main()
{
    auto triangle = 1LU;
    for (auto i = 2LU; i < 10; ++i)
    {
        triangle += i;
        auto c = divisor_count(triangle);
        std::cout << "i: " << i << ", triangle: " << triangle << ", divisor_count: " << divisor_count << std::endl;
        if (c > 500)
        {
            std::cout << triangle << std::endl;
            return 0;
        }
    }
}