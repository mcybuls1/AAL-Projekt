#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    clock_t czasStart = clock();
    cout << "Dobry projekt! wykonuje sie:" << endl;
    for (int i = 0; i < 300000000; i++);
    float czasWykonania = ((float)clock() - czasStart)/CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << czasWykonania << " sec"<< endl;

    return 0;
}

