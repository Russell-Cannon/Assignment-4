#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Functions.h"
#include "WordPair.h"

class LinearProbing {
public:
    LinearProbing() {
        arr = new WordPair [size];
    }
    LinearProbing(std::istream& in) {
        arr = new WordPair [size];
        Read(in);
    }
    LinearProbing(std::vector<WordPair>& in) {
        arr = new WordPair [size];
        Read(in);
    }
    ~LinearProbing() {
        delete [] arr;
    }

    void Read(std::istream& in) {
        std::string word;
        while (in >> word) {
            for (std::string w : clean_and_split(word)) { //Usually just one, sometimes two
                addElement(WordPair(w, 1));
            }
        }
    }

    void ReadUntil(std::istream& in, std::string end) {
        clean(end);
        std::string word;
        while (in >> word) {
            for (std::string w : clean_and_split(word)) { //Usually just one, sometimes two
                if (w == end)
                    return;

                addElement(WordPair(w, 1));
            }
        }
    }

    void Read(std::vector<WordPair>& in) {
        for (WordPair pair : in) {
            addElement(pair);
        }
    }

    void Output(std::ostream& out) {
        for (int i = 0; i < size; i++) {
            if (!arr[i].empty) {
                out << arr[i].word << " (" << arr[i].count << ")\n";
            }
        }
    }

    std::vector<WordPair> SortAscending(int K) {
        std::priority_queue<WordPair, std::vector<WordPair>, Greater> heap;
        for (int i = 0; i < size; i++) {
            if (!arr[i].empty)
                heap.push(arr[i]);
        }

        std::vector<WordPair> output(K);
        int heapSize = heap.size();
        for (int i = 0; i < K && i < heapSize; i++) {
            output[i] = heap.top();
            heap.pop();
        }
        return output;
    }
    std::vector<WordPair> SortDescending(int K) {
        std::priority_queue<WordPair, std::vector<WordPair>, Less> heap;
        for (int i = 0; i < size; i++) {
            if (!arr[i].empty)
                heap.push(arr[i]);
        }

        std::vector<WordPair> output(K);
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

    void addElement(WordPair pair) {
        if (occupancy*2 >= size)
            resize();

        int index = hash(pair.word, size);
        while (!arr[index].empty && arr[index].word != pair.word) {
            index = (index + 1) % size;
        }
        if (arr[index].empty) { //Does not already exist
            arr[index].word = pair.word;
            arr[index].empty = false;
            occupancy++; //had to declare new space
        }
        arr[index].count += pair.count; //Does exist
        if (debug) std::cout << pair.word << " (" << arr[index].count << ")\n";
    }

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
