#pragma once
#include "WordPair.h"
#include <cctype>
#include <string>
#include <vector>

#define debug 0

static int sentence_counter = 0;
inline void checkForSentence(const std::string &raw_word) {
    int back = raw_word.size() - 1;
    while (raw_word[back] == '\'' || raw_word[back] == '"')
        back--;

    if (raw_word[back] == '.' || raw_word[back] == '!' || raw_word[back] == '?') {
        ++sentence_counter;
    } 
}

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
        if (std::isalpha(word[i]) || std::isdigit(word[i])) {
            word[i] = tolower(word[i]);
        } else {
            // but hyphenation is critical, and double hyphens “–” should be discarded.
            if (word[i] == '-') { //atleast one hyphen
                if (i + 1 < size && word[i+1] == '-') { //if next character is also hyphen
                    word[i] = ' ';
                    word[i + 1] = ' ';
                } continue; //keep single hyphens
            }

            //keep contractions
            if (word[i] == '\'' && i + 2 < size && i > 0 && isalpha(word[i - 1]) && isalpha(word[i + 1]) && std::isalpha(word[i + 2])) //if apostrophe and room and next two characters are letters is one character: 
                continue;
            //keep possessives
            if (word[i] == '\'' && i + 2 == size && isalpha(word[i + 1])) //if apostrophe and room and next character is one letter: 
                continue;
            //Preserve apostrophes in the middle of a word (i.e., will-o'-the-wisps)
            if (word[i] == '\'' && i > 2 && i + 2 < size)
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
    checkForSentence(word); // check for punctuation before cleaning word
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

static std::vector<std::string> clean_and_split(std::string word) {
    std::vector<std::string> arr;
    clean_and_split(word, arr);
    return arr;
}

template <typename T>
static std::vector<T> combineVectors(const std::vector<T>& left, const std::vector<T>& right) {
    std::vector<T> out = left;
    out.insert(out.end(), right.begin(), right.end());
    return out;
}

template <typename T>
static void printVector(std::ostream &out, const std::vector<T>& arr) {
    for (int i = 0; i < (int)arr.size(); i++) {
        out << arr[i] << '\n';
    }
}

