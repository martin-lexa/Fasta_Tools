#include <iostream>
#include <fstream>
#include <sstream>

#include "NucleicAcid.h"

vector<NucleicAcid *> NucleicAcid::sm_standardNucleicAcids;

NucleicAcid *NucleicAcid::getStandardNucleicAcid(char i_oneLetterName)
{
    initStandardNucleicAcids();

    for (auto *pAcid : sm_standardNucleicAcids)
        if (pAcid->getOneLetterName() == i_oneLetterName)
            return pAcid;

    throw FastaException(string("'") + i_oneLetterName + "' is not a known one letter code for Nucleic acids.");
}

void NucleicAcid::initStandardNucleicAcids(const string &standardNucleicAcidsFile = "StandardNucleicAcids")
{
    if (sm_standardNucleicAcids.empty())
    {
        struct AcidInfo
        {
            string longName;
            string threeLetterName;
            char oneLetterName;
            float molecularMass;
        };
        vector<AcidInfo> standardNucleicAcidInfos;
        ifstream inputFile("StandardAcids");
        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string value;
            vector<string> values;
            while (getline(iss, value, ','))
            {
                values.push_back(value);
            }
            AcidInfo newAcidInfo = {values[0], values[1], values[2][0], stof(values[3])};
            standardNucleicAcidInfos.push_back(newAcidInfo);
        }
        inputFile.close();
        for (auto &acidInfo : standardNucleicAcidInfos)
        {
            NucleicAcid *pNewAcid = new NucleicAcid(acidInfo.oneLetterName, acidInfo.longName);
            sm_standardNucleicAcids.push_back(pNewAcid);
        }
    }
}

// C'tors
NucleicAcid::NucleicAcid(char i_oneLetterName, string i_longName)
    : Acid(i_oneLetterName, i_longName)
{
}

NucleicAcid::NucleicAcid(const NucleicAcid &i_src)
    : Acid(i_src)
{
    *this = i_src;
} // copy c'tor

// Destructor
NucleicAcid::~NucleicAcid()
{
}

// Operators
NucleicAcid &NucleicAcid::operator=(const NucleicAcid &i_src) // assignment operator
{
    this->m_oneLetterName = i_src.m_oneLetterName;
    // todo?
    return *this;
}

// interface functions
void NucleicAcid::print() const
{
    cout << "Nucleic Acid '" << m_oneLetterName << "': " << m_longName << endl;
}