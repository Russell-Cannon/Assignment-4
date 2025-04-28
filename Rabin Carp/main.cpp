/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#include <bits/stdc++.h>
using namespace std;

// Search the pat string in the txt string
void search(string pat, string txt, int q)
{
    int M = pat.size();
    int N = txt.size();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
    int d = 256; // d is the number of characters in the input alphabet
    int amount = 0;
    // The value of h would be "pow(d, M-1)%q"

    for (i = 0; i < M - 1; i++)
    {
        h = (h * d) % q;
    }

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        cout << "-------------------" << endl;
        cout << "I: " << i+1 << endl;
        p = (d * p + pat[i]) % q;
        cout << "P: " << p << endl;
        t = (d * t + txt[i]) % q;
        cout << "T: " << p << endl;
    }
        cout << "-------------------" << endl;

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
        
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        if (p == t)
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    cout << "Found a pattern" << endl;
                    break;
                }
            }

            // if p == t and pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]

            if (j == M)
            {
                amount++;
                cout << "Pattern found at index: " << i << endl;
                cout << txt << endl;
                for(int o = 0;  o < i; o++)
                {
                    cout << " ";
                }
                for(int v = 0; v < pat.size(); v++)
                {
                    cout << "^";
                }
                cout << endl;
            }
        }

        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            // We might get negative value of t, converting
            // it to positive
            if (t < 0)
            {
                t = (t + q);
            }
        }
    }
    if(amount == 0)
    {
        cout << "No patterns found" << endl;
    }
}

/* Driver code */
int main()
{
    string txt = "How much wood could a wood chuck chuck if a wood chuck could chuck wood";
    string pat = "wood";

    // we mod to avoid overflowing of value but we should
    // take as big q as possible to avoid the collison
    int q = INT_MAX;
    // Function Call
    search(pat, txt, q);
    return 0;
}

// This is code is contributed by rathbhupendra