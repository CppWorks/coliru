#include <iostream>

class scoped_redirect
{
public:
    scoped_redirect(std::ostream & orig, std::ostream & red) :
        orig_(orig),
        old_(orig.rdbuf(red.rdbuf()))
    { }

    ~scoped_redirect()
    {
        orig_.rdbuf(old_);
    }    

private:
    scoped_redirect(const scoped_redirect&) = delete;
    scoped_redirect& operator=(const scoped_redirect&) = delete;

    std::ostream & orig_;
    std::streambuf * old_;
};

int main()
{
    scoped_redirect redirect1(std::cout, std::cerr);
    scoped_redirect redirect2(std::cerr, std::cout);
    std::cout << "hello";
}