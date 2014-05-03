#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include "pudelko.h"
#include "kontener.h"

using namespace std;
enum ZrodloDanych {PLIK = 1, GENEROWANIE = 2};

int main()
{
    int skadCzytamyDane;
    string nazwaPliku;
    cout << "W jaki sposób załadować dane?" << endl;
    cout << "1 - z pliku; 2 - wygenerowac" << endl;
    cin >> skadCzytamyDane;

    if( skadCzytamyDane == PLIK ) {
        cout << "Podaj nazwę pliku z którego wczytać dane" << endl;
        cin >> nazwaPliku;
        ifstream plikZDanymi;
        plikZDanymi.open(nazwaPliku.c_str());
        if( plikZDanymi.good() ){
            cout << "Pomyslnie wczytano plik!" << endl;
        }

        //Wczytywanie danych pudelek do kontenera
        Kontener kontener;
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

    }
    clock_t czasStart = clock();
    for (int i = 0; i < 300000000; i++);
    float czasWykonania = ((float)clock() - czasStart)/CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << czasWykonania << " sec"<< endl;

    return 0;
}

