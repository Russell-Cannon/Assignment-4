#include "Rabin.h"

void Rabin(const std::string& txt, std::string pat)
{
    const int q = 0b1111111111111111111111111111111;
    clean(pat); // clean user keys/patters
    
    // search for user keys. txt is already cleaned from building string
    Search(pat, txt, q);

}

void Search(const std::string& pat, const std::string& txt, int q)
{
    int M = pat.size();
    int N = txt.size();
    int patHash = 0;
    int txtHash = 0;
    int d = 256;
    int h = 1;
    if (M == 0 || N < M) {
        std::cout << "Pattern: \"" << pat << "\"\n" << "No possible matches (empty or longer than text).\n" << "===================================\n\n";
        return; 
      }

    // build word count mapping for each character
    std::vector<int> charToWordCount(N);
    int wordCount = 1;
    for (int i = 0; i < N; ++i) {
    charToWordCount[i] = wordCount;
    if (txt[i] == ' ') {
            ++wordCount;
        }
    }

    // The value of h would be "pow(d, M-1)%q"
    for (int i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    /* Calculate hash values of pattern and first window of text */
    for (int i = 0; i < M; ++i) {
        //Horner’s rule for the rolling hash should be utilized for this purpose
        patHash = (d * patHash + pat[i]) % q;
        txtHash = (d * txtHash + txt[i]) % q;
    }

     /* Slide the pattern over text one by one */
    std::vector<int> positions;
    auto time_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= N - M; ++i) {
    if (patHash == txtHash) {
    bool match = true;
    for (int j = 0; j < M; ++j) {
        if (txt[i + j] != pat[j]) {
            match = false;
            break;
        }
    }
    // if hashes match, then do a las vegas check
    if (match && Las_vegas(pat, txt, i)) {
        positions.push_back(charToWordCount[i]);
    }
    }
    // slide the hash forward
    if (i < N - M) {
        txtHash = (d * (txtHash - txt[i] * h) + txt[i + M]) % q;
        if (txtHash < 0){ 
            txtHash += q;
        }
    }
    }
    auto time_end = std::chrono::high_resolution_clock::now();
    auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();

    // print summary of search
    std::cout << "===========================================================\n";
    std::cout << "Pattern            : " << pat << "\n";
    std::cout << "Pattern length     : " << M << "\n";
    std::cout << "Total matches      : " << positions.size() << "\n";
    std::cout << "Word position in ch: ";

    if (positions.empty()) {
        std::cout << "no matches\n";
    
    } 
    // less than or equal to 20 matches, list all positions
    else if (positions.size() <= 20) {
        for (size_t k = 0; k < positions.size(); ++k) {
            std::cout << positions[k]
            << (k + 1 < positions.size() ? ", " : "\n");
        }
    } 
    // display first 10 & last 10
    else {
        // first 10
        for (size_t k = 0; k < 10; ++k) {
            std::cout << positions[k] << ", ";
        }
        std::cout << "…, ";
        // last 10
        for (size_t k = positions.size() - 10; k < positions.size(); ++k) {
            std::cout << positions[k]
            << (k + 1 < positions.size() ? ", " : "\n");
        }
    }
    std::cout << "Chapter length     : " << wordCount << " words\n";
    std::cout << "Elapsed time       : " << time_duration << " nanoseconds\n";
    std::cout << "=========================================================\n\n";
}

bool Las_vegas(std::string pat, std::string txt, int i)
{
    bool veg;
    for(size_t j = 0; j < pat.size(); j++)
    {    
        if(pat[j] == txt[i + j])
        {
            veg = true;
        }
    }
    if(veg == true)
    {
        return true;
    }
    return false;
}