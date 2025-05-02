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
    friend bool operator<(const WordPair& left, const WordPair& right);
    friend bool operator>(const WordPair& left, const WordPair& right);
    friend bool operator==(const WordPair& left, const WordPair& right);
};

std::ostream& operator<<(std::ostream& out, const WordPair& pair) {
    return out << pair.word << ": " << pair.count;
}
bool operator<(const WordPair& left, const WordPair& right) {
    if (left.count == right.count) return left.word < right.word;
    return left.count > right.count;
}
bool operator>(const WordPair& left, const WordPair& right) {
    if (left.count == right.count) return left.word > right.word;
    return left.count < right.count;
}
bool operator==(const WordPair& left, const WordPair& right) {
    return left.count == right.count;
}

//Overrides for priority queue
struct Less { bool operator()(const WordPair& lhs, const WordPair& rhs) {
    return lhs < rhs;
} };
struct Greater { bool operator()(const WordPair& lhs, const WordPair& rhs) {
    return lhs > rhs;
} };

