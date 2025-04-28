#pragma once
#include <string>

class HashTable {
protected:
    void clean(std::string& _word) 
    {
        // It’s important to note that capitalization should not matter (i.e., “Watson” and “watson” should be counted as the same word)
        for (int i = 0; i < _word.size(); i++) {
            _word[i] = tolower(_word[i]);
            // but hyphenation is critical, and double hyphens “–” should be discarded.
            // TODO
        }
    }
};
