#include <iostream>
#include <memory>

template <typename T>
struct Arf {
    T stuff;

    Arf() : stuff() {
        
    }

    int foo () {
        return (int)stuff;
    }

};

template <typename T>
struct Woof {
    T stuff;

    Woof() : stuff() {
        
    }

    int foo () {
        int woofwoof = (int)stuff;
        return woofwoof + 42;
    }

};

struct Virtualize{
    virtual int foo () = 0;
};

template <typename T>
struct TVirtualize : Virtualize, T
{
    TVirtualize() : T() {}
    TVirtualize(T virtualize) : T(std::move(virtualize)) { }
    
    virtual int foo () override
    {
        T& t = *this;
        return t.foo();
    }
    
};


int main() {
   std::unique_ptr<Virtualize> gotit( new TVirtualize<Woof<int>>( ) );
   std::cout << gotit->foo() << std::endl;
   gotit.reset( new TVirtualize<Arf<float>>() );
   std::cout << gotit->foo() << std::endl;
   
   TVirtualize<Arf<float>> varf;
   Arf<float>& arf = varf; // Get reference to T. OK
   arf.stuff = 444;
   std::cout << arf.foo() << std::endl;
   
   Arf<float> arf2 = varf; // Slicing. Also ok.
   std::cout << arf2.foo() << std::endl;
   
}