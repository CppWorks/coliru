#include <cassert>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <stdlib.h>

namespace { constexpr std::size_t desired_alignment = 32; }

#include <iostream>
void* operator new[](std::size_t size) {
    struct with_dtor { ~with_dtor(); };

    static bool first_run = true;
    static bool detecting = true;
    static std::size_t extra = 0;
    if(first_run) {
        first_run = false;
        new with_dtor[1];
    } else if(detecting) {
        detecting = false;
        extra = size - sizeof(with_dtor);
        assert(extra <= desired_alignment);
        return nullptr; // unused return
    }
    
    void* ptr;
    int r = ::posix_memalign(&ptr, desired_alignment, size); // or just call the over-aligned operator new
    if(r != 0) throw std::bad_alloc();
    return static_cast<char*>(ptr) + (desired_alignment - size);
}

void operator delete[](void* ptr) noexcept {
    //std::align still missing from GCC
    auto u = reinterpret_cast<std::uintptr_t>(ptr);
    void* aligned = reinterpret_cast<void*>(u - (u % desired_alignment));
    assert(aligned);
    ::free(aligned);
}

struct foo { ~foo() {} };

int main() {
    auto p = new foo[10];
    delete[] p;
}
