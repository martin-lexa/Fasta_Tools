#include <iostream>
#include <string>

#include "SequenceElement.h"

using namespace std;

// TEMPPPPPP
string fileName = "StandardAcids";

vector<AminoAcid *> AminoAcid::sm_standardAcids;
map<char, AminoAcid *> AminoAcid::sm_allAcids;

AminoAcid *AminoAcid::getStandardAcid(char i_oneLetterName)
{
    initStandardAcids(fileName); // todo

    for (auto *pAcid : sm_standardAcids)
        if (pAcid->getOneLetterName() == i_oneLetterName)
            return pAcid;

    // error
}

void AminoAcid::initStandardAcids(string &standardAcidsFile)
{
    struct AcidInfo
    {
        string longName;
        string threeLetterName;
        char oneLetterName;
        float molecularMass;
    };
    vector<AcidInfo> standardAcidInfos;
}

const map<char, AminoAcid *> &AminoAcid::getAllAcids()
{
    return sm_allAcids;
}

AminoAcid::AminoAcid(char i_oneLetterName)
    : m_oneLetterName(i_oneLetterName)
{
    if (sm_allAcids.find(i_oneLetterName) != sm_allAcids.end())
        ; // FEHLER !
    sm_allAcids[i_oneLetterName] = this;
}

AminoAcid::AminoAcid(const AminoAcid &i_src) { *this = i_src; } // copy c'tor

// Destructor
AminoAcid::~AminoAcid()
{
    auto iter = sm_allAcids.find(m_oneLetterName);
    if (iter != sm_allAcids.end())
        sm_allAcids.erase(iter);
}

// Operators
AminoAcid &AminoAcid::operator=(const AminoAcid &i_src) // assignment operator
{
    this->m_oneLetterName = i_src.m_oneLetterName;
    // todo?
    return *this;
}
bool AminoAcid::operator==(const AminoAcid &i_rhs) const // not in cpp
{
}

// setter
void AminoAcid::setLongName(const string &i_longName) { m_longName = i_longName; }
void AminoAcid::setThreeLetterName(const string &i_threeLetterName) { m_threeLetterName = i_threeLetterName; }
void AminoAcid::setOneLetterName(char i_oneLetterName) { m_oneLetterName = i_oneLetterName; }
void AminoAcid::setMolecularMass(float i_molecularMass) { m_molecularMass = i_molecularMass; }

// getter
const string &AminoAcid::getLongName() const { return m_longName; }
const string &AminoAcid::getThreeLetterName() const { return m_threeLetterName; }
char AminoAcid::getOneLetterName() const { return m_oneLetterName; }
float AminoAcid::getMolecularMass() const { return m_molecularMass; }

// interface functions
void AminoAcid::print() const
{
    cout << "Amino Acid " << m_longName << ", Molecular Mass: " << m_molecularMass << endl;
}
