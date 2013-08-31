#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>
#include <cmath>
#include <iostream>


using namespace boost::phoenix;


// define arguments a, b and c
expression::argument<1>::type a;
expression::argument<2>::type b;
expression::argument<3>::type c;


// square_root (helper for sq)
struct square_root {
    template<typename Arg> struct result { typedef double type; };    
    template<typename Arg> typename result<Arg>::type operator()(Arg n) { return std::sqrt(static_cast<typename result<Arg>::type>(n)); }
};
boost::phoenix::function<square_root> sq;


// define the discriminant, x1 and x2
auto D = (b*b) - (4*a*c);
auto x1 = (-b + sq(D)) / (2 * a);
auto x2 = (-b - sq(D)) / (2 * a);


void solve(double a, double b, double c)
{
    std::cout << "a = " << a << ", b = " << b << " and c = " << c << std::endl;
    std::cout << "-> x1 = " << x1(a, b, c) << std::endl;
    std::cout << "-> x2 = " << x2(a, b, c) << std::endl;
}


int main()
{
    solve(1, 2, -15);
}