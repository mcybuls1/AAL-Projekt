#ifndef PUDELKO_H
#define PUDELKO_H
#include <string>
#include <vector>

class Pudelko
{
public:
    Pudelko();
    Pudelko(int w, int d, int h);
    std::vector<Pudelko> rotacje();

    int x; //x + w
    int z; //z + d
    int y; //y + h
    int w; //szerokosc
    int d; //glebokosc
    int h; //wysokosc
};

#endif // PUDELKO_H
