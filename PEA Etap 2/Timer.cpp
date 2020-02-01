#include <iostream>
#include <chrono>
#include "Timer.h"
#include <windows.h>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;
void Timer::start()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0; // czas w milisekundach

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double Timer::duration()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}
