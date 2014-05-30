#include "pudelko.h"

Pudelko::Pudelko()
{
}

Pudelko::Pudelko(int a, int b, int c)
{
    this->w = a;
    this->d = b;
    this->h = c;

}

std::string Pudelko::toString()
{
    std::string toString;
    toString += w;
    toString.append(" ");
    toString += d;
    toString.append(" ");
    toString += h;
    return toString;
}
