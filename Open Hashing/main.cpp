#include "openhashing.h"
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream in("A Scandal In Bohemia.txt");
    if (!in.is_open()) {
        std::cerr << "Failed to open input file.\n";
        return 1;
    }

    // Create open hash table
    OpenHashing openHash(16691);

    // Fill the table with Works I–VI
    openHash.readUntilVII(in);

    // display 80 most frequent occuring words
    std::cout << "80 most frequent words\n";
    openHash.displayMostFrequent(80);

    std::cout <<"\n =============================================" << std::endl;
    
    // display 80 least frequent occuring words
    std::cout << "\n80 least frequent words\n";
    openHash.displayLeastFrequent(80);

    
    return 0;
}
