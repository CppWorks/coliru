#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include <sstream>

const unsigned num_tests = 10000000;

unsigned three_way(const char* one, const char* two, const char* three) {
    unsigned result =0;
    for(int i=0; i<num_tests; ++i) {
        result += strcmp(one, two) < 0;
        result += strcmp(two, three) < 0;
        result += strcmp(three, one) < 0;
        result += strcmp(two, one) < 0;
        result += strcmp(three, two) < 0;
        result += strcmp(one, three) < 0;
    }
    return result;    
}

unsigned two_way(const std::string& one, const std::string& two, const std::string& three) {
    unsigned result =0;
    for(int i=0; i<num_tests; ++i) {
        result += one<two;
        result += two<three;
        result += three<one;
        result += two<one;
        result += three<two;
        result += one<three;
    }
    return result;    
}

int make_three_way(const std::string& one, const std::string& two) {
    if (one<two) return -1;
    if (two<one) return 1;
    return 0;
}

unsigned two_wayish(const std::string& one, const std::string& two, const std::string& three) {
    unsigned result =0;
    for(int i=0; i<num_tests; ++i) {
        result += make_three_way(one,two);
        result += make_three_way(two, three);
        result += make_three_way(three, one);
        result += make_three_way(two, one);
        result += make_three_way(three, two);
        result += make_three_way(one, three);
    }
    return result;    
}

int main() {
    //stringstream to prevent gcc from precalculating string comparisons
    std::stringstream ss;
    std::string one = ss.str();
    ss << "unsigned two_way(const std::string& one, const std::string& two, const std::string& three)";
    std::string two = ss.str();
    ss << ';';
    std::string three = ss.str();
    
    clock_t begin = clock();
    unsigned r = three_way(one.c_str(), two.c_str(), three.c_str());
    clock_t end = clock();
    std::cout << "three_way:\t" << (end-begin) << " ticks\t" << r << '\n';
    
    begin = clock();
    r = two_way(one, two, three);
    end = clock();
    std::cout << "two_way:\t" << (end-begin) << " ticks\t" << r << '\n';
    
    begin = clock();
    r = two_wayish(one, two, three);
    end = clock();
    std::cout << "two_wayish:\t" << (end-begin) << " ticks\t" << r << '\n';
    
}