// =====================================================================================
// Auto.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

namespace Auto_Examples {

    std::map<int, std::string> getFunction() { return {}; };

    void test_01_a() {

        auto n = 123;    // n is type of int

        auto result = getFunction();
        std::map<int, std::string> result2 = getFunction();
    }

    // ---------------------------------------------------------------------

    auto sum(float f1, float f2)
    {
        return f1 + f2;
    }

    auto foo(bool flag, char ch, double d) -> double
    {
        if (flag) {
            return ch;
        }
        else {
            return d;
        }
    }

    void test_01_b() {

        auto result = sum(1.0, 2.0);  // float

        auto value = foo(true, '!', 123.456);   // double
    }

    // ---------------------------------------------------------------------

    class Contact
    {
        std::string m_name;
        size_t m_number;

    public:
        auto getName() const { return m_name; }
        auto getMobileNumber() const { return m_number; }
    };

    // ---------------------------------------------------------------------

    auto make_planet()
    {
        struct Planet { std::string name; int moons; bool rings; };

        return Planet{ "Saturn", 82, true };
    }

    void test_01_c() {

        // using automatic return type deduction
        auto planet = make_planet();

        std::cout
            << planet.name << ' '
            << planet.moons << ' '
            << planet.rings << std::endl;

        // using automatic return type deduction & structured binding
        auto [name, num_moons, has_rings] = make_planet();

        std::cout
            << name << ' '
            << num_moons << ' '
            << has_rings << std::endl;
    }

    // ---------------------------------------------------------------------

    const std::string message{ "This is an important message :)" };

    const std::string& getMessage()
    {
        return message;
    }

    void test_01_d() {

        auto msg = getMessage();
        std::cout << "Message: " << msg << std::endl;

        // but:
        const auto& msg2 = getMessage();
        std::cout << "Message: " << msg2 << std::endl;

        // or:
        decltype(getMessage()) msg3 = getMessage();
        std::cout << "Message: " << msg3 << std::endl;

        // once again 'or':
        decltype(auto) msg4 = getMessage();
        std::cout << "Message: " << msg4 << std::endl;
    }

    // ---------------------------------------------------------------------

    template <typename TReturn, typename T1, typename T2>
    TReturn add1(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    template <typename T1, typename T2, typename TReturn>
    TReturn add2(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    template <typename TReturn = long, typename T1, typename T2>
    TReturn add3(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    void test_01_e()
    {
        // works - specifying all template parameters
        auto result = add1<long, int, int>(10, 20);

        // works too - only the return template parameter type needs to be specified
        auto result1 = add1<long>(10, 20);

        // doesn't work too - return template parameter is at wrong position
        // auto result2 = add2<long>(10, 20);

        // works too - no template parameter type needs to be specified
        auto result3 = add3(10, 20);
    }

    // ---------------------------------------------------------------------

    decltype(auto) getFirstCharacter(const std::string& s)
    {
        return s[0];
    }

    void test_01_f()
    {
        auto ch1 = getFirstCharacter(std::string{ "ABC" });
        decltype(auto) ch2 = getFirstCharacter(std::string{ "ABC" });
    }
}

void main_auto()
{
    using namespace Auto_Examples;
    test_01_a();
    test_01_b();
    test_01_c();
    test_01_d();
    test_01_e();
    test_01_f();
}

// =====================================================================================
// End-of-File
// =====================================================================================
