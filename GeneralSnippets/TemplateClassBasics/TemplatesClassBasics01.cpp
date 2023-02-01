// =====================================================================================
// TemplatesClassBasics01.cpp // Class Templates Basics 01
// =====================================================================================

#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <map>
#include <type_traits>

namespace ClassTemplatesBasics {

    namespace ClassTemplatesBasics_Seminar {

        class Calculator_MitFrage {
        public:
            static int add(int n, int m) { return n + m; }
            static int sub(int n, int m) { return n - m; }
            static int mul(int n, int m) { return n * m; }
            static int div(int n, int m) { return n / m; }

            int foo() { return 0; }
            virtual int bar() { return 0; }
        };


        void test_seminar_01() {

            Calculator_MitFrage calc;
            calc.foo();

            Calculator_MitFrage::add(1, 2);

            // ABER !!!!!!!!!!!!!!

            Calculator_MitFrage* calc2 = new Calculator_MitFrage();
            calc2->bar();
        }

        // OO
        //class Calculator {
        //public:
        //    static int add(int n, int m) { return n + m; }
        //    static int sub(int n, int m) { return n - m; }
        //    static int mul(int n, int m) { return n * m; }
        //    static int div(int n, int m) { return n / m; }
        //};

        // GP
        // Klassenvorlagen / Klassenschablone
        // Primäres Template
        template <typename T>
        class Calculator {
        public:
            static T add(T n, T m) { 
                return n + m;
            }
            static T sub(T n, T m) { return n - m; }
            static T mul(T n, T m) { return n * m; }
            static T div(T n, T m) { return n / m; }
        };

        // Partielle Spezialisierung
        template <>
        class Calculator <int> {
        public:
            static int add(int n, int m) {
                return n + m;
            }
            static int sub(int n, int m) { return n - m; }
            static int mul(int n, int m) { return n * m; }

            static int div(int n, int m) {
                return  (int) ( ( (double) n / m ) + 0.5 ) ;
            }
        };

        class DoubleCalculator {
        public:
            static double add(double n, double m) { return n + m; }
            static double sub(double n, double m) { return n - m; }
            static double mul(double n, double m) { return n * m; }
            static double div(double n, double m) { return n / m; }
        };

        void test_seminar_calc() {

            Calculator<int> calc;

            int result = Calculator<int>::add(1, 2);

            double result2 = Calculator<double>::div(1.7, 2.7);

            result = Calculator<int>::div(3, 4);
        }

        // 2. Beispiel zu Partielle Template Spezialisierung

        // Primäres Template
        template <typename T>   // T = int&
        struct MyReferenceRemove
        {
            using type = T;
        };

        // Partielles Template
        template <typename T>   // T& = int&   ==> T = int
        struct MyReferenceRemove <T&>
        {
            using type = T;
        };

        void test_seminar() {

            // Beispiel:
            std::vector<int> zahlen;
            std::vector<int>::iterator position;

            std::map<int, int> zahlen2;
            std::map<int, int>::iterator position2;

            using T1 = MyReferenceRemove<int>::type;
            using T2 = MyReferenceRemove<int&>::type;

            T1 a;
            T2 b;
        }


    }














    namespace SimpleTemplateCalculator {

        // primary templyte
        template <typename T>
        class Calculator
        {
        public:
            static T add(T x, T y) { return x + y; }
            static T sub(T x, T y) { return x - y; }
            static T mul(T x, T y) { return x * y; }
            static T div(T x, T y) { return x / y; }
        };

        // explicit specialization of whole template class Calculator<T> for T = int
        template <>
        class Calculator<int>
        {
        public:
            static int add(int x, int y) { return x + y; }
            static int sub(int x, int y) { return x - y; }
            static int mul(int x, int y) { return x * y; }
            static int div(int x, int y) { 
                return static_cast<int> (
                    (static_cast<double>(x) / x) + 0.5
                );
            }
        };

        // or explicit specialization of single template class method 'div' for T = int

        //template <>
        //int Calculator<int>::div(int n, int m) {
        //    std::cout << "do rounding:" << std::endl;
        //    return (int)(((double)n / m) + 0.5);
        //}

        // see
        // https://stackoverflow.com/questions/25724360/template-class-with-a-single-method-specialized-in-c
        // or
        // https://stackoverflow.com/questions/1723537/template-specialization-of-a-single-method-from-a-templated-class

        void test_01() {

            // just verifying template concept: is this assignment allowed?
            Calculator<int> calc10;
            Calculator<int> calc11;
            calc10 = calc11;

            // T = double
            Calculator<double> calc;
            [[maybe_unused]] double result = calc.add(1.0, 2.0);

            // T = int
            using MyType = int;
            Calculator<MyType> calc2;
            [[maybe_unused]] MyType result2 = calc2.add(10, 11);
            result2 = calc2.div(4, 10);

            // T = std::complex<double>
            using namespace std::complex_literals;
            Calculator<std::complex<double>> calc3;
            std::complex<double> z1 = 1. + 2i;
            std::complex<double> z2 = 1. - 2i;
            [[maybe_unused]] std::complex<double> result3 = calc3.add(z1, z2);
        }
    }
}

void main_class_templates_basics_01()
{ 
    ClassTemplatesBasics::ClassTemplatesBasics_Seminar::test_seminar();

    //using namespace ClassTemplatesBasics::SimpleTemplateCalculator;
    //test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
