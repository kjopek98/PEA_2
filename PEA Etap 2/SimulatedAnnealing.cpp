#include "SimulatedAnnealing.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include <conio.h>


SimulatedAnnealing::SimulatedAnnealing(int** loadedMatrix, double sizeOfMatrix, int counter)
{
	T = 0;
	size = sizeOfMatrix;
	iterationCounter = counter;
	bestCostOfRoad = INT_MAX;
	//TMax = 10000; // temperatura pocz¹tkowa
	TMax = sizeOfMatrix * sizeOfMatrix * 1000 * 0.7; // temperatura pocz¹tkowa

	//tabela zmiennych do wy¿arzania
	constants = new double[10];
	constants[0] = 0.75;
	constants[1] = 0.8;
	constants[2] = 0.85;
	constants[3] = 0.9;
	constants[4] = 0.95;
	constants[5] = 0.975;
	constants[6] = 0.999;
	constants[7] = 0.9999;
	constants[8] = 0.99999;
	constants[9] = 0.999999;
	/*constants[0] = 0.99;
	constants[1] = 0.99;
	constants[2] = 0.99;
	constants[3] = 0.99;
	constants[4] = 0.99;
	constants[5] = 0.99;
	constants[6] = 0.99;
	constants[7] = 0.99;
	constants[8] = 0.99;
	constants[9] = 0.99;*/

	//Tworzenie kopii macierzy kosztów do u¿ycia w algorytmie
	matrixOfCost = new int* [size];
	for (int i = 0; i < size; i++)
	{
		matrixOfCost[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			matrixOfCost[i][j] = loadedMatrix[i][j];		//przekopiowanie wartosci macierzy kosztow do wewnetrznej macierzy algorytmu
		}
	}
}

// generowanie permutacji 
void SimulatedAnnealing::generatePerm(int*& perm)
{
	int* tab = new int[size];	//tymczasowa tablica
	int q;								//zmienna pomocnicza
	for (int i = 0; i < size; i++)
	{
		tab[i] = i;					//inicjalizacja tablicy pomocniczej kolejnymi wierzcholkami
	}
	for (int i = size; i > 0; i--)
	{
		q = rand() % i;
		perm[i - 1] = tab[q];	// losowanie indeksu zeby przypisac do permutacji
		tab[q] = tab[i - 1];
	}
	delete[] tab;
} 

// prawdopodobienatwo przyjecia gorszej sciezki
bool SimulatedAnnealing::probability(double a, double b)
{
	double q = pow( M_E , ((-1 * (b - a)) / T));	//wzor na wyliczenie prawdopodobieñstwa
	double r = (double)rand() / RAND_MAX;
	if (r < q) 
	{
		// uznano, ¿e to gorsza sciezka
		return true; 
	}
	else
		return false;
}


// obliczenie kosztu sciezki
int SimulatedAnnealing::road(int* perm) 
{
	int cost = 0;
	for (int i = 0; i < size - 1; i++)
	{
		cost += matrixOfCost[perm[i]][perm[i + 1]]; //obliczanie kosztow przejsc miedzy wierzcholkami
	}
	cost += matrixOfCost[perm[size - 1]][perm[0]]; // doliczenie kosztu powrotu
	return cost;
}

// wyœwietlenie wyniku
void SimulatedAnnealing::show()
{
	cout << "Najlepszy znaleziony koszt sciezki : " << bestCostOfRoad << endl;
}

double SimulatedAnnealing::Get(){
	 return bestCostOfRoad;
}

double SimulatedAnnealing::GetT() {
	return T;
}
// g³ówna funkcja algorytmu
void SimulatedAnnealing::simulatedAnnealing()
{

	 // iteracja po zmiennych tyle razy ile poda³ u¿ytkownik
	
		for (int i = 0; i < iterationCounter; i++) 
		{
			int cost = INT_MAX;
			int* firstPerm = new int[size]; // permutacje miast
			int* secondPerm = new int[size];
			int firstVertex, secondVertex, a, b;
			
			T = TMax; //przypisanie pocz¹tkowej maksymalnej temperatury

			generatePerm(firstPerm); // generowanie loswej permutacji
			a = road(firstPerm);	   // i obliczenie jej kocztu			
			for (int j = 0; j < size; j++)
			{
				secondPerm[j] = firstPerm[j];	
			}

			while (T > 0.01 ) // wykonuje siê, dopóki temperatura nie spadnie do wartoœci minimalnej - (0.01)
			{
				do 
				{
					// losowanie miast do zamiany 
					firstVertex = rand() % size; 
					secondVertex = rand() % size;
				} while (firstVertex == secondVertex);

				swap(secondPerm[firstVertex],secondPerm[secondVertex]); // zamiana miast s¹siednich swapem
				
				b = road(secondPerm); // obliczenie kosztu drugiej œcie¿ki

				if (b <= a || probability(a, b) == true)  // jeœli b <= a lub prawdopodobieñstwo jest dobre
				{ 
					a = b;
					if (a <= cost) // sprawdzenie, czy œcie¿ka ma ni¿szy koszt ni¿ obecne najlepsze rozwi¹zanie
					{
						cost = a;
					}
					firstPerm[firstVertex] = secondPerm[firstVertex];
					firstPerm[secondVertex] = secondPerm[secondVertex]; // przyjmujemy drug¹ permutacje jako kolejna wyjsciowa
				}
				else				//powrot do pocz¹tku, jesli nie ma szans na wyznaczenie lepszego kosztu
				{
					secondPerm[firstVertex] = firstPerm[firstVertex]; 
					secondPerm[secondVertex] = firstPerm[secondVertex]; 
				}
				T *= constants[i]; // mnozenie temperatury przez wyznaczona sta³¹ z tablicy
				//cout << "T wynosi: " << T << endl;
			}

			delete[] firstPerm;
			delete[] secondPerm;	//usuwanie permutacji, na których wykonala sie iteracja
			if (cost < bestCostOfRoad)
			{
				bestCostOfRoad = cost;		//wyznaczenie najlepszej sciezki
			}
		}
}