#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LoadInstance.h"

using namespace std;

int main()
{
    int menu;
    LoadInstance load;
    srand(time(NULL));
    do
    {
        cout << "\nProjektowanie Efektywnych Algorytmow - Etap 2\nKrzysztof Jopek\n241406\n\n";
        cout << "M E N U  G L O W N E" << endl;
        cout << "1.Wczytaj instancje z pliku" << endl;
        cout << "2.Wyjscie" << endl << endl;
        cin >> menu; // wprowadzenie zmiennej wyboru uzytkownika
        cout << endl << endl;

        if (menu != 1 && menu != 2) break; // warunek wyjscia z programu

        switch (menu)
        {
        case 1: load.load();
            break;

		case 2: cout << "Zakonczono.\n" << endl;
			return 0;
			

        }
    } while (menu);
    return 0;
}
