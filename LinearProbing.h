#pragma once
#include <iostream>
#include <string>

class LinearProbing {
typedef std::pair<std::string, int> word_pair;
public:
    LinearProbing(std::istream& in) {
        arr = new word_pair [size];
        for (int i = 0; i < size; i++) arr[i] = empty; //Unoccupied

        Read(in);
    }

    void Read(std::istream& in) {
        std::string word;
        while (in >> word) {
            if (occupancy*2 >= size)
                resize();

            int index = hash(word);
            while (arr[index] != empty && arr[index].first != word) {
                index = (index + 1) % size;
            }
            if (arr[index] == empty) {
                arr[index].first = word;
                occupancy++; //had to declare new space
            }
            arr[index].second++;
            std::cout << word << " (" << arr[index].second << ")\n";
        }
    }

private:
    int size = 64, occupancy = 0;
    word_pair* arr = nullptr;
    word_pair empty = {"", 0};

    int hash(const std::string& word) {
        int n = 0;

        // for (char c : word) 
        //     n = n*31 + (tolower(c) - 'a');

        for (int i = 0; i < word.size(); i++) n += (word[i] - 'a')*(i+1);
        return n % size;
    }    
    void resize() {
        int oldSize = size;
        size *= 2;
        word_pair* newArr = new word_pair[size];
        for (int i = 0; i < size; i++) newArr[i] = empty;

        //rehash
        for (int i = 0; i < oldSize; i++) {
            if (arr[i] != empty) {
                int index = hash(arr[i].first);
                while (newArr[index] != empty) {
                    index = (index + 1) % size;
                }
                newArr[index] = arr[i];
            }
        }
        
        delete [] arr;
        arr = newArr;
    }
};
