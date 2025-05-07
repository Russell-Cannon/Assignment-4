#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Functions.h"
#include "WordPair.h"

struct Pattern {
    std::string raw;              
    std::string pat;              
    int M;                         
    int d = 256;
    int q = 2147483647;
    long p_hash = 0;              
    long h = 1; 
    long w_hash = 0;                  
    std::deque<char> window;      
    std::vector<int> occurrences; 
};

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
    void addElement(WordPair pair);
    void addInsertionTime(std::chrono::nanoseconds ns);

    
    private:
    int size = 64, occupancy = 0;
    WordPair* arr = nullptr;
    std::chrono::nanoseconds total_nanoseconds;
    
    void resize();
};
