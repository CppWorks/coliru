#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;
int main() {
    qi::rule<char*,int()> parser = qi::int_;
}
////