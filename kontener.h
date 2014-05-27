#ifndef KONTENER_H
#define KONTENER_H
#include <vector>
#include <iostream>
#include <algorithm>
#include "pudelko.h"

enum WzglednaPozycjaPudelek {BLAD, I_NA_LEWO_OD_J, I_PONIZEJ_J, I_Z_TYLU_J};

class Kontener
{
public:
    Kontener();
    void dodajPudelko(const Pudelko);
    void ustawPudelkaDoZapakowania(std::vector<Pudelko> pudelka);
    void wyswietlPudelka();
    int ustawBokPodstawy();
    int ustalPozycje(Pudelko i, Pudelko j);
    int prostyAlgorytm(int czyKrokowo);
    int gilotynowyAlgorytm();
    double objetoscPudelek();

private:
    std::vector<Pudelko> PudelkadDoZapakowania;
    std::vector<Pudelko> PudelkaZapakowane;
    int bokPodstawy;
};

#endif // KONTENER_H
