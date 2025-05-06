#include "OpenHashing.h"

// constructor
OpenHashing::OpenHashing() : size(64), occupancy(0), total_nanoseconds(0) {
    open_hash_table = new std::list<WordPair> [size];
}

OpenHashing::~OpenHashing() { // delete hash table
    delete [] open_hash_table;
}

// Reads and inserts words until "vii"
void OpenHashing::readUntil(std::ifstream& inFile, std::string delimiter) {
    clean(delimiter);
    std::string word;
    while (inFile >> word) {
        std::vector<std::string> words;
        auto time_start = std::chrono::high_resolution_clock::now();
        clean_and_split(word, words);
        for (std::string w : words) {
            clean(w); // question, do we need this since we called clean_and_split() before which already calls clean() internally?
            if (w == delimiter) {
                return;
            }

            insert(w);
        }
        auto time_stop = std::chrono::high_resolution_clock::now();
        auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_stop - time_start);
        total_nanoseconds += time_duration;
    }
}

std::chrono::nanoseconds OpenHashing::getTotalNanoseconds() {
    return total_nanoseconds;
}

// Insert a word (or increment if already exists) in hash table
void OpenHashing::insert(const std::string& raw_word) {
    if (10*occupancy/size > 9)
        resize(); //Y. Daniel Yiang recommends a lambda under 0.9 for separate chaining

    std::string word = raw_word;
    clean(word);
    if (word.empty()) {
        return;
    }
    int index = hash(word, size);
    for (auto& wc : open_hash_table[index]) {
        if (wc.word == word) { 
            wc.count++; 
            return; 
        }
    }
    open_hash_table[index].push_front({word, 1}); // chain word to list
    occupancy++; //if we made a new element in the list
}

//Double the size of the hash_table.
void OpenHashing::resize() {
    std::list<WordPair>* new_table = new std::list<WordPair>[size*2];

    for (int i = 0; i < size; i++) {
        for (WordPair pair : open_hash_table[i]) {
            new_table[hash(pair.word, size*2)].push_front(pair);
        }
    }

    delete [] open_hash_table;
    open_hash_table = new_table;
    size *= 2;
}

// Gets how many time a word appears (word count)
int OpenHashing::getWordCount(const std::string& raw_word) const {
    std::string word = raw_word;
    clean(word);
    int index = hash(word, size);
    for (const auto& wc : open_hash_table[index]) {
        if (wc.word == word) {
            return wc.count;
        }
    }
    return 0;
}

 // Returns the average chainlength in the table
void OpenHashing::printChainStats(std::ostream& out) const {
    int max = open_hash_table[0].size(), min = max;
    int numNonZero = 0, sumNonZero = 0;
    
    for (int i = 0; i < size; i++) {
        int n = open_hash_table[i].size();
        if (n != 0) {
            numNonZero++;
            sumNonZero += n;
        }
        if (max < n) max = n;
        if (min > n) min = n;
    }

    out << "Number of lists: " << size << '\n';
    out << "Number of words stored: " << occupancy << '\n';
    out << "Load Size (Lambda): " << (double)occupancy/size << "\n";
    out << "Maximum Chain Length: " << max << "\n";
    out << "Minimum Chain Length: " << min << "\n";
    out << "Average Chain Length (excluding 0): " << (double) sumNonZero / numNonZero << '\n';
    out << "Total Runtime in Nanoseconds: " << total_nanoseconds.count() << '\n';
}

// Returns all word-count pairs sorted in descending order, unchains words
std::vector<WordPair> OpenHashing::getAllWordsSortedDescending() const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsDescending(words);
    return words;
}

// Returns all word-count pairs sorted in ascending order, unchains words
std::vector<WordPair> OpenHashing::getAllWordsSortedAscending() const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsAscending(words);
    return words;
}

// Helper function that fills parameter word-count pairs, unchains words
void OpenHashing::fillAllWords(std::vector<WordPair>& outWords) const {
    for (int i = 0; i < size; i++) {
        for (const auto& wc : open_hash_table[i]) {
            outWords.push_back(wc);
        }
    }
}


// gets n most frequent words
std::vector<WordPair> OpenHashing::getMostFrequent(int n) const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsDescending(words);
    if ((int)words.size() > n) {
        words.resize(n);
    }
    return words;
}

// gets n least frequent words
std::vector<WordPair> OpenHashing::getLeastFrequent(int n) const {
    std::vector<WordPair> words;
    fillAllWords(words);
    sortWordPairsAscending(words);
    if ((int)words.size() > n) {
        words.resize(n);
    }

    return words;
}

// insertion sort for quickSortHybrid
void OpenHashing::insertionSort(std::vector<WordPair>& vec, int low, int high, bool descending) const {
    for (int i = low + 1; i <= high; ++i) {
        WordPair key = vec[i];
        int j = i - 1;
        while (j >= low && ((descending ? vec[j].count < key.count : vec[j].count > key.count) || (vec[j].count == key.count && vec[j].word > key.word))) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

// Quicksort partition using middle element as pivot
int OpenHashing::partition(std::vector<WordPair>& vec, int low, int high, bool descending) const {
    int mid = low + (high - low) / 2;
    WordPair pivot = vec[mid];
    std::swap(vec[mid], vec[high]);
    int i = low;
    for (int j = low; j < high; ++j) {
        if ((descending ? vec[j] > pivot : vec[j] < pivot) || (vec[j] == pivot && vec[j].word < pivot.word)) {
            std::swap(vec[i], vec[j]);
            ++i;
        }
    }
    std::swap(vec[i], vec[high]);
    return i;
}

// Quicksort that switches to insertion sort for small sub vectors of size 20 or less
void OpenHashing::quickSortHybrid(std::vector<WordPair>& vec, int low, int high, bool descending) const {
    const int INSERTION_THRESHOLD = 20;

    if (low < high) {
        if (high - low + 1 <= INSERTION_THRESHOLD) {
            insertionSort(vec, low, high, descending);
        } else {
            int pivotIndex = partition(vec, low, high, descending);
            quickSortHybrid(vec, low, pivotIndex - 1, descending);
            quickSortHybrid(vec, pivotIndex + 1, high, descending);
        }
    }
}

// Sort from most to least frequent
void OpenHashing::sortWordPairsDescending(std::vector<WordPair>& vec) const {
    if (!vec.empty()) {
        quickSortHybrid(vec, 0, static_cast<int>(vec.size() - 1), true);
    }
}

// Sort from least to most frequent
void OpenHashing::sortWordPairsAscending(std::vector<WordPair>& vec) const {
    if (!vec.empty()) {
        quickSortHybrid(vec, 0, static_cast<int>(vec.size() - 1), false);
    }
}
