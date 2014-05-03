#ifndef KONTENER_H
#define KONTENER_H
#include <vector>
#include <iostream>
#include "pudelko.h"

class Kontener
{
public:
    Kontener();
    void dodajPudelko(const Pudelko);
    void wyswietlPudelka();

private:
    std::vector<Pudelko> Pudelka;
    int bokPodstawy;
};

#endif // KONTENER_H
