#ifndef PUDELKO_H
#define PUDELKO_H
#include <string>

class Pudelko
{
public:
    Pudelko();
    Pudelko(int w, int d, int h);
    std::string toString();

//private:
    int x;
    int y;
    int z;
    int w; //szerokosc
    int d; //glebokosc
    int h; //wysokosc
};

#endif // PUDELKO_H
