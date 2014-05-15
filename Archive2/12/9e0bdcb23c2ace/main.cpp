#include <utility>
#include <iostream>

template< typename Signature >
class Delegate;

template< typename Ret, typename Param >
class Delegate< Ret(Param) >
{
public:
   
   Ret operator()(Param&& p_param)
   {
      return m_ifunc(m_obj, std::forward< Param >(p_param));
   }
   
   // only provide a declaration, no definition. Need the extra template arguments becaue the
   // definition can no longer inherit Delegate's template parameters
   template< typename Ret1, typename Param1, typename ObjType, Ret1(ObjType::*Method)(Param1) >
   friend Delegate< Ret1(Param1) > createDelegate(ObjType * const p_obj);
   
private:
   
   void * m_obj = nullptr;
   Ret (*m_ifunc)(void*, Param&&) = nullptr;
   
   template< typename ObjType, Ret(ObjType::*Method)(Param) >
   static Ret ifunction(void * const p_obj, Param&& p_param)
   {
      ObjType * const obj = (ObjType * const) p_obj;
      return (obj->*Method)(std::forward< Param >(p_param));
   }
};

template< typename Ret, typename Param, typename ObjType, Ret(ObjType::*Method)(Param) >
Delegate< Ret(Param) > createDelegate(ObjType * const p_obj)
{
  Delegate< Ret(Param) > del;
  del.m_obj = p_obj;
  del.m_ifunc = &Delegate< Ret(Param) >::template ifunction< ObjType, Method >;
  return del;
}

struct Test
{
   void test(int x)
   {
      std::cout << x << std::endl;
   }
   
};

int main()
{
   Test t;
   
   Delegate< void(int) > d = createDelegate< void, int, Test, &Test::test >(&t);
   
   d(5);
}
