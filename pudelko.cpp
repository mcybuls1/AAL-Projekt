#include "pudelko.h"

Pudelko::Pudelko()
{
}

Pudelko::Pudelko(int w, int d, int h)
{
    this->w = w;
    this->d = d;
    this->h = h;
    x = 0;
    y = 0;
    z = 0;
}

std::vector<Pudelko> Pudelko::rotacje()
{
    std::vector<Pudelko> pudelka;
    pudelka.push_back(Pudelko(w,d,h));
    pudelka.push_back(Pudelko(d,w,h));
    pudelka.push_back(Pudelko(h,w,d));
    pudelka.push_back(Pudelko(h,d,w));
    pudelka.push_back(Pudelko(d,h,w));
    pudelka.push_back(Pudelko(w,h,d));

    return pudelka;
}
