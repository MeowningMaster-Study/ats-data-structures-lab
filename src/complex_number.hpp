#ifndef _ComplexNumber_
#define _ComplexNumber_

#include <iostream>

struct ComplexNumber
{
    double real;
    double imaginary;

    bool operator>(const ComplexNumber c)
    {
        return real == c.real ? (imaginary > c.imaginary) : (real > c.real);
    }

    bool operator<(const ComplexNumber c)
    {
        return real == c.real ? (imaginary < c.imaginary) : (real < c.real);
    }
};

ostream &operator<<(ostream &out, const ComplexNumber &c)
{
    out << c.real;
    out << (c.imaginary < 0 ? "-" : "+") << "i" << abs(c.imaginary) << endl;
    return out;
}

#endif