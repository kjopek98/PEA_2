#ifndef LOADINSTANCE_H
#define LOADINSTANCE_H

#include <string>


using namespace std;

class LoadInstance
{
public:
    LoadInstance();

    string instance;    //nazwa instancji
    int number;         //numer pliku do wczytania
    int size;           //rozmiar instancji
    int** costMatrix;   //wskaznik na macierz kosztow podrozy komiwojazera

    void load();     //laduje jedna instancje problemu wskazana przez uzytkownika

};

#endif // LOADINSTANCE_H
