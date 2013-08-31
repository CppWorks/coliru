#include <iostream>

template<class type>
struct track {
    struct node {       
        void foo() {std::cout << "A";}
    };
    struct payload : public node {     
        void bar() {this->foo();} //no error   
        //void bar2() {foo();}      //error
    };
};

template<>
void track<int>::node::foo() {std::cout << "B";}

int main() {track<int>::payload a; a.foo();}