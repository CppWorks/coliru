#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

struct tie_it{
    template<class... Ts>
    std::tuple<Ts&...> operator()(Ts&... vs){
        return std::tie(vs...);
    }
};

struct less{
    template<class L, class R>
    bool operator()(L&& lhs, R&& rhs){
        return std::forward<L>(lhs) < std::forward<R>(rhs);
    }
};

struct unwrap_single{
    template<class T>
    T& operator()(std::tuple<T&> t){ return std::get<0>(t); }
    
    template<class Tuple>
    Tuple operator()(Tuple t){ return t; }
};

template<unsigned...> struct seq{};

template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class Comp, class... Accessors>
struct compare_by_ : private Comp{
    compare_by_(Comp c, std::tuple<Accessors...> acc)
      : Comp(c), accessors(acc){}
    
    std::tuple<Accessors...> accessors;
    
    template<class L, class R>
    bool operator()(L&& lhs, R&& rhs){
        auto access = make_access(gen_seq<sizeof...(Accessors)>{});
        Comp& comp = *this;
        return comp(access(std::forward<L>(lhs)), access(std::forward<R>(rhs)));
    }

    template<unsigned... Is>
    auto make_access(seq<Is...>)
      -> decltype(std::bind(unwrap_single{}, std::bind(tie_it{}, std::bind(std::get<Is>(accessors), std::placeholders::_1)...)))
    {
        return std::bind(unwrap_single{}, std::bind(tie_it{}, std::bind(std::get<Is>(accessors), std::placeholders::_1)...));
    }
    
    template<class NC>
    compare_by_<NC, Accessors...> with(NC nc){ return {nc, accessors}; }
};

template<class Comp = less, class... Keys>
compare_by_<Comp, Keys...> compare_by(Keys... ks){ return {{}, std::make_tuple(ks...)}; }

#include <vector>
#include <iostream>
#include <algorithm>

struct identity{
    template<class T>
    T&& operator()(T&& v){
        return std::forward<T>(v);
    }
};

struct user{
  int id;
  std::string name;
};

int const& get_id(user const& u){ return u.id; }
std::string const& get_name(user const& u){ return u.name; }

int main(){
    std::vector<int> v1{ 3, 5, 1, 0, 4, 8, 6, 2, 7, 9};
    std::vector<user> users{ {4, "Bjarne"}, {1, "Herb"}, {3, "Scott"}, {0, "STL"}, {2, "Andrei"} };
    
    std::sort(v1.begin(), v1.end(), compare_by(identity{}));
    for(int i : v1)
        std::cout << i << " ";
 
    std::cout << "\n";
    std::sort(users.begin(), users.end(), compare_by(get_id));
    for(auto& u : users)
        std::cout << "(" << u.id << ", " << u.name << ") ";
        
    std::cout << "\n";
    std::sort(users.begin(), users.end(), compare_by<std::greater<std::string>>(get_name));
    for(auto& u : users)
        std::cout << "(" << u.id << ", " << u.name << ") ";
}