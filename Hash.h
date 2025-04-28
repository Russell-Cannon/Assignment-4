#pragma once
#include <string>

static int hash(const std::string& word, int size) {
    int n; // Hash value
    int h = 1;
    int d = 256; // d is the number of characters in the input alphabet 
    // The value of h would be "pow(d, M-1)%q"
    for (int i = 0; i < word.size() - 1; i++)
        h = (h * d) % size;

    for (int i = 0; i < word.size(); i++) {
        n = (d * n + word[i]) % size;
    }
    return n;
}