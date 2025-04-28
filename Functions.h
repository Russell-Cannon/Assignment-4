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

static void clean(std::string& _word) 
{
    // It’s important to note that capitalization should not matter (i.e., “Watson” and “watson” should be counted as the same word)
    for (int i = 0; i < _word.size(); i++) {
        _word[i] = tolower(_word[i]);
        // but hyphenation is critical, and double hyphens “–” should be discarded.
        // TODO
    }
}

