#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "Functions.h" 

// Struct that keeps track of word and word count
struct WordCount {
    std::string word;
    int count;
};

class OpenHashTable {
private:
    std::vector<std::list<WordCount>> open_hash_table;
    int size;

public:
    OpenHashTable(int s); // create hash table with specified size

    void readUntilVII(std::ifstream& in); // reads until the cleaned word "vii" (marks the end of Book VI)
    void insert(const std::string& raw_word); // clean and insert word into hash table
    int getWordCount(const std::string& raw_word) const; // get how many times a word appears in the table
    
    // these functions return a vector of the data in hash table
    std::vector<std::list<WordCount>> getOpenHashTable() const; // deep copy open hash table, keeps chains
    std::vector<WordCount> getAllWordsUnsorted() const; //  unsorted words, unchains data
    std::vector<WordCount> getAllWordsSortedDescending() const; // desecending by word count, unchains data
    std::vector<WordCount> getAllWordsSortedAscending() const; // ascending by word count, unchains data
    void fillAllWords(std::vector<WordCount>& outWords) const; // helper function that fills word-count pairs from hash table, unchains data
    
    // display the most or least frequent n words
    void displayMostFrequent(int n) const;
    void displayLeastFrequent(int n) const;

    // gets the most or least frequent n words
    std::vector<WordCount> getMostFrequent(int n) const;
    std::vector<WordCount> getLeastFrequent(int n) const;

    // Sorting function & helpers  |  sort by word counts
    void insertionSort(std::vector<WordCount>& vec, int low, int high, bool descending) const;
    int partition(std::vector<WordCount>& vec, int low, int high, bool descending) const;
    void quickSortHybrid(std::vector<WordCount>& vec, int low, int high, bool descending) const;
    void sortWordCountsDescending(std::vector<WordCount>& vec) const; // Sort from most to least frequent
    void sortWordCountsAscending(std::vector<WordCount>& vec) const; // Sort from least to most frequent

    // helper functions for inserting words | some modifications to functions from Functions.h
    inline void clean_word(std::string& word) const;
    inline void split_and_clean(const std::string& word, std::vector<std::string>& vec);
};

// constructor
OpenHashTable::OpenHashTable(int s) : size(s) {
    open_hash_table.resize(size);
}

// Reads and inserts words until "vii"
void OpenHashTable::readUntilVII(std::ifstream& inFile) {
    std::string word;
    while (inFile >> word) {
        std::vector<std::string> words;
        split_and_clean(word, words);
        for (std::string w : words) {
            clean_word(w);
            if (w == "vii") {
                return;
            }

            insert(w);
        }
    }
}

// Insert a word (or increment if already exists) in hash table
void OpenHashTable::insert(const std::string& raw_word) {
    std::string word = raw_word;
    clean_word(word);
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
int OpenHashTable::getWordCount(const std::string& raw_word) const {
    std::string word = raw_word;
    clean_word(word);
    int index = hash(word, size);
    for (const auto& wc : open_hash_table[index]) {
        if (wc.word == word) {
            return wc.count;
        }
    }
    return 0;
}

// Returns a deep copy of internal hash table
std::vector<std::list<WordCount>> OpenHashTable::getOpenHashTable() const {
    std::vector<std::list<WordCount>> copy = open_hash_table;
    return copy;
}

// Returns all word-count pairs unsorted, unchains words
std::vector<WordCount> OpenHashTable::getAllWordsUnsorted() const {
    std::vector<WordCount> words;
    fillAllWords(words);
    return words;
}

// Returns all word-count pairs sorted in descending order, unchains words
std::vector<WordCount> OpenHashTable::getAllWordsSortedDescending() const {
    std::vector<WordCount> words;
    fillAllWords(words);
    sortWordCountsDescending(words);
    return words;
}

// Returns all word-count pairs sorted in ascending order, unchains words
std::vector<WordCount> OpenHashTable::getAllWordsSortedAscending() const {
    std::vector<WordCount> words;
    fillAllWords(words);
    sortWordCountsAscending(words);
    return words;
}

// Helper function that fills parameter word-count pairs, unchains words
void OpenHashTable::fillAllWords(std::vector<WordCount>& outWords) const {
    for (const auto& chain : open_hash_table) {
        for (const auto& wc : chain) {
            outWords.push_back(wc);
        }
    }
}

// prints n most frequent words
void OpenHashTable::displayMostFrequent(int n) const {
    std::vector<WordCount> words;
    fillAllWords(words);
    sortWordCountsDescending(words);
    for (int i = 0; i < n && i < (int)words.size(); ++i) {
        std::cout << words[i].word << ": " << words[i].count << '\n';
    }
}

// prints n least frequent words
void OpenHashTable::displayLeastFrequent(int n) const {
    std::vector<WordCount> words;
    fillAllWords(words);
    sortWordCountsAscending(words);
    for (int i = 0; i < n && i < (int)words.size(); ++i) {
        std::cout << words[i].word << ": " << words[i].count << '\n';
    }
}

// gets n most frequent words
std::vector<WordCount> OpenHashTable::getMostFrequent(int n) const {
    std::vector<WordCount> words;
    fillAllWords(words);
    sortWordCountsDescending(words);
    if ((int)words.size() > n) {
        words.resize(n);
    }
    return words;
}

// gets n least frequent words
std::vector<WordCount> OpenHashTable::getLeastFrequent(int n) const {
    std::vector<WordCount> words;
    fillAllWords(words);
    sortWordCountsAscending(words);
    if ((int)words.size() > n) {
        words.resize(n);
    }

    return words;
}

// insertion sort for quickSortHybrid
void OpenHashTable::insertionSort(std::vector<WordCount>& vec, int low, int high, bool descending) const {
    for (int i = low + 1; i <= high; ++i) {
        WordCount key = vec[i];
        int j = i - 1;
        while (j >= low && ((descending ? vec[j].count < key.count : vec[j].count > key.count) || (vec[j].count == key.count && vec[j].word > key.word))) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

// Quicksort partition using middle element as pivot
int OpenHashTable::partition(std::vector<WordCount>& vec, int low, int high, bool descending) const {
    int mid = low + (high - low) / 2;
    WordCount pivot = vec[mid];
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
void OpenHashTable::quickSortHybrid(std::vector<WordCount>& vec, int low, int high, bool descending) const {
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
void OpenHashTable::sortWordCountsDescending(std::vector<WordCount>& vec) const {
    if (!vec.empty()) {
        quickSortHybrid(vec, 0, static_cast<int>(vec.size() - 1), true);
    }
}

// Sort from least to most frequent
void OpenHashTable::sortWordCountsAscending(std::vector<WordCount>& vec) const {
    if (!vec.empty()) {
        quickSortHybrid(vec, 0, static_cast<int>(vec.size() - 1), false);
    }
}

// convert to lowercase, also removes leading & trailing non-letter characters
inline void OpenHashTable::clean_word(std::string& word) const {
    // convert to lowercase
    for (size_t i = 0; i < word.length(); ++i) {
        if (isalpha(word[i])) {
            word[i] = std::tolower(static_cast<unsigned char>(word[i]));
        }
    }

    // find index of first alphabetic character
    size_t start = 0;
    while (start < word.length() && !std::isalpha(word[start])) {
        ++start;
    }
    // find the index of last character
    size_t end = word.length();
    while (end > start && !std::isalpha(word[end - 1])) {
        --end;
    }
    word = word.substr(start, end - start);
}

// splits & cleans punctuation, numbers, or any non-letter character. Perserves hyphens in middle of words
inline void OpenHashTable::split_and_clean(const std::string& word, std::vector<std::string>& vec) {
    std::string current;
    for (size_t i = 0; i < word.length(); ++i) {
        char c = tolower(word[i]);
        if (isalpha(c)) {
            current += c; // build one letter at a time
        } 
        else if (c == '-') {
            // Keep a hyphen only if it's between two letters
            if (i > 0 && i < word.length() - 1 && isalpha(word[i - 1]) && isalpha(word[i + 1])) {
                current += '-';
            } 
            else if (!current.empty()) {
                vec.push_back(current); 
                current.clear();
            }
        } 
        else {
            // Any other punctuation/seperators, disregard them and push word
            if (!current.empty()) {
                vec.push_back(current);
                current.clear();
            }
        }
    }
    // push last word if loop ended while a word exists in current
    if (!current.empty()) {
        vec.push_back(current);
    }
}
