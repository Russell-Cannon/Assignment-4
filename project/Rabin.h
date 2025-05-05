/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include "OpenHashing.h"
#include "Functions.h"
#include "LinearProbing.h"
using namespace std;

int search(string pat, string txt, int q);
bool Las_vegas(string, string, int);
int Wordplace(int, string);

int Rabin(int row);


// Search the pat string in the txt string
int search(string pat, string txt, int q);

bool Las_vegas(string pat, string txt, int i);

int Wordplace(int index, string txt);

/*
    auto tot_start = std::chrono::high_resolution_clock::now();
    auto tot_stop = std::chrono::high_resolution_clock::now();
    auto tot_time = std::chrono::duration_cast<std::chrono::nanoseconds>(tot_stop - tot_start);
    std::cout << "Final time: " << tot_time.count() << " seconds!" << std::endl;
*/