/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include "OpenHashing.h"
#include "Functions.h"
#include "LinearProbing.h"

void Search(const std::string& pat, const std::string& txt, int q);
void Rabin(const std::string& txt, std::string pat);
bool Las_vegas(std::string pat, std::string txt, int i);
