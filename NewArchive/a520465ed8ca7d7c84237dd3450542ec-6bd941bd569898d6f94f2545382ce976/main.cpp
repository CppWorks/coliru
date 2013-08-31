#include <type_traits>

template <typename T>
struct ClassName
{
  void some_method()
  {
      static_assert(std::is_floating_point<T>(), "this one only for floats");
  }
};

int main()
{
  ClassName<double> d;
  ClassName<int> i;
  i.some_method();
}