#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <ratio>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Timer
{
public:

    void start();  //metoda wyznaczajaca czas startu algorytmu

    double duration(); // metoda wyznaczajaca czas dzialania algorytmu
};

#endif 
