#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "Functions.h" 
#include "WordPair.h"

class OpenHashing {
private:
    std::list<WordPair>* open_hash_table;
    int size, occupancy;
    std::chrono::nanoseconds total_nanoseconds;

public:
    OpenHashing(); // create hash table
    ~OpenHashing(); // delete hash table

    void readUntil(std::ifstream& in, std::string delimiter); // reads until the cleaned word "vii" (marks the end of Book VI)
    void insert(const std::string& raw_word); // clean and insert word into hash table
    void resize(); //Double the size of the hash_table.
    int getWordCount(const std::string& raw_word) const; // get how many times a word appears in the table
    void printChainStats(std::ostream& out) const; // Prints the average, max, and min chainlength in the table
    std::chrono::nanoseconds getTotalNanoseconds(); // return total nanoseconds

    // these functions return a vector of the data in hash table
    std::vector<std::list<WordPair>> getOpenHashTable() const; // deep copy open hash table, keeps chains
    std::vector<WordPair> getAllWordsUnsorted() const; //  unsorted words, unchains data
    std::vector<WordPair> getAllWordsSortedDescending() const; // desecending by word count, unchains data
    std::vector<WordPair> getAllWordsSortedAscending() const; // ascending by word count, unchains data
    void fillAllWords(std::vector<WordPair>& outWords) const; // helper function that fills word-count pairs from hash table, unchains data

    // gets the most or least frequent n words
    std::vector<WordPair> getMostFrequent(int n) const;
    std::vector<WordPair> getLeastFrequent(int n) const;

    // Sorting function & helpers  |  sort by word counts
    void insertionSort(std::vector<WordPair>& vec, int low, int high, bool descending) const;
    int partition(std::vector<WordPair>& vec, int low, int high, bool descending) const;
    void quickSortHybrid(std::vector<WordPair>& vec, int low, int high, bool descending) const;
    void sortWordPairsDescending(std::vector<WordPair>& vec) const; // Sort from most to least frequent
    void sortWordPairsAscending(std::vector<WordPair>& vec) const; // Sort from least to most frequent
};
