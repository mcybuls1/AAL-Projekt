#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include "pudelko.h"
#include "kontener.h"

using namespace std;
enum ZrodloDanych {PLIK = 1, GENEROWANIE = 2};
enum CzyKrokowo {NIE_KROKOWO, KROKOWO};

vector<Pudelko> generuj(int ilosc, int maxBok)
{
    srand(time(NULL));
    vector<Pudelko> pudelka;
    for (int i = 0; i < ilosc; ++i) {
        pudelka.push_back(Pudelko(rand() % maxBok + 1, rand() % maxBok + 1, rand() % maxBok + 1));
    }
    return pudelka;
}

int main()
{
    int czyKrokowo;
    int skadCzytamyDane;
    int bok;
    string nazwaPliku;
    cout << "W jaki sposób załadować dane?" << endl;
    cout << "1 - z pliku; 2 - wygenerowac" << endl;
    cin >> skadCzytamyDane;

    Kontener kontener;
    if( skadCzytamyDane == PLIK ) {
        cout << "Podaj nazwę pliku z którego wczytać dane" << endl;
        cin >> nazwaPliku;
        ifstream plikZDanymi;
        plikZDanymi.open(nazwaPliku.c_str());
        if( plikZDanymi.good() ){
            cout << "Pomyslnie wczytano plik!" << endl;
        }

        //Wczytywanie danych pudelek do kontenera

        while( true ) {
            int a, b, c;
            plikZDanymi >> a >> b >> c;
            if( plikZDanymi.good() ){
                kontener.dodajPudelko(Pudelko(a, b, c));
            } else {
                break;
            }
        }

        kontener.wyswietlPudelka();
        cout << "Proszę podać długość boku podstawy (większą lub" <<  endl << "równą najdłuższemu bokowi zadanych pudełek)" << endl;
        cin >> bok;
        while(kontener.ustawBokPodstawy(bok) == 0)
        {
            cin >> bok;
        }
    }
    else
    {
        int ile, dlBoku;
        cout << "Prosze podać dane w formacie: [ile pudelek wygenerowac] [maksymalna dlugosc boku]" << endl;
        cin >> ile >> dlBoku;
        kontener.ustawPudelkaDoZapakowania(generuj(ile, dlBoku));
        kontener.wyswietlPudelka();
        cout << "Czy wykonać krokowo?" << endl << "0 - nie; 1 - tak" << endl;
        cin >> czyKrokowo;
        cout << "Proszę podać długość boku podstawy (większą lub" <<  endl << "równą najdłuższemu bokowi zadanych pudełek)" << endl;
        cin >> bok;
        while(kontener.ustawBokPodstawy(bok) == 0)
        {
            cin >> bok;
        }
    }
    clock_t czasStart = clock();

//    cout << "Wysokosc wg prostego: " << kontener.trywialnyAlgorytm() << endl;
    cout << "Wysokosc wg drzewa przeszukiwań: " << kontener.drzewoPrzeszukiwan() << endl;
    kontener.zapiszDoPliku(kontener.dajRezultatDrzewa());
    float czasWykonania = ((float)clock() - czasStart)/CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << czasWykonania << " sec"<< endl << endl;

    getchar();
    getchar();
    czasStart = clock();

    cout << "Wysokosc wg FFDH: " << kontener.nextFitDecreasingHeight(czyKrokowo) << endl;
    kontener.zapiszDoPliku(kontener.dajRezultatNFDH());
    czasWykonania = ((float)clock() - czasStart)/CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << czasWykonania << " sec"<< endl;
    return 0;
}

