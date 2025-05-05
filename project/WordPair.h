#include <cctype>
#include <string>
#include <iostream>

#pragma once

class WordPair {
public:
    std::string word = "";
    int count = 0;
    bool empty = true;

    WordPair(std::string _first, int _second);
    WordPair();

    friend std::ostream& operator<<(std::ostream& out, const WordPair& pair);
    friend bool operator<(const WordPair& left, const WordPair& right);
    friend bool operator>(const WordPair& left, const WordPair& right);
    friend bool operator==(const WordPair& left, const WordPair& right);
};

std::ostream& operator<<(std::ostream& out, const WordPair& pair);
bool operator<(const WordPair& left, const WordPair& right);
bool operator>(const WordPair& left, const WordPair& right);
bool operator==(const WordPair& left, const WordPair& right);

//Overrides for priority queue
struct Less { bool operator()(const WordPair& lhs, const WordPair& rhs); };
struct Greater { bool operator()(const WordPair& lhs, const WordPair& rhs); };

