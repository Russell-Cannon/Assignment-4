#pragma once
#include <iostream>
#include <string>
#include <queue>
#include "Functions.h"
#include "WordPair.h"

class LinearProbing {
public:
    LinearProbing(std::istream& in) {
        arr = new WordPair [size];

        Read(in);
    }

    void Read(std::istream& in) {
        std::string word;
        while (in >> word) {
            std::vector<std::string> words;
            clean_and_split(word, words);

            for (std::string w : words) { //Usually just one, sometimes two
                if (occupancy*2 >= size)
                    resize();

                int index = hash(w, size);
                while (!arr[index].empty && arr[index].word != w) {
                    index = (index + 1) % size;
                }
                if (arr[index].empty) {
                    arr[index].word = w;
                    arr[index].empty = false;
                    occupancy++; //had to declare new space
                }
                arr[index].count++;
                if (debug) std::cout << w << " (" << arr[index].count << ")\n";
            }

        }
    }

    void Output(std::ostream& out) {
        for (int i = 0; i < size; i++) {
            if (!arr[i].empty) {
                out << arr[i].word << " (" << arr[i].count << ")\n";
            }
        }
    }

    WordPair* SortAscending(int K) {
        std::priority_queue<WordPair, std::vector<WordPair>, Greater> heap;
        for (int i = 0; i < size; i++) {
            if (!arr[i].empty)
                heap.push(arr[i]);
        }

        WordPair* output = new WordPair [K];
        int heapSize = heap.size();
        for (int i = 0; i < K && i < heapSize; i++) {
            output[i] = heap.top();
            heap.pop();
        }
        return output;
    }
    WordPair* SortDescending(int K) {
        std::priority_queue<WordPair, std::vector<WordPair>, Less> heap;
        for (int i = 0; i < size; i++) {
            if (!arr[i].empty)
                heap.push(arr[i]);
        }

        WordPair* output = new WordPair [K];
        int heapSize = heap.size();
        for (int i = 0; i < K && i < heapSize; i++) {
            output[i] = heap.top();
            heap.pop();
        }
        return output;
    }

private:
    int size = 64, occupancy = 0;
    WordPair* arr = nullptr;

    void resize() {
        if (debug) std::cout << "Resizing.\n";
        int oldSize = size;
        size *= 2;
        WordPair* newArr = new WordPair[size];

        //rehash
        for (int i = 0; i < oldSize; i++) {
            if (!arr[i].empty) {
                int index = hash(arr[i].word, size);
                while (!newArr[index].empty) {
                    index = (index + 1) % size;
                }
                
                newArr[index] = arr[i];
            }
        }
        
        delete [] arr;
        arr = newArr;
    }
};
