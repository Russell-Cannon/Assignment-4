#include "WordPair.h"

WordPair::WordPair(std::string _first, int _second) : word(_first), count(_second) {}
WordPair::WordPair() {}
    
std::ostream& operator<<(std::ostream& out, const WordPair& pair) {
    return out << pair.word << ": " << pair.count;
}
bool operator<(const WordPair& left, const WordPair& right) {
    if (left.count == right.count) return left.word < right.word;
    return left.count > right.count;
}
bool operator>(const WordPair& left, const WordPair& right) {
    if (left.count == right.count) return left.word > right.word;
    return left.count < right.count;
}
bool operator==(const WordPair& left, const WordPair& right) {
    return left.count == right.count;
}

bool Less::operator()(const WordPair& lhs, const WordPair& rhs) {
    return lhs < rhs;
} 
bool Greater::operator()(const WordPair& lhs, const WordPair& rhs) {
    return lhs > rhs;
} 
