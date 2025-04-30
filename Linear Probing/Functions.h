#pragma once
#include <cctype>
#include <string>
#include <vector>

#define debug 0

static int hash(const std::string& word, int size) {
    int n = 0; // Hash value
    int h = 1;
    int d = 256; // d is the number of characters in the input alphabet 
    // The value of h would be "pow(d, M-1)%q"
    for (int i = 0; i < (int)word.size() - 1; i++)
        h = (h * d) % size;

    for (int i = 0; i < (int)word.size(); i++)
        n = (d * n + word[i]) % size;
    
    return abs(n);
}

static void clean(std::string& word) 
{
    // It’s important to note that capitalization should not matter (i.e., “Watson” and “watson” should be counted as the same word)
    int size = word.size();
    for (int i = 0; i < size; i++) {
        if (std::isalpha(word[i])) {
            word[i] = tolower(word[i]);
        } else {
            // but hyphenation is critical, and double hyphens “–” should be discarded.
            if (word[i] == '-') { //atleast one hyphen
                if (i + 1 < size && word[i+1] == '-') { //if next character is also hyphen
                    word[i] = ' ';
                    word[i + 1] = ' ';
                } continue; //keep single hyphens
            }
            if (word[i] == '\'' && i + 1 < size && isalpha(word[i + 1])) //if apostrophe and room and next letter is character: keep for possessives
                continue;

            word[i] = ' '; //Scrap all other punctuation
        }
    }
    int i;
    for (i = size - 1; i >= 0; i--) { //Read from back
        if (word[i] != ' ')
            break; //break on first letter
    }

    word = word.substr(0, i + 1);
    size = word.length();

    for (i = 0; i < size; i++) { //Read from front
        if (word[i] != ' ')
            break;
    }

    word = word.substr(i);
}

static void clean_and_split(std::string word, std::vector<std::string>& arr) {
    clean(word);
    int size = word.length();
    for (int i = 0; i < size; i++) {
        if (word[i] == ' ') {
            int new_size = size - i - 1;
            if (new_size > 0) { //recurse on later half
                clean_and_split(word.substr(i+1), arr);
            }
            //Truncate
            size = i;
            break;
        }
    }

    if (size > 0) {
        word = word.substr(0, size);
        arr.push_back(word);
    }
}

