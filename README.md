# Notes
Libraries - Everything but STL algorithms
Works I-VI use open hashing (separate chaining)
Works VII-XII use linear probing
Read once, string-by-string
Display (and log) a list of words by their number of occurrences
    Display once, most to least
    Again, least to most
Clean words during input
    Capitalization doesn't matter
    keep single hyphens
    Discard double hyphens
Let the user search for words
    8 at a time (use '@@@' to mark queries that have less than 8 words)
Need to be able to display the number of sentences in the text
Report the time it takes for each task
All files need .h headers

# To Do
 - [x] Implement Open Hashing
 - [x] Implement linear probing
 - [x] Cleaning strings
 - [x] Change the hash function?
 - [x] Detect chapter headings and split input for open hashing and linear probing
 - [ ] Pattern matching
 - [ ] Report times
 - [x] Count sentences
   - Ignore '!'
   - Count '?'
   - Count '.'
 - [ ] Paper
   - [ ] Test with multiple hash functions
   - [ ] Test with different occupancy ratios

# Division
Russell - Combining open and linear hashing to project folder
Patrick - Count sentances
Ian - Rabin-Karp
