#include "kontener.h"
#include "cstdio"

Kontener::Kontener()
{

}

void Kontener::dodajPudelko(const Pudelko pudelko)
{
    PudelkadDoZapakowania.push_back(pudelko);
}

void Kontener::ustawPudelkaDoZapakowania(std::vector<Pudelko> pudelka)
{
    PudelkadDoZapakowania = pudelka;
}

void Kontener::wyswietlPudelka()
{
    for (unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i) {
       std::cout << PudelkadDoZapakowania.at(i).getW() << " " << PudelkadDoZapakowania.at(i).getD() << " " << PudelkadDoZapakowania.at(i).getH() << std::endl;
    }
}

int Kontener::ustawBokPodstawy()
{
    int max = 0;
    for (unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i)
    {
       if(PudelkadDoZapakowania.at(i).getW() > max) {
           max = PudelkadDoZapakowania.at(i).getW();
       }
       if(PudelkadDoZapakowania.at(i).getD() > max) {
           max = PudelkadDoZapakowania.at(i).getD();
       }
       if(PudelkadDoZapakowania.at(i).getH() > max) {
           max = PudelkadDoZapakowania.at(i).getH();
       }
    }
    bokPodstawy = max;
    return max;
}

int Kontener::ustalPozycje(Pudelko i, Pudelko j)
{
    //paczka i jest na lewo, ponad lub z przodu w stosunku do paczki j
    bool A = (i.x + i.w <= j.x || i.y >= j.y + j.h || i.z >= j.z +j.d);
    //paczka i jest na lewo, pod lub z tyłu w stosunku do paczki j
    bool B = (i.x <= j.x + j.w || i.y <= j.y + j.h || i.z <= j.z);
    //paczka i jest na prawo, pod, lub z przodu w stosunku do paczki j
    bool C = (i.x >= j.x + j.w || i.y + i.h <= j.y || i.z >= j.z + j.d);

    if(A && B && !C){
        //i jest na lewo od j
        return I_NA_LEWO_OD_J;
    } else if (!A && B && C) {
        //i jest ponizej j
        return I_PONIZEJ_J;
    } else if ((!A && B && !C) || (A && B && C)) {
        //i jest z tylu j
        return I_Z_TYLU_J;
    } else {
        //blad
        return BLAD;
    }

}

bool jakSortowac(Pudelko i, Pudelko j)
{
    return i.h < j.h;
}

/**
 * @brief Kontener::prostyAlgorytm
 * Sposób opierający się na First Fit Decreasing Height
 */
int Kontener::prostyAlgorytm(int czyKrokowo)
{
    std::vector<Pudelko> pakowanePudelka = PudelkadDoZapakowania;
    sort(pakowanePudelka.begin(), pakowanePudelka.end(), jakSortowac);
    /*
    for (unsigned int i = 0; i < pakowanePudelka.size(); ++i) {
       std::cout << pakowanePudelka.at(i).getW() << " " << pakowanePudelka.at(i).getD() << " " << pakowanePudelka.at(i).getH() << std::endl;
    }*/
    std::vector<int> wysokosciPlatform;
    wysokosciPlatform.push_back(0);
    while(pakowanePudelka.size() > 0)
    {

        int y = wysokosciPlatform.back();
        wysokosciPlatform.push_back(pakowanePudelka.back().h + wysokosciPlatform.back());
        //std::cout << "h: " << wysokosciPlatform.back() << std::endl;
        //Robimy platforme i wypelniamy ja
        std::vector<Pudelko> obecnaPlatforma;

        bool wstawiono = true;
        while(wstawiono && pakowanePudelka.size() > 0)
        {
            //bokPodstawy
            Pudelko pakowane = pakowanePudelka.back();
            //Pierwsze pudelko na platformie
            if(obecnaPlatforma.size() == 0)
            {
                pakowane.x = pakowane.z = 0;
            }
            else
            {
                pakowane.x = obecnaPlatforma.back().x + obecnaPlatforma.back().w;
                pakowane.z = obecnaPlatforma.back().z;
                //nie miesci sie horyzontalnie
                if (pakowane.x + pakowane.w > bokPodstawy)
                {
                    //sprawdzic najwyzszy na podstawie
//                    std::cout << "Nie miesci sie horyzontalnie | ";
                    pakowane.x = 0;
                    pakowane.z = 0;
                    for (unsigned int i = 0; i < obecnaPlatforma.size(); ++i)
                    {
                        if(pakowane.z < obecnaPlatforma[i].z + obecnaPlatforma[i].d)
                            pakowane.z = obecnaPlatforma[i].z + obecnaPlatforma[i].d;
                    }

                }
                //nie miesci sie na wysokosc
                if(pakowane.z + pakowane.d > bokPodstawy)
                {
                    wstawiono = false;
//                    std::cout << "Nie miesci sie wysokosciowo | ";
                    break;
                }
            }

            pakowane.y = y;

            if(czyKrokowo != 0)
            {
                std::getchar();
            }
            //zdjecie z pakowanych i wrzucenie do zapakowanych
            PudelkaZapakowane.push_back(pakowane);
            obecnaPlatforma.push_back(pakowane);
            std::cout << "x= " << pakowane.x << " (" << pakowane.w << ") z= " << pakowane.z << " (" << pakowane.d <<
                         ") y= " << pakowane.y << " (" << pakowane.h << ")" << std::endl;
            pakowanePudelka.pop_back();
        }//while
    }
    std::cout << "% wypelnienia: " << (objetoscPudelek() / (bokPodstawy * bokPodstawy * wysokosciPlatform.back())) * 100 << std::endl;
    return wysokosciPlatform.back();
}

int Kontener::gilotynowyAlgorytm()
{
    int dlugosc = 0;
    for (unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i) {
        Pudelko pudelko = PudelkadDoZapakowania.at(i);
        int wysokosc = pudelko.getD();
        if (wysokosc > pudelko.getH()) {
            wysokosc = pudelko.getH();
        } else if(wysokosc > pudelko.getW()) {
            wysokosc = pudelko.getW();
        }
        dlugosc += wysokosc;
    }
    return dlugosc;
}

double Kontener::objetoscPudelek()
{
    double objetosc = 0;
    for (unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i) {
        objetosc += PudelkadDoZapakowania[i].w * PudelkadDoZapakowania[i].h * PudelkadDoZapakowania[i].d;
    }
//    std::cout << objetosc;
    return objetosc;
}
