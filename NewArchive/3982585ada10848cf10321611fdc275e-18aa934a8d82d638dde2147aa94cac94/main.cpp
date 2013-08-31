#include <boost/optional.hpp>

class myint {
public:
    int m_a;
    myint (int r_a) : m_a(r_a) {}
};

struct myclass {
    boost::optional<myint> content;
    myclass(boost::none_t arg) :content(arg){}
    myclass (int arg) : content(arg) {}
};

int main() {
     myclass a(0);
     if (a.content) std::cout << "exists";
     else std::cout << "noexists :(";
}