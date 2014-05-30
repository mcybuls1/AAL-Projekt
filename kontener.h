#ifndef KONTENER_H
#define KONTENER_H
#include <vector>
#include <iostream>
#include <fstream>
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
    int ustawBokPodstawy(int bok);
    int ustalPozycje(Pudelko i, Pudelko j);
    double nextFitDecreasingHeight(int czyKrokowo);
    double trywialnyAlgorytm();
    double objetoscPudelek();
    void zapiszDoPliku(std::vector<Pudelko> doPliku);
    double drzewoPrzeszukiwan();
    std::vector<Pudelko> dajRezultatNFDH();
    std::vector<Pudelko> dajRezultatDrzewa();

private:
    void rekurencja(int nrDoZapakowania, std::vector<Pudelko> doZapakowania, std::vector<Pudelko> zapakowane);

    std::vector<Pudelko> PudelkadDoZapakowania;
    std::vector<Pudelko> rezultatNFDH;
    std::vector<Pudelko> rezultatTrywialnego;
    std::pair<std::vector<Pudelko>,double> rezultatDrzewa;
    int bokPodstawy;
};

#endif // KONTENER_H
