#include <iostream>
#include <fstream>
#include <sstream>

#include "Acid.h"

using namespace std;

map<string, Acid *> Acid::sm_allAcids;

const map<string, Acid *> &Acid::getAllAcids()
{
    return sm_allAcids;
}

// C'tors
Acid::Acid(char i_oneLetterName, string &i_longName)
    : m_oneLetterName(i_oneLetterName),
      m_longName(i_longName)
{
    if (sm_allAcids.find(i_longName) != sm_allAcids.end())
        throw FastaException(string("The code '") + i_oneLetterName + "' is already in use for (an) amino acid(s)");
    sm_allAcids[i_longName] = this;
}

Acid::Acid(const Acid &i_src) { *this = i_src; } // copy c'tor

// Destructor
Acid::~Acid()
{
    auto iter = sm_allAcids.find(m_longName);
    if (iter != sm_allAcids.end())
        sm_allAcids.erase(iter);
}

// Operators
Acid &Acid::operator=(const Acid &i_src) // assignment operator
{
    this->m_oneLetterName = i_src.m_oneLetterName;
    this->m_longName = i_src.m_longName;
    return *this;
}
bool Acid::operator==(const Acid &i_rhs) const
{
    return (i_rhs.m_oneLetterName == m_oneLetterName && i_rhs.m_longName == m_longName);
}
bool Acid::operator==(const std::string &i_rhs) const
{
    return i_rhs == m_longName;
}
bool Acid::operator!=(const Acid &i_rhs) const
{
    return (i_rhs.m_oneLetterName != m_oneLetterName || i_rhs.m_longName != m_longName);
}
bool Acid::operator!=(const std::string &i_rhs) const
{
    return i_rhs != m_longName;
}

// setter
void Acid::setLongName(const string &i_longName) { m_longName = i_longName; }
void Acid::setOneLetterName(char i_oneLetterName) { m_oneLetterName = i_oneLetterName; }

// getter
const string &Acid::getLongName() const { return m_longName; }
char Acid::getOneLetterName() const { return m_oneLetterName; }

// interface functions
void Acid::print() const
{
    cout << "Acid '" << m_oneLetterName << "': " << m_longName << endl;
}