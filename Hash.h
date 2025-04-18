#pragma once

#include <iostream>
#include <fstream>
#include <string>

//Fix this once we know what a Hash even is

class Hash {
public:
    virtual int GetSentences();
    virtual std::ostream& CountAscending(std::istream& in);
    virtual std::ostream& CountDescending(std::istream& in);
    virtual void ReadUntil(std::string delimit);

protected:
    std::string GetWord(std::istream& in);

};
