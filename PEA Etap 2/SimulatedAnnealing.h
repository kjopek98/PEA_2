#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class SimulatedAnnealing
{
	int** matrixOfCost;	//wskaznik na dynamiczna macierz zawierajaca macierz kosztow przejsc
	int size;			//rozmiar instancji
	int iterationCounter;	//liczba iteracji algorytmu
	double TMax;			// pocz¹tkowa temperatura
	double T;				
	double bestCostOfRoad;	//najlepsze znalezione rozwiazanie
	double* constants;		//tablica ze stalymi potrzebnymi do obliczania temperatury

public:
	SimulatedAnnealing(int** loadedMatrix, double sizeOfMatrix, int counter);	//konstrutor klasy
	void generatePerm(int*& perm);		//generowanie loswej permutacji
	int road(int* perm);					//oblizanie kosztu sciezki
	bool probability(double a, double b);			//oblizenie prawdopodobieñstwa znalezienia lepszego rozwiazania
	void simulatedAnnealing();						//funkcja glowna algorytmu
	void show();								//funkcja wyswietlajaca wyniki na ekran
	double Get();
	double GetT();
};

#endif