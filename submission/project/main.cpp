#include "Functions.h"
#include "LinearProbing.h"
#include "OpenHashing.h"
#include "WordPair.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <cstring>
#include "Rabin.h"

std::vector<std::string> getUserSearchKeys();
void searchKeys(std::ifstream& in, LinearProbing& linear, std::string end);

int main(int argc, char *argv[]) {
    //Open input file
    char *inFileName, *outFileName;
    inFileName = new char[32];
    outFileName = new char[32];
    if (argc < 2) { //If the user forgot to provide an input filename and output filename
        std::cout << "Enter name of input file: ";
        std::cin >> inFileName;
        std::cout << "Enter name of output file: ";
        std::cin >> outFileName;
    } else if (argc == 2) { //Input but no output
        strcpy(inFileName, argv[1]); //Copy terminal argument to the filename
        std::cout << "Enter name of output file: ";
        std::cin >> outFileName;
    } else if (argc >= 3) { //Both
        strcpy(inFileName, argv[1]);
        strcpy(outFileName, argv[2]);
    }
    std::chrono::nanoseconds total_time = std::chrono::nanoseconds(0);
    std::ifstream in(inFileName);

    if (!in.is_open()) {
        std::cerr << "Failed to open input file '" << inFileName << "'.\n";
        return 1;
    }

    std::cout << "Welcome!\nPlease make a choice:\n0. Quit Program.\n1. Find search keys in Chapter IX and count words.\n2. Just count words in text.\nChoice: ";
    int choice = -1;
    bool findKeys = true;
    std::cin >> choice;
    switch (choice) {
        case 0:
            std::cout << "Thank you!\nShutting down...\n";
            return 0;
        case 1:
            break;
        case 2:
            findKeys = false;
            break;
        default:
            std::cout << "Invalid choice!\nShutting down...\n";
            return 1;
    }

    // Works I through VI should be stored using open hashing (separate chaining)
    OpenHashing open;
    open.readUntil(in, "VII");

    // Works VII to XII should be stored using Linear Probing.
    LinearProbing linear;
    linear.readUntil(in, "IX"); //read up until we hit Chapter 9.

    //As the program starts processing work IX “The Adventure of the Engineer’s Thumb”, it should prompt the user for search key
    //display the position of each key’s occurrence in the text
    if (findKeys)
        searchKeys(in, linear, "X"); // also stores chapter IX in linear probing

    linear.read(in); //read until end
    
    // Once the data is processed, the program should display and record to a file a list of word occurrences from highest to lowest vice versa of the 80 most and least repeated words (and their count)
    const int N = 80;
    std::vector<WordPair> highest = combineVectors(linear.getMostFrequent(2*N), open.getMostFrequent(2*N));
    std::vector<WordPair> lowest = combineVectors(linear.getLeastFrequent(2*N), open.getLeastFrequent(2*N));
    
    std::ofstream output(outFileName);

    //Create another hash table to combine the two
    LinearProbing highestCombined(highest);
    highest = highestCombined.getMostFrequent(N);
    
    LinearProbing lowestCombined(lowest);
    lowest = lowestCombined.getLeastFrequent(N);
    
    output << "Total sentences: " << sentence_counter << '\n';
    output << "Most common word: '" << highest[0].word << "'\n";
    output << "Least common word: '" << lowest[0].word << "'\n";
    // can use getters from classes to get the total runtime
    total_time += open.getTotalNanoseconds() + linear.getTotalNanoseconds();
    output << "Total time for open and linear: " << total_time.count() << '\n';
    
    output << "\nOpen Chaining:\n";
    open.printChainStats(output);
    output << "\nLinear Probing:\n";
    linear.printStats(output);

    output << '\n' << N << " most frequent words:\n";
    for (int i = 0; i < N; i++) output << (i+1) << ". " << highest[i] << '\n';

    output << '\n' << N << " least frequent words:\n";
    for (int i = 0; i < N; i++) output << (i+1) << ". " << lowest[i] << '\n';

    output.close();

    return 0;
}

std::vector<std::string> getUserSearchKeys() {
    std::vector<std::string> keys;
    std::cout << "Enter up to 8 search keys (type @@@ to stop adding keys):\n";
    while (keys.size() < 8) {
        std::string input;
        std::cin >> input;
        if (input == "@@@") {
            break;
        }
        keys.push_back(input);
    }
    return keys;
}

void searchKeys(std::ifstream& in, LinearProbing& linear, std::string end) {
    clean(end);

    // Get search keys from user
    std::vector<std::string> rawKeys = getUserSearchKeys();

    
    std::string chapterIX; // store chapter into a string
    std::string word;
    while (in >> word) {
        bool isEnd = false;
        auto t0 = std::chrono::high_resolution_clock::now(); // start time
        auto clean_word = clean_and_split(word);
        for (auto &w : clean_word) {
            if (w == end) { 
                isEnd = true; 
                break; 
            }
        }
        if (isEnd) {
            break;
        }
        // insert each cleaned word into the linear table
        for (auto &w : clean_word) {
            linear.addElement(WordPair(w, 1));
            // build the Chapter IX string
            chapterIX += w;
            chapterIX += ' ';
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0);
        linear.addInsertionTime(time_duration); // continue to calculate time of cleaning & inserting items to linear
    }
    

    // search chapterIX with the user search keys
    if (!rawKeys.empty()) {
        std::cout << "\n-- Search Results in Chapter IX --\n" << std::endl;
        for (auto key : rawKeys) {
            Rabin(chapterIX, key);
        }
    } // case user just input @@@
    else {
        std::cout << "No keys entered; skipped Chapter IX keys search.\n";
    }
}