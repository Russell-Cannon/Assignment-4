#pragma once
#include <iostream>
#include <string>
#include "Hash.h"

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

            int index = hash(word, size);
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
    int size = 128, occupancy = 0;
    word_pair* arr = nullptr;
    word_pair empty = {"", 0};

    void resize() {
        std::cout << "Resizing.\n";
        int oldSize = size;
        size *= 2;
        word_pair* newArr = new word_pair[size];
        for (int i = 0; i < size; i++) newArr[i] = empty;

        //rehash
        for (int i = 0; i < oldSize; i++) {
            if (arr[i] != empty) {
                int index = hash(arr[i].first, size);
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
