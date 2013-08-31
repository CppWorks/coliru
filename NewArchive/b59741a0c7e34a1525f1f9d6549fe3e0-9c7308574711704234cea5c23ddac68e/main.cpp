#include <iostream>

[[noreturn]] void f() 
{
    throw "error";
}

[[noreturn]] void g()
{
    f();
    std::cout << "unreachable\n"; 
}

int main()
{
    try {
        g();
    } catch(...) {
        std::cout << "and we're back\n";    
    }
}
