#include "LinearProbing.h"
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>

void clean(std::string& _word);
int hash(const std::vector<std::list<int>>& hash_table, const std::string& word);

int main() 
{
    // Works I through VI should be stored using open hashing (separate chaining)
    // std::ifstream I_VI("I_VI.txt");
    // std::string word;
    // std::vector<std::list<int>> open_hash;

    //Get open_hash working

    // while (I_VI >> word) {
    //     clean(word);

    //     open_hash[hash(open_hash, word)].front() = 1;
    // }

    // Works VII to XII should be stored using Linear Probing.
    std::ifstream VII_XII("VII_XII.txt");
    LinearProbing linear(VII_XII);
    
    // Once the data is processed, the program should display and record to a file a list of word occurrences from highest to lowest vice versa of the 80 most and least repeated words (and their count)


    //As the program starts processing work IX “The Adventure of the Engineer’s Thumb”, it should prompt the user for search key
    //display the position of each key’s occurrence in the text

    //Rabin-Karp pattern matching algorithm and Horner’s rule for the rolling hash should be utilized for this purpose

    return 0;
}

void clean(std::string& _word) 
{
    // It’s important to note that capitalization should not matter (i.e., “Watson” and “watson” should be counted as the same word)
    for (int i = 0; i < _word.size(); i++) {
        _word[i] = tolower(_word[i]);
        // but hyphenation is critical, and double hyphens “–” should be discarded.
        // TODO
    }
}

int hash(const std::vector<std::list<int>>& hash_table, const std::string& word) 
{
    int n = 0;
    for (int i = 0; i < word.size(); i++) n += (word[i] - 'a')*(i+1);
    return n % hash_table.size();
}

/*
    auto tot_start = std::chrono::high_resolution_clock::now();
    auto tot_stop = std::chrono::high_resolution_clock::now();
    auto tot_time = std::chrono::duration_cast<std::chrono::nanoseconds>(tot_stop - tot_start);
    std::cout << "Final time: " << tot_time.count() << " seconds!" << std::endl;
*/