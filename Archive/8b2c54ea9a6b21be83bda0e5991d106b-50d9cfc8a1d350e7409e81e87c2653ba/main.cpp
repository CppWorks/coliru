#include <cstdlib>
#include <iostream>

//emulate MSVC's rand()
//this returns nonrandom results in the same
//range and distribution as MSVC's rand()
//as long as it's called a multiple of 32767 times;
int mrand() {
    static unsigned last=0;
    if (++last==32767)
        last = 0;
    return last;
}
#undef RAND_MAX
#define RAND_MAX 32767

int main() {
    const unsigned max = 1000;
    unsigned dist[max] = {};
    srand(time(NULL));
    for(unsigned i=0; i<32767*100; ++i) {
        //int output = mrand()%max;
        int output = ((double)mrand()/(double)RAND_MAX)*max;
        dist[output] ++;
    }
    unsigned problem=RAND_MAX%max;
    unsigned low=0;
    for(unsigned i=0; i<problem; ++i)
        low += dist[i];
    unsigned high=0;
    for(unsigned i=problem; i<max; ++i)
        high += dist[i];
    std::cout << "numbers 0 through " << problem << " average ";
    std::cout << double(low/problem) << '\n';
    std::cout << "numbers " << problem << " through " << max << " average ";
    std::cout << double(high/(max-problem)) << '\n';
}
