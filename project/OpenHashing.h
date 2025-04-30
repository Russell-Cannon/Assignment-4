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
    std::vector<std::list<WordPair>> open_hash_table;
    int size;

public:
    OpenHashing(int s); // create hash table with specified size

    void readUntilVII(std::ifstream& in); // reads until the cleaned word "vii" (marks the end of Book VI)
    void insert(const std::string& raw_word); // clean and insert word into hash table
    int getWordCount(const std::string& raw_word) const; // get how many times a word appears in the table
    
    // these functions return a vector of the data in hash table
    std::vector<std::list<WordPair>> getOpenHashTable() const; // deep copy open hash table, keeps chains
    std::vector<WordPair> getAllWordsUnsorted() const; //  unsorted words, unchains data
    std::vector<WordPair> getAllWordsSortedDescending() const; // desecending by word count, unchains data
    std::vector<WordPair> getAllWordsSortedAscending() const; // ascending by word count, unchains data
    void fillAllWords(std::vector<WordPair>& outWords) const; // helper function that fills word-count pairs from hash table, unchains data
    
    // display the most or least frequent n words
    void displayMostFrequent(int n) const;
    void displayLeastFrequent(int n) const;

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

// constructor
OpenHashing::OpenHashing(int s) : size(s) {
    open_hash_table.resize(size);
}

// Reads and inserts words until "vii"
void OpenHashing::readUntilVII(std::ifstream& inFile) {
    std::string word;
    while (inFile >> word) {
        std::vector<std::string> words;
        clean_and_split(word, words);
        for (std::string w : words) {
            clean(w);
            if (w == "vii") {
                return;
            }

            insert(w);
        }
    }
}

// Insert a word (or increment if already exists) in hash table
void OpenHashing::insert(const std::string& raw_word) {
    std::string word = raw_word;
    clean(word);
    if (word.empty()) {
        return;
    }
    int index = hash(word, size);
    for (auto& wc : open_hash_table[index]) {
        if (wc.word == word) { 
            wc.count++; 
            return; 
        }
    }
    open_hash_table[index].push_back({word, 1}); // chain word to list
}

// Gets how many time a word appears (word count)
int OpenHashing::getWordCount(const std::string& raw_word) const {
    std::string word = raw_word;
    clean(word);
    int index = hash(word, size);
    for (const auto& wc : open_hash_table[index]) {
        if (wc.word == word) {
            return wc.count;
        }
    }
    return 0;
}

// Returns a deep copy of internal hash table
std::vector<std::list<WordPair>> OpenHashing::getOpenHashTable() const {
    std::vector<std::list<WordPair>> copy = open_hash_table;
    return copy;
}

// Returns all word-count pairs unsorted, unchains words
std::vector<WordPair> OpenHashing::getAllWordsUnsorted() const {
    std::vector<WordPair> words;
    fillAllWords(words);
    return words;
}

// Returns all word-count pairs sorted in descending order, unchains words
std::vector<WordPair> OpenHashing::getAllWordsSortedDescending() const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsDescending(words);
    return words;
}

// Returns all word-count pairs sorted in ascending order, unchains words
std::vector<WordPair> OpenHashing::getAllWordsSortedAscending() const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsAscending(words);
    return words;
}

// Helper function that fills parameter word-count pairs, unchains words
void OpenHashing::fillAllWords(std::vector<WordPair>& outWords) const {
    for (const auto& chain : open_hash_table) {
        for (const auto& wc : chain) {
            outWords.push_back(wc);
        }
    }
}

// prints n most frequent words
void OpenHashing::displayMostFrequent(int n) const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsDescending(words);
    for (int i = 0; i < n && i < (int)words.size(); ++i) {
        std::cout << words[i].word << ": " << words[i].count << '\n';
    }
}

// prints n least frequent words
void OpenHashing::displayLeastFrequent(int n) const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsAscending(words);
    for (int i = 0; i < n && i < (int)words.size(); ++i) {
        std::cout << words[i].word << ": " << words[i].count << '\n';
    }
}

// gets n most frequent words
std::vector<WordPair> OpenHashing::getMostFrequent(int n) const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsDescending(words);
    if ((int)words.size() > n) {
        words.resize(n);
    }
    return words;
}

// gets n least frequent words
std::vector<WordPair> OpenHashing::getLeastFrequent(int n) const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsAscending(words);
    if ((int)words.size() > n) {
        words.resize(n);
    }

    return words;
}

// insertion sort for quickSortHybrid
void OpenHashing::insertionSort(std::vector<WordPair>& vec, int low, int high, bool descending) const {
    for (int i = low + 1; i <= high; ++i) {
        WordPair key = vec[i];
        int j = i - 1;
        while (j >= low && ((descending ? vec[j].count < key.count : vec[j].count > key.count) || (vec[j].count == key.count && vec[j].word > key.word))) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

// Quicksort partition using middle element as pivot
int OpenHashing::partition(std::vector<WordPair>& vec, int low, int high, bool descending) const {
    int mid = low + (high - low) / 2;
    WordPair pivot = vec[mid];
    std::swap(vec[mid], vec[high]);
    int i = low;
    for (int j = low; j < high; ++j) {
        if ((descending ? vec[j].count > pivot.count : vec[j].count < pivot.count) || (vec[j].count == pivot.count && vec[j].word < pivot.word)) {
            std::swap(vec[i], vec[j]);
            ++i;
        }
    }
    std::swap(vec[i], vec[high]);
    return i;
}

// Quicksort that switches to insertion sort for small sub vectors of size 20 or less
void OpenHashing::quickSortHybrid(std::vector<WordPair>& vec, int low, int high, bool descending) const {
    const int INSERTION_THRESHOLD = 20;

    if (low < high) {
        if (high - low + 1 <= INSERTION_THRESHOLD) {
            insertionSort(vec, low, high, descending);
        } else {
            int pivotIndex = partition(vec, low, high, descending);
            quickSortHybrid(vec, low, pivotIndex - 1, descending);
            quickSortHybrid(vec, pivotIndex + 1, high, descending);
        }
    }
}

// Sort from most to least frequent
void OpenHashing::sortWordPairsDescending(std::vector<WordPair>& vec) const {
    if (!vec.empty()) {
        quickSortHybrid(vec, 0, static_cast<int>(vec.size() - 1), true);
    }
}

// Sort from least to most frequent
void OpenHashing::sortWordPairsAscending(std::vector<WordPair>& vec) const {
    if (!vec.empty()) {
        quickSortHybrid(vec, 0, static_cast<int>(vec.size() - 1), false);
    }
}
