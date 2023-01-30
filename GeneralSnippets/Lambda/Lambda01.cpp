// =====================================================================================
// Lambda Methods
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

namespace Lambdas {

    bool compare (int n1, int n2) {
        std::cout << "  .. vergleiche " << n1 << " mit " << n2 << std::endl;
        return n1 > n2;
    }

    // Instanz:  function object //  functor  // Funktor // Aufrufbares Objekt
    class Comparer
    {
    private:
        bool m_flag;

    public:
        Comparer() : m_flag{ true } {}
        Comparer(bool flag) : m_flag{ flag } {}

        // Aufrufoperator
        bool operator() (int n1, int n2) const {
            std::cout << "  .. operator(): vergleiche " << n1 << " mit " << n2 << std::endl;
            
            return (m_flag) ? n1 < n2 : n1 > n2;
        }
    };


    void tueWas(int element) {
        std::cout << "Element: " << element << std::endl;
    }

    void test_000()
    {
        // STL  // vector / längenveränderbares Array

        std::vector<int> numbers;  // STL-Container

        numbers.reserve(80);

        for (int i = 0; i < 100; ++i) {

            numbers.push_back(2 * i);

            // Capacity: wird bei Erreichen der Grenze um den Faktor 1.5 erweitert

            std::cout << "Size: " << numbers.size() << ", Capacity: "
                << numbers.capacity() << std::endl;
        }

        // STL-Algorithmen   // STL-Iterator: Position in einem STL-Container
        std::for_each(
            numbers.begin(),
            numbers.end(),
            tueWas
        );

    }

    void test_00()
    {
        Comparer obj{ false };

        bool result = obj (1, 2);
        
        std::cout << std::boolalpha << result << std::endl;
    }

    void test_01()
    {
        // local class within function possible
        class LocalComparer
        {
        private:
            /* mutable */ bool m_flag;

        public:
            LocalComparer() : m_flag{ true } {}
            LocalComparer(bool flag) : m_flag{ flag } {}

            bool operator() (int n1, int n2) const {

                // m_flag = false;

                std::cout << "  .. local operator(): vergleiche " << n1 << " mit " << n2 << std::endl;
                return (m_flag) ? n1 < n2 : n1 > n2;
            }
        };

        std::vector<int> vec { 5, 9, 1, 3, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        //std::sort(
        //    std::begin(vec),
        //    std::end(vec),
        //    compare
        //);
        //// or
        //std::sort(
        //    std::begin(vec),
        //    std::end(vec), 
        //    Comparer(false)
        //);
        //// or
        //std::sort(std::begin(vec), std::end(vec), Comparer{false});
        //// or
        //std::sort(
        //    std::begin(vec),
        //    std::end(vec),
        //    LocalComparer()
        //);


        // Lambda: Funktion ohne Namen // Instanz einer Klasse mit operator()

        std::sort(
            std::begin(vec),
            std::end(vec),
            [] (int n1, int n2) {
                std::cout << "  Lambda: vergleiche " << n1 << " mit " << n2 << std::endl;
                return n1 < n2; 
            }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    void test_02() {

        std::vector<int> vec{ 50, 90, 10, 30, 70, 80 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            std::begin(vec),
            std::end(vec),
            [] (int n1, int n2) { return n1 < n2; }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    void test_03() {

        // shortest lambda on earth: no parameters, capturing and doing nothing
        auto nothing = [] {};
        nothing();

        // c'tor notation
        auto itsOne ([] { return 1; });
        auto itsTwo ([] { return 2; });
        std::cout << itsOne() << ", " << itsTwo() << std::endl;

        // "copy-c'tor" notation
        auto itsFour = [] { return 4; };
        auto itsFive = [] { return 5; };
        std::cout << itsFour() << ", " << itsFive() << std::endl;
    }

    void test_04() {

       // int (*fp) (int, int, int);

        // int  (int, int, int);

        // defining a lambda without 'auto'
        std::function< int(int, int, int) > threeArgs([](int x, int y, int z) {
            return x + y + z; 
            }
        );

        std::cout << threeArgs (5, 6, 7) << std::endl;
    }

    void test_05() {

        // defining new variables in the lambda capture:
        // we can declare a new variable that is only visible
        // in the scope of the lambda: We do so by defining a variable
        // in the lambda-capture without specifying its type:

        // lambda with instance variable definition

        // mutable: removes const-ness of operator()

        auto lambda = [variable = 10] () mutable {    // Type Deduction
            
            variable ++;
            
            return variable; 
        };

        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;
        return;








        // Captures default to 'const value':
        // The mutable keyword removes the 'const' qualification from all captured variables
        auto counter = [count = 50] () mutable { 
            ++count; 
            return count;
        };

        for (size_t i{}; i < 5; ++i) {
            std::cout << counter() << " ";
        }
        std::cout << std::endl;
    }

    void test_06() {

        int n = 1;   // lokale Variable
        int m = 2;   // Closure (JavaScript)

        auto l1 = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        auto l3 = [&, m] {
            std::cout << "Both:      " << n << " " << m << std::endl;
        };

        auto l4 = [=, &m] {
            std::cout << "More both: " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();
        l2();
        l3();
        l4();
    }

    auto test_07_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    auto test_07_helper_b() {

        int n = 1;
        int m = 2;   // Closure: Stack (JavaScript:  Heap)

        auto lambda = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;                                                                                  // I would't do this never ever :-)
    }

    void test_07() {

        auto outerLambda1 = test_07_helper_a();
        auto outerLambda2 = test_07_helper_b();
        outerLambda1();
        outerLambda2();
    }

    void test_08() {

        // demonstrating 'noexcept'
        auto itsOne([] () noexcept { return 1; });
        auto itsTwo = [] () noexcept { return 2; };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    void test_09() {
        // IIFE -Immediately Invoked Functional Expression:
        // Inline-definition and direct invocation of lambda funtion:
        
        std::cout << [] (int l, int r) { return l + r; } (11, 12) << std::endl;

        // Use case for IIFE:
        // This kind of expression might be useful when you have
        // a complex initialization of a const  object:

        auto constexpr ConstValue = [] () {
            /* several lines of code ... - "very complex" computation */
            return 123;
        } ();

        std::cout << "Const Value: " << ConstValue << std::endl;
    }
}

void main_lambdas()
{
    using namespace Lambdas; 
    //test_000();
    //test_00();
    //test_01();
    //test_02();
    //test_03();
    //test_04();
    //test_05();
    //test_06();
    test_07();
    //test_08();
    //test_09();
}

// =====================================================================================
// End-of-File
// =====================================================================================
