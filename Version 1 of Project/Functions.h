#pragma once
#include "WordPair.h"
#include <cctype>
#include <string>
#include <vector>
#include <chrono>

extern int sentence_counter;

void checkForSentence(const std::string &raw_word);
int charToIndex(const char c);
int hash(const std::string& word, int size);
void clean(std::string& word);
void clean_and_split(std::string word, std::vector<std::string>& arr);

std::vector<std::string> clean_and_split(std::string word);

// Having issues moving to implementation cpp, works if it remains in header
template <typename T>
std::vector<T> combineVectors(const std::vector<T>& left, const std::vector<T>& right) {
    std::vector<T> out = left;
    out.insert(out.end(), right.begin(), right.end());
    return out;
}

template <typename T>
void printVector(std::ostream &out, const std::vector<T>& arr) {
    for (int i = 0; i < (int)arr.size(); i++) {
        out << arr[i] << '\n';
    }
}

