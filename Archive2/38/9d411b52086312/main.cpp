#include <iostream>

struct selfie_taker {
    void* operator()() const {
        return this; // haha, clearly not stateless
    }
};

static_assert(std::is_empty<selfie_taker>::value, "it is however, empty");

int main() {}