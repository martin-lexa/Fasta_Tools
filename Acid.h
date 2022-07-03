#pragma once

#include "FastaException.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class Acid
{
protected:
    // Constructors
    Acid(char i_oneLetterName, string &i_longName);

    Acid(const Acid &i_src); // copy c'tor

    // Destructor
    ~Acid();

    // Assignment Operator
    Acid &operator=(const Acid &i_src);

    // members variables
    static map<string, Acid *> sm_allAcids;

    string m_longName;
    char m_oneLetterName;

public:
    // Static Access
    static const map<string, Acid *> &getAllAcids();

    // Operators
    bool operator==(const Acid &i_rhs) const;
    bool operator==(const std::string &i_rhs) const;
    bool operator!=(const Acid &i_rhs) const;
    bool operator!=(const std::string &i_rhs) const;

    // setter
    void setLongName(const string &i_longName);
    void setOneLetterName(char i_oneLetterName);

    // getter
    const string &getLongName() const;
    char getOneLetterName() const;

    // interface functions
    virtual void print() const;
};
