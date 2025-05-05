#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Functions.h"
#include "WordPair.h"

class LinearProbing {
public:
    LinearProbing();
    LinearProbing(std::istream& in);
    LinearProbing(std::vector<WordPair>& in);
    ~LinearProbing();

    void read(std::istream& in);
    void readUntil(std::istream& in, std::string end);
    void read(std::vector<WordPair>& in);
    std::chrono::nanoseconds getTotalNanoseconds();
    void output(std::ostream& out);  
    void printStats(std::ostream& out);
    std::vector<WordPair> getMostFrequent(int K);
    std::vector<WordPair> getLeastFrequent(int K);

private:
    int size = 64, occupancy = 0;
    WordPair* arr = nullptr;
    std::chrono::nanoseconds total_nanoseconds;

    void addElement(WordPair pair);
    void resize();
};
