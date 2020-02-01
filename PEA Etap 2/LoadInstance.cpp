#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "LoadInstance.h"
#include "Timer.h"
#include "SimulatedAnnealing.h"


using namespace std;

LoadInstance::LoadInstance()
{
    instance = "";
    number = 0;
    size = 0;
}


void LoadInstance::load()
{
    Timer czas; //obiekt wykorzystywany przy pomiarach czasu

    string name = "";
    cout << "Podaj nazwe instancji  'data.txt': " << endl;
    cin >> name;
    instance = "C:/Users/Krzysiek/Desktop/PEA/PEA Etap 2/ATSP/ATSP/" + name;
    ifstream data(instance.c_str());
    if (!data)
    {
        cout << "Wykryto blad przy otwieraniu pliku." << endl << endl;
        return;
    }

    data >> instance >> size;

    costMatrix = new int* [size];         // utworzenie tablicy wskaznikow

    for (int i = 0; i < size; i++)
    {
        costMatrix[i] = new int[size];    //utworzenie macierzy dwuwymiaorwej
    }


    for (int i = 0; i < size; i++)         //wypelnienie macierzy wartosciami wejsciowymi
    {
        for (int j = 0; j < size; j++)
        {
            data >> costMatrix[i][j];
        }
    }
    cout << endl;
    data.close();

    cout << "Instancja zostala wczytana pomyslnie." << endl << endl;
    double timeOf = 0;
    double najmsciezka = INT_MAX;
    int wybor;
    int numberOfIterations = 5;
   /* cout << "Algorytm: " << endl;
    cout << "1. Symulowane wyzarzanie  " << endl;
    cout << "2. Tabu Search/ TODO" << endl;
    cin >> wybor; cout << endl;
       if (wybor == 1)
    {*/
           for (int i = 0; i < 300 ; i++) {
               
               //cout << "Podaj ilosc iteracji algorytmu" << endl;
              // cin >> numberOfIterations;
               SimulatedAnnealing symulacja(costMatrix, size, numberOfIterations);

               czas.start();
               symulacja.simulatedAnnealing();
              // cout << "Czas wykonywania algorytmu: " << czas.duration() << "[ms]" << endl;
               if (symulacja.Get() < najmsciezka) {
                   najmsciezka = symulacja.Get();
                   timeOf = czas.duration();
               }
              // symulacja.show();
           }
           cout << "Najmniejsza sciezka: " << najmsciezka << endl;
           cout << "Czas wykonywania algorytmu: " << timeOf << "[ms]" << endl;
    /*}
    else*/ return;
}

