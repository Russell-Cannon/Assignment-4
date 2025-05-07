#include "LinearProbing.h"

int debug = 0;

LinearProbing::LinearProbing() : total_nanoseconds(0) {
    arr = new WordPair [size];
}
LinearProbing::LinearProbing(std::istream& in) : total_nanoseconds(0) {
    arr = new WordPair [size];
    read(in);
}
LinearProbing::LinearProbing(std::vector<WordPair>& in) : total_nanoseconds(0) {
    arr = new WordPair [size];
    read(in);
}
LinearProbing::~LinearProbing() {
    delete [] arr;
}

void LinearProbing::read(std::istream& in) {
    std::string word;
    while (in >> word) {
        auto time_start = std::chrono::high_resolution_clock::now();
        for (std::string w : clean_and_split(word)) { //Usually just one, sometimes two
            addElement(WordPair(w, 1));
        }
        auto time_stop = std::chrono::high_resolution_clock::now();
        auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_stop - time_start);
        total_nanoseconds += time_duration;
    }
}

void LinearProbing::readUntil(std::istream& in, std::string end) {
    clean(end);
    std::string word;
    std::vector<std::string> words;
    while (in >> word) {
        auto time_start = std::chrono::high_resolution_clock::now();
        words = clean_and_split(word); //Usually just one, sometimes two
        for (std::string w : words) { 
            if (w == end)
                return;
                
            addElement(WordPair(w, 1));
        }
        auto time_stop = std::chrono::high_resolution_clock::now();
        auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_stop - time_start);
        total_nanoseconds += time_duration;

        words.clear();
    }
}

void LinearProbing::read(std::vector<WordPair>& in) {
    auto time_start = std::chrono::high_resolution_clock::now();
    for (WordPair pair : in) {
        addElement(pair);
    }
    auto time_stop = std::chrono::high_resolution_clock::now();
    auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_stop - time_start);
    total_nanoseconds += time_duration;
}

std::chrono::nanoseconds LinearProbing::getTotalNanoseconds() { 
    return total_nanoseconds;
}

void LinearProbing::output(std::ostream& out) {
    for (int i = 0; i < size; i++) {
        if (!arr[i].empty) {
            out << arr[i].word << " (" << arr[i].count << ")\n";
        }
    }
}

void LinearProbing::printStats(std::ostream& out) {
    out << "Size of hashtable: " << size << '\n';
    out << "Number of words stored: " << occupancy << '\n';
    out << "Load size (lambda): " << (double)occupancy/size << '\n';

    int maxClusterSize = 0, minClusterSize = 255, sumClusterSize = 0, numClusters = 0;
    bool inCluster = false;
    int currentClusterSize = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].empty && inCluster) { //just left cluster
            sumClusterSize += currentClusterSize;
            numClusters++;
            if (maxClusterSize < currentClusterSize) maxClusterSize = currentClusterSize;
            if (minClusterSize > currentClusterSize) minClusterSize = currentClusterSize;

            currentClusterSize = 0;
            inCluster = false;
        }
        inCluster = !arr[i].empty;
        if (inCluster)
            currentClusterSize++;
    }

    out << "Largest cluster: " << maxClusterSize << '\n';
    out << "Smallest cluster: " << minClusterSize << '\n';
    out << "Average cluster: " << (double)sumClusterSize/numClusters << '\n';
    out << "Total Runtime in Nanoseconds: " << total_nanoseconds.count() << '\n';
}

std::vector<WordPair> LinearProbing::getMostFrequent(int K) {
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

std::vector<WordPair> LinearProbing::getLeastFrequent(int K) {
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

void LinearProbing::addElement(WordPair pair) {
    if (4*occupancy/size >= 3)
        resize();

    int index = hash(pair.word, size);
    for (int i = 1; !arr[index].empty && arr[index].word != pair.word; i++) {
        index = (index + i*i) % size;
    }
    if (arr[index].empty) { //Does not already exist
        arr[index].word = pair.word;
        arr[index].empty = false;
        occupancy++; //had to declare new space
    }
    arr[index].count += pair.count; //Does exist
    if (debug) std::cout << pair.word << " (" << arr[index].count << ")\n";
}

void LinearProbing::resize() {
    if (debug) std::cout << "Resizing.\n";
    WordPair* newArr = new WordPair[size*2];
    
    //rehash
    for (int i = 0; i < size; i++) {
        if (!arr[i].empty) {
            int index = hash(arr[i].word, size*2);
            while (!newArr[index].empty) {
                index = (index + 1) % (size*2);
            }
            
            newArr[index] = arr[i];
        }
    }
    
    delete [] arr;
    arr = newArr;
    size *= 2;
}

void LinearProbing::addInsertionTime(std::chrono::nanoseconds ns) {
    total_nanoseconds += ns;
}