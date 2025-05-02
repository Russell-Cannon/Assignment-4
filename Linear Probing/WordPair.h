#include <string>

#pragma once

class WordPair {
public:
    std::string word = "";
    int count = 0;
    bool empty = true;

    WordPair(std::string _first, int _second) : word(_first), count(_second) {}
    WordPair() {}
};

struct Less     { bool operator()(const WordPair& lhs, const WordPair& rhs) {return lhs.count > rhs.count;} };
struct Greater  { bool operator()(const WordPair& lhs, const WordPair& rhs) {return lhs.count < rhs.count;} };
