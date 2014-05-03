#include "kontener.h"

Kontener::Kontener()
{

}

void Kontener::dodajPudelko(const Pudelko pudelko)
{
    Pudelka.push_back(pudelko);
}

void Kontener::wyswietlPudelka()
{
    for (unsigned int i = 0; i < Pudelka.size(); ++i) {
       std::cout << Pudelka.at(i).getA() << " " << Pudelka.at(i).getB() << " " << Pudelka.at(i).getC() << std::endl;
    }
}
