#include <cctype>
#include <string>
#include <iostream>

#pragma once

class WordPair {
public:
    std::string word = "";
    int count = 0;
    bool empty = true;

    WordPair(std::string _first, int _second) : word(_first), count(_second) {}
    WordPair() {}

    friend std::ostream& operator<<(std::ostream& out, const WordPair& pair);
};

std::ostream& operator<<(std::ostream& out, const WordPair& pair) {
    return out << pair.word << ": " << pair.count;
}

//Overrides for priority queue
struct Less { bool operator()(const WordPair& lhs, const WordPair& rhs) {
    if (lhs.count == rhs.count) return lhs.word < rhs.word;
    return lhs.count > rhs.count;
} };
struct Greater { bool operator()(const WordPair& lhs, const WordPair& rhs) {
    if (lhs.count == rhs.count) return lhs.word > rhs.word;
    return lhs.count < rhs.count;
} };

