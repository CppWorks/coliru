#include <type_traits>

struct foo {
    int x : 1;
    int y : 2;
};

static_assert(std::is_same<decltype(foo().x), int>::value, "");

int main() {}