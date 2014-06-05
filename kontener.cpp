#include "kontener.h"


Kontener::Kontener()
{
    rezultatDrzewa = std::make_pair(NULL, 0);
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
       std::cout << PudelkadDoZapakowania.at(i).w << " " << PudelkadDoZapakowania.at(i).d << " " << PudelkadDoZapakowania.at(i).h << std::endl;
    }
}

int Kontener::ustawBokPodstawy(int bok)
{
    int max = 0;
    for (unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i)
    {
       if(PudelkadDoZapakowania.at(i).w > max) {
           max = PudelkadDoZapakowania.at(i).w;
       }
       if(PudelkadDoZapakowania.at(i).d > max) {
           max = PudelkadDoZapakowania.at(i).d;
       }
       if(PudelkadDoZapakowania.at(i).h > max) {
           max = PudelkadDoZapakowania.at(i).h;
       }
    }
    if(bok >= max)
    {
        bokPodstawy = bok;
        return bokPodstawy;
    }
    else
    {
        return 0;
    }
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
 * @brief Kontener::nextFitDecreasingHeight
 * Sposób opierający się na Next Fit Decreasing Height
 * @return uzyskaną wysokość
 */
double Kontener::nextFitDecreasingHeight(int czyKrokowo)
{
    std::vector<Pudelko> pakowanePudelka = PudelkadDoZapakowania;
    sort(pakowanePudelka.begin(), pakowanePudelka.end(), jakSortowac);

    std::vector<int> wysokosciPlatform;
    wysokosciPlatform.push_back(0);
    while(pakowanePudelka.size() > 0)
    {
        int y = wysokosciPlatform.back();
        wysokosciPlatform.push_back(pakowanePudelka.back().h + wysokosciPlatform.back());

        //Robimy platforme i wypelniamy ja
        std::vector<Pudelko> obecnaPlatforma;

        bool wstawiono = true;
        while(wstawiono && pakowanePudelka.size() > 0)
        {
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
                    break;
                }
            }

            pakowane.y = y;

            if(czyKrokowo != 0)
            {
                std::cout << "x= " << pakowane.x << " (" << pakowane.w << ") z= " << pakowane.z << " (" << pakowane.d <<
                          ") y= " << pakowane.y << " (" << pakowane.h << ")" << std::endl;
                std::getchar();
            }
            //zdjecie z pakowanych i wrzucenie do zapakowanych
            rezultatNFDH.push_back(pakowane);
            obecnaPlatforma.push_back(pakowane);

            pakowanePudelka.pop_back();
        }//while
    }

    std::cout << "% wypelnienia: " << (objetoscPudelek() / (bokPodstawy * bokPodstawy * wysokosciPlatform.back())) * 100 << std::endl;
    return wysokosciPlatform.back();
}
/**
 * @brief Kontener::trywialnyAlgorytm
 * @param czyKrokowo
 * @return uzyskaną wysokość
 */
double Kontener::trywialnyAlgorytm(int czyKrokowo)
{
    double dlugosc = 0;
    Pudelko pierwsze = PudelkadDoZapakowania[0];
    pierwsze.x = 0;
    pierwsze.y = 0;
    pierwsze.z = 0;
    rezultatTrywialnego.push_back(pierwsze);

    for (unsigned int i = 1; i < PudelkadDoZapakowania.size(); ++i)
    {
        Pudelko pakowane = PudelkadDoZapakowania[i];
        pakujNaroznikami(pakowane, rezultatTrywialnego);
        rezultatTrywialnego.push_back(pakowane);
        if(czyKrokowo != 0)
        {
            std::cout << "x= " << pakowane.x << " (" << pakowane.w << ") z= " << pakowane.z << " (" << pakowane.d <<
                      ") y= " << pakowane.y << " (" << pakowane.h << ")" << std::endl;
            std::getchar();
        }
    }
    for (unsigned int i = 0; i < rezultatTrywialnego.size(); ++i)
    {
       Pudelko bierzace = rezultatTrywialnego[i];
       if(bierzace.y + bierzace.h > dlugosc)
           dlugosc = bierzace.y + bierzace.h;
    }

    std::cout << "% wypelnienia: " << (objetoscPudelek() / (bokPodstawy * bokPodstawy * dlugosc)) * 100 << std::endl;
    return dlugosc;
}

double Kontener::objetoscPudelek()
{
    double objetosc = 0;
    for (unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i) {
        objetosc += PudelkadDoZapakowania[i].w * PudelkadDoZapakowania[i].h * PudelkadDoZapakowania[i].d;
    }

    return objetosc;
}

void Kontener::zapiszDoPliku(std::vector<Pudelko> doPliku)
{
    std::ofstream NowyPlik;
    NowyPlik.open("cuboids_to_render.xml");
    NowyPlik << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>" << std::endl;
    NowyPlik << "<!DOCTYPE boost_serialization>" << std::endl;
    NowyPlik << "<boost_serialization signature=\"serialization::archive\" version=\"10\">" << std::endl;
    NowyPlik << "<cuboid class_id=\"0\" tracking_level=\"0\" version=\"0\">" << std::endl;

    bool pierwszy = true;
    for (unsigned int i = 0; i < doPliku.size(); ++i) {
       Pudelko cuboid = doPliku[i];
       if(!pierwszy)
       {
           NowyPlik << "<cuboid>" << std::endl;
       }
       pierwszy = false;
       NowyPlik << "<width>" << cuboid.w << "</width>" << std::endl;
       NowyPlik << "<height>" << cuboid.h << "</height>" << std::endl;
       NowyPlik << "<depth>" << cuboid.d << "</depth>" << std::endl;
       NowyPlik << "<x>" << (float)(cuboid.x + (float)cuboid.w/2) << "</x>" << std::endl;
       NowyPlik << "<y>" << (float)(cuboid.y + (float)cuboid.h/2) << "</y>" << std::endl;
       NowyPlik << "<z>" << (float)(cuboid.z + (float)cuboid.d/2) << "</z>" << std::endl;
       NowyPlik << "</cuboid>" << std::endl;
    }
    NowyPlik << "<base class_id=\"1\" tracking_level=\"0\" version=\"0\">" << std::endl;
    NowyPlik << "<width>" << bokPodstawy << "</width>" << std::endl;
    NowyPlik << "<height>" << bokPodstawy << "</height>" << std::endl;
    NowyPlik << "<x>" << 0 << "</x>" << std::endl;
    NowyPlik << "<y>" << 0 << "</y>" << std::endl;
    NowyPlik << "</base>" << std::endl << "</boost_serialization>";
}

void Kontener::zapiszDoPlikuWygenerowane()
{
    std::ofstream NowyPlik;
    NowyPlik.open("wygenerowane.txt");

    for (unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i)
    {
        Pudelko cuboid = PudelkadDoZapakowania[i];
        NowyPlik << cuboid.w << " " << cuboid.d << " " << cuboid.h << std::endl;
    }
}

void Kontener::rekurencja(int nrDoZapakowania, std::vector<Pudelko> doZapakowania, std::vector<Pudelko> zapakowane)
{
    Pudelko doPakowania = doZapakowania[nrDoZapakowania];
    doZapakowania.erase(doZapakowania.begin() + nrDoZapakowania);


    for (int j = 0; j < 6; ++j)
    {
        Pudelko pakowane = doPakowania.rotacje().at(j);
        std::vector<Pudelko> ulozone = zapakowane;

        //Pierwsze pudełko
        if(zapakowane.size() == 0)
        {
            pakowane.x = 0;
            pakowane.z = 0;
            pakowane.y = 0;
            std::vector<Pudelko> pudelka;
            pudelka.push_back(pakowane);


            for(unsigned int i = 0; i < doZapakowania.size(); ++i)
            {
                rekurencja(i, doZapakowania, pudelka);
            }
        }
        else
        {
            //wyznacz pozycje do zapakowania
            pakujNaroznikami(pakowane, ulozone);

            //dodaj do zapakowanych
            ulozone.push_back(pakowane);

            //Wszystko zapakowano
            if(doZapakowania.size() == 0)
            {
                double wysokosc = 0;
                for(unsigned int i = ulozone.size() - 4; i < ulozone.size(); ++i)
                {
                    if(wysokosc < ulozone[i].h + ulozone[i].y)
                        wysokosc = ulozone[i].h + ulozone[i].y;
                }
                //Uzyskano lepszy rezultat
                if(rezultatDrzewa.second > wysokosc || rezultatDrzewa.second == 0)
                {
                    rezultatDrzewa = std::make_pair(ulozone, wysokosc);
                }
            }
            else
            {
                for(unsigned int i = 0; i < doZapakowania.size(); ++i)
                {
                    //Idziemy w kierunku gorszego rezultatu
                    if(rezultatDrzewa.second < (pakowane.y + pakowane.h) && rezultatDrzewa.second != 0)
                    {
                        return;
                    }
                    rekurencja(i, doZapakowania, ulozone);
                }
            }
        }
    }


}

void Kontener::pakujNaroznikami(Pudelko &pakowane, std::vector<Pudelko> &zapakowane)
{
    Pudelko poprzedzajace = zapakowane.back();

    //Poprzedni w lewym dolnym rogu
    if(poprzedzajace.x == 0 && poprzedzajace.z == 0)
    {
        //nie miesci sie - wstawione na kolejny poziom
        if(poprzedzajace.d + pakowane.d > bokPodstawy)
        {
            pakowane.x = 0;
            pakowane.z = 0;
            pakowane.y = poprzedzajace.y + poprzedzajace.h;
        }
        //miesci sie
        else
        {
        pakowane.x = 0;
        pakowane.z = bokPodstawy - pakowane.d;
        pakowane.y = poprzedzajace.y;
        }
    }
    //Poprzedni w lewym gornym rogu
    else if(poprzedzajace.x == 0)
    {
        //nie miesci sie - wstawione na kolejny poziom
        if(poprzedzajace.w + pakowane.w > bokPodstawy ||
                zapakowane[zapakowane.size() - 2].w + pakowane.w > bokPodstawy ||
                zapakowane[zapakowane.size() - 2].d + pakowane.d > bokPodstawy)
        {
            pakowane.x = 0;
            pakowane.z = 0;
            if(poprzedzajace.h < zapakowane[zapakowane.size() - 2].h)
            {
                pakowane.y = poprzedzajace.y + zapakowane[zapakowane.size() - 2].h;
            }
            else
            {
                pakowane.y = poprzedzajace.y + poprzedzajace.h;
            }
        }
        //miesci sie
        else
        {
            pakowane.x = bokPodstawy - pakowane.w;
            pakowane.z = bokPodstawy - pakowane.d;
            pakowane.y = poprzedzajace.y;
        }
    }
    //Poprzedni w prawym gornym rogu
    else if(poprzedzajace.z != 0)
    {
        //nie miesci sie - wstawione na kolejny poziom
        if(poprzedzajace.d + pakowane.d > bokPodstawy ||
                zapakowane[zapakowane.size() - 2].w + pakowane.w > bokPodstawy ||
                zapakowane[zapakowane.size() - 2].d + pakowane.d > bokPodstawy ||
                zapakowane[zapakowane.size() - 3].w + pakowane.w > bokPodstawy)
        {
            pakowane.x = 0;
            pakowane.z = 0;
            pakowane.y = poprzedzajace.y;
            int wysokosc = 0;
            for(unsigned int i = zapakowane.size() - 3; i < zapakowane.size(); ++i)
            {
                if(wysokosc < zapakowane[i].h)
                    wysokosc = zapakowane[i].h;
            }
            pakowane.y += wysokosc;
        }
        //miesci sie
        else
        {
            pakowane.x = bokPodstawy - pakowane.w;
            pakowane.z = 0;
            pakowane.y = poprzedzajace.y;
        }
    }
    //Poprzedni w prawym dolnym rogu - przechodze na kolejny poziom
    else
    {
        pakowane.x = 0;
        pakowane.z = 0;
        pakowane.y = poprzedzajace.y;
        int wysokosc = 0;
        for(unsigned int i = zapakowane.size() - 4; i < zapakowane.size(); ++i)
        {
            if(wysokosc < zapakowane[i].h)
                wysokosc = zapakowane[i].h;
        }
        pakowane.y += wysokosc;
    }
}

double Kontener::drzewoPrzeszukiwan()
{
    std::cout << "Przeszukuję drzewo rozwiązań..." << std::endl;

    for(unsigned int i = 0; i < PudelkadDoZapakowania.size(); ++i)
    {
        std::vector<Pudelko> pusto;
        rekurencja(i, PudelkadDoZapakowania, pusto);
    }

    std::cout << "% wypelnienia: " << (objetoscPudelek() / (bokPodstawy * bokPodstawy * rezultatDrzewa.second)) * 100 << std::endl;
    return rezultatDrzewa.second;
}

std::vector<Pudelko> Kontener::dajRezultatNFDH()
{
    return rezultatNFDH;
}

std::vector<Pudelko> Kontener::dajRezultatDrzewa()
{
    return rezultatDrzewa.first;
}

std::vector<Pudelko> Kontener::dajRezultatTrywialnego()
{
    return rezultatTrywialnego;
}

