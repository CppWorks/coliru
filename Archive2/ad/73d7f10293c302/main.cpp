#define BOOST_RESULT_OF_USE_DECLTYPE // needed for gcc 4.7, not clang++
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <functional>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

// okay, so you want position reporting (actually unrelated):
#include <boost/spirit/include/support_line_pos_iterator.hpp>
using It = boost::spirit::line_pos_iterator<std::string::const_iterator>;

// AST type that represents a Number 'token' (with source and location
// information)
struct Number 
{ 
    double      value;
    size_t      line_pos;
    std::string source;

    explicit Number(double value = 0.0, boost::iterator_range<It> const& range = {})
        : 
          value(value),
          line_pos(get_line(range.begin())),
          source(range.begin(), range.end())
    {}

    bool operator< (const Number& other) const { return (other.value - value) > 0.0001; }
};

// the exposed attribute for the parser:
using Words    = std::set<Number>;

// the callback signature for our warning; you could make it more like
// `on_error` so it takes the iterators directly, but again, I'm doing the
// simple thing for the dmeo
using Callback = std::function<bool(std::string const& source, size_t line)>;

template <typename It>
    struct parser : qi::grammar<It, Words()>
{
    parser(Callback warning) 
        : parser::base_type(start),
          warning(warning)
    {
        using namespace qi;
        auto check_unique = phx::end(_val) == phx::find(_val, _1);

    word   = 
               raw [ double_ [ _a = _1 ] ] [ _val = phx::construct<Number>(_a, _1) ]
               ;

        start %= 
               - word        [ _pass = check_unique || phx::bind(warning, 
					phx::bind(&Number::source,   _1),
					phx::bind(&Number::line_pos, _1)) ]
               % +space
               >> eoi
               ;
    }

  private:
    Callback warning;
    qi::rule<It, Number(), qi::locals<double> > word;
    qi::rule<It, Words()> start;
};

int main(int argc, const char *argv[])
{
    // parse command line arguments
    const auto flags          = std::set<std::string> { argv+1, argv+argc };
    const bool fatal_warnings = end(flags) != flags.find("-Werror");

    // test input
    const std::string input("2.4 2.7 \n\n\n-inf \n\nNaN 88 -2.40001 \n3.14 240001e-5\n\ninf");

    // warning handler
    auto warning_handler = [&](std::string const& source, size_t line) { 
        std::cerr << (fatal_warnings?"Error":"Warning") 
                  << ": Near-identical entry '" << source << "' at L:" << line << "\n"; 
        return !fatal_warnings;
    };

    // do the parse
    It f(begin(input)), l(end(input));
    bool ok = qi::parse(f, l, parser<It>(warning_handler));

    // report results
    if (ok)   std::cout << "parse success\n";
    else      std::cerr << "parse failed\n";
    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";

    // exit code
    return ok? 0 : 255;
}

