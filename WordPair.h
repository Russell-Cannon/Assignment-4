#include <string>

#pragma once

class WordPair {
public:
    std::string first = "";
    int second = 0;
    bool empty = true;

    WordPair(std::string _first, int _second) : first(_first), second(_second), empty(true) {}
    WordPair() {}
};
    
struct Less     { bool operator()(const WordPair& lhs, const WordPair& rhs) {return lhs.second > rhs.second;} };
struct Greater  { bool operator()(const WordPair& lhs, const WordPair& rhs) {return lhs.second < rhs.second;} };
