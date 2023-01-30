// =====================================================================================
// Explicit.cpp // Keyword 'explicit'
// =====================================================================================

#include <iostream>

namespace KeywordExplicit {

    class Complex {
    private:
        double m_real;
        double m_imag;

    public:
        // c'tors
        Complex() : Complex {0.0, 0.0}{}

        /* explicit */ Complex(double real) :   // remove or add keyword 'explicit'
            m_real{ real }, m_imag{} {}

        explicit Complex(double real, double imag) :
            m_real{ real }, m_imag{ imag } {}

        // comparison operator
        bool operator == (Complex rhs)
        {
            return (m_real == rhs.m_real && m_imag == rhs.m_imag);
        }
    };
}

void main_keyword_explicit()
{
    using namespace KeywordExplicit;

    // a Complex object
    Complex c{ 3.0, 0.0 };

    if (c == 3.0) {
        std::cout << "Same objects";
    }
    else {
        std::cout << "Not same objects";
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
