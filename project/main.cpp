#include "Functions.h"
#include "LinearProbing.h"
#include "OpenHashing.h"
#include "WordPair.h"
#include "Rabin.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

int main() {
    std::ifstream in("A Scandal In Bohemia.txt");
    int user;
    std::string text;
    std::string temptext;
    int row;
    std::string key[10000] = {}; //I think this is causing errors to prevent run from working

    if (!in.is_open()) {
        std::cerr << "Failed to open input file.\n";
        return 1;
    }

    // Works I through VI should be stored using open hashing (separate chaining)
    OpenHashing open;
    open.readUntil(in, "VII");

    // Works VII to XII should be stored using Linear Probing.
    LinearProbing linear;
    linear.readUntil(in, "IX"); //read up until we hit Chapter 9.

    std::cout << "Would you like to find words in 'The Adventure of the Engineer’s Thumb'?" << std::endl;
    std::cout << "0: no, end program..." << std::endl << "1: yes, pattern match..." << std::endl;
    std::cin >> user;
    if (user == 0)
    {
        std::cout << "skipping program...";
        return 0;
    }
    else if (user == 1)
    {
        std::cout << "up to 8 searches per run, use '@@@' to state the end of your string if under 8 words to search.";
        std::cout << "Please state all your keys you want to search for: ";
        for(int i = 0; i < sizeof(key); i++)
        {
            std::string tempkey;
            std::cin >> tempkey;
            key[i] = tempkey;
        }
        for (int i = 0; i <= sizeof(key); i++)
        {
            std::getline(std::cin, key[i], ' ');
            if(key[i] == "@@@")
            {
                std::cerr << "Break out character detected, exiting" << std::endl;
                break;
            }

            //while(in != "X. THE ADVENTURE OF THE NOBLE BACHELOR") essentially, if we see "X. THE ADVENTURE OF THE NOBLE BACHELOR", stop reading
            //{
                while(std::getline(in, text))
                {
                    text += temptext + "\n";
                    Rabin(text, key[i], row); //obtain which row you are on and pass that into rabin, 
                }
            //}
        }
    }



    //As the program starts processing work IX “The Adventure of the Engineer’s Thumb”, it should prompt the user for search key
    //display the position of each key’s occurrence in the text
    //Rabin-Karp pattern matching algorithm and Horner’s rule for the rolling hash should be utilized for this purpose

    linear.read(in); //read until end
    
    // Once the data is processed, the program should display and record to a file a list of word occurrences from highest to lowest vice versa of the 80 most and least repeated words (and their count)
    const int N = 80;
    std::vector<WordPair> highest = combineVectors(linear.getMostFrequent(N), open.getMostFrequent(N));
    std::vector<WordPair> lowest = combineVectors(linear.getLeastFrequent(N), open.getLeastFrequent(N));
    
    std::ofstream mostOut("frequent.log");
    std::ofstream leastOut("rare.log");

    //Create another hash table to combine the two
    LinearProbing highestCombined(highest);
    highest = highestCombined.getMostFrequent(N);
    for (int i = 0; i < N; i++) mostOut << (i+1) << ". " << highest[i] << '\n';

    LinearProbing lowestCombined(lowest);
    lowest = lowestCombined.getLeastFrequent(N);
    for (int i = 0; i < N; i++) leastOut << (i+1) << ". " << lowest[i] << '\n';

    std::ofstream stats("stats.log");
    stats << "Total sentences: " << sentence_counter << '\n';
    stats << "Most common word: '" << highest[0].word << "'\n";
    stats << "Least common word: '" << lowest[0].word << "'\n";

    stats << "\nOpen Chaining:\n";
    open.printChainStats(stats);
    stats << "\nLinear Probing:\n";
    linear.printStats(stats);

    // can use getters from classes to get the total runtime
    std::chrono::nanoseconds total_time = open.getTotalNanoseconds() + linear.getTotalNanoseconds();
    std::cout << "Total time for open and linear: " << total_time.count() << '\n';

    stats.close();
    mostOut.close();
    leastOut.close();

    return 0;
}

/*
    auto tot_start = std::chrono::high_resolution_clock::now();
    auto tot_stop = std::chrono::high_resolution_clock::now();
    auto tot_time = std::chrono::duration_cast<std::chrono::nanoseconds>(tot_stop - tot_start);
    std::cout << "Final time: " << tot_time.count() << " seconds!" << std::endl;
*/
