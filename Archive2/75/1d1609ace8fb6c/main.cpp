#include <memory>
#include <iostream>
 
struct Foo {
     ~Foo() { std::cout << "~Foo...\n"; }
    Foo() { std::cout << "Foo...\n"; }

};

class sample 
{
    public:
     int a;
      sample() {}
     
         ~sample() {}
    protected:
         sample(int a) { a = a; }
       
      
};
 
struct D { 
    void operator()(Foo* p) const {
        std::cout << "Call delete for Foo object...\n";
        delete p;
    }
};
 
int main()
{
    sample objA;
    std::shared_ptr<sample>(new sample(5));
    std::cout << obj->a <<std::endl;
    {
        std::cout << "constructor with no managed object\n";
        std::shared_ptr<Foo> sh1;
    }
 
    {
        std::cout << "constructor with object\n";
        std::shared_ptr<Foo> sh2(new Foo);
        std::shared_ptr<Foo> sh3(sh2);
        std::cout << sh2.use_count() << '\n';
        std::cout << sh3.use_count() << '\n';
    }
 
    {
        std::cout << "constructor with object and deleter\n";
        std::shared_ptr<Foo> sh4(new Foo, D());
    }
}