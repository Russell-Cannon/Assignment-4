/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#include <chrono>
#include <iostream>
#include <string>
#include "../Open Hashing/Functions.h"
using namespace std;

int search(string, string, int);
bool Las_vegas(string, string, int);
int Wordplace(int, string);
/* 
For when we add all these togeather, replace the name main with this:

int Rabin(int row)
{
    string txt = "how much wood could a wood chuck chuck if a wood chuck could chuck wood";
    string pat = "wood";
    int q = INT_MAX;
    int word_count;

    clean(txt);
    clean(pat);

    word_count = search(pat, txt, q);
    if(amount > 0 )
    {
    cout << " Pattern found 
     " << endl;
    }
    cout << "There are a total of " << word_count << " in the txt that match" << endl;
    return 0;

    Then modify the search to this search(string pat, string txt, int q, int row);
}
*/
int main()
{
    string txt = "how much wood could a wood chuck chuck if a wood chuck could chuck wood";
    string pat = "wood";
    int q = INT_MAX;
    int word_count;

    clean(txt);
    clean(pat);

    word_count = search(pat, txt, q);
    cout << "There are a total of " << word_count << " in the txt that match" << endl;
    return 0;
}

// Search the pat string in the txt string
int search(string pat, string txt, int q)
{
    int M = pat.size();
    int N = txt.size();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
    int d = 256; // d is the number of characters in the input alphabet
    int amount = 0;

    /* start the clock for run time of both Rabin Carp and Las Vegas check */
    auto tot_start = std::chrono::high_resolution_clock::now();

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
    {
        h = (h * d) % q;
    }

    /* Calculate hash values of pattern and first window of text */
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    /* Slide the pattern over text one by one */
    for (i = 0; i <= N - M; i++)
    {

        if (p == t)
        {

            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    cerr << "ERR: pattern broken" << endl;
                    break;
                }
            }

            if (j == M)
            {
                if (Las_vegas(pat, txt, i) == true)
                {
                    amount++;
                    auto tot_stop = std::chrono::high_resolution_clock::now();
                    auto tot_time = std::chrono::duration_cast<std::chrono::nanoseconds>(tot_stop - tot_start);
                    cout << "Line " << i /* will fix this in a sec*/ << " in IX found your word!" << endl;
                    cout << "------------------------------------" << endl;
                    cout << "Word found " << Wordplace(i, txt) << " words into the sentence" << endl;
                    printf("\n");

                    cout << "\"" << txt << "\" " << endl;
                    for(int o = 0;  o < i+1; o++)
                    {
                        cout << " ";
                    }
                    for(int v = 0; v < pat.size(); v++)
                    {
                        cout << "^";
                    }
                    printf("\n");
                    std::cout << "Rabin Carp time taken: " << tot_time.count() << " nanoseconds!" << std::endl;      
                }
                else
                {
                    auto tot_stop = std::chrono::high_resolution_clock::now();
                    auto tot_time = std::chrono::duration_cast<std::chrono::nanoseconds>(tot_stop - tot_start);
                    cout << "Pattern denied by Las Vegas check" << endl;

                    std::cout << "Rabin Carp time: " << tot_time.count() << " nanoseconds!" << std::endl;
                }
            }
        }
        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
            {
                t = (t + q);
            }
        }
    }
    if(amount == 0)
    {
        cout << "No patterns found" << endl;
        auto tot_stop = std::chrono::high_resolution_clock::now();
        auto tot_time = std::chrono::duration_cast<std::chrono::nanoseconds>(tot_stop - tot_start);
        std::cout << "Time elapsed: " << tot_time.count() << " nanoseconds!" << std::endl;
    }
    cout << "------------------------------------" << endl;
    return amount;
}

bool Las_vegas(string pat, string txt, int i)
{
    bool veg;
    for(int j = 0; j < pat.size(); j++)
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

int Wordplace(int index, string txt)
{
    int spacecount = 1; // to account for the 0th word
    for(int i = 0; i < index; i++)
    {
        if(txt[i] == ' ')
        {
            spacecount++;
        }
    }
    return spacecount;
}

// This is code is contributed by rathbhupendra
/*
    auto tot_start = std::chrono::high_resolution_clock::now();
    auto tot_stop = std::chrono::high_resolution_clock::now();
    auto tot_time = std::chrono::duration_cast<std::chrono::nanoseconds>(tot_stop - tot_start);
    std::cout << "Final time: " << tot_time.count() << " seconds!" << std::endl;
*/