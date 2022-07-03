#include <iostream>
#include <fstream>
#include <sstream>

#include "AminoAcid.h"

vector<AminoAcid *> AminoAcid::sm_standardAminoAcids;

AminoAcid *AminoAcid::getStandardAminoAcid(char i_oneLetterName)
{
    initStandardAminoAcids();

    for (auto *pAcid : sm_standardAminoAcids)
        if (pAcid->getOneLetterName() == i_oneLetterName)
            return pAcid;

    throw FastaException(string("'") + i_oneLetterName + "' is not a known one letter code for amino acids.");
}

void AminoAcid::initStandardAminoAcids(const string &standardAminoAcidsFile = "StandardAminoAcids")
{
    if (sm_standardAminoAcids.empty())
    {
        struct AcidInfo
        {
            string longName;
            string threeLetterName;
            char oneLetterName;
            float molecularMass;
        };
        vector<AcidInfo> standardAminoAcidInfos;
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
            standardAminoAcidInfos.push_back(newAcidInfo);
        }
        inputFile.close();
        for (auto &acidInfo : standardAminoAcidInfos)
        {
            AminoAcid *pNewAcid = new AminoAcid(acidInfo.oneLetterName, acidInfo.longName);
            pNewAcid->setThreeLetterName(acidInfo.threeLetterName);
            pNewAcid->setMolecularMass(acidInfo.molecularMass);
            sm_standardAminoAcids.push_back(pNewAcid);
        }
    }
}

// C'tors
AminoAcid::AminoAcid(char i_oneLetterName, string &i_longName)
    : Acid(i_oneLetterName, i_longName)
{
}

AminoAcid::AminoAcid(const AminoAcid &i_src)
    : Acid(i_src)
{
    *this = i_src;
} // copy c'tor

// Destructor
AminoAcid::~AminoAcid()
{
}

// Operators
AminoAcid &AminoAcid::operator=(const AminoAcid &i_src) // assignment operator
{
    this->m_oneLetterName = i_src.m_oneLetterName;
    this->m_longName = i_src.m_longName;
    this->m_threeLetterName = i_src.m_threeLetterName;
    this->m_molecularMass = i_src.m_molecularMass;
    return *this;
}

// setter
void AminoAcid::setThreeLetterName(const string &i_threeLetterName) { m_threeLetterName = i_threeLetterName; }
void AminoAcid::setMolecularMass(float i_molecularMass) { m_molecularMass = i_molecularMass; }

// getter
const string &AminoAcid::getThreeLetterName() const { return m_threeLetterName; }
float AminoAcid::getMolecularMass() const { return m_molecularMass; }

// interface functions
void AminoAcid::print() const
{
    cout << "Amino Acid " << m_longName << ", Molecular Mass: " << m_molecularMass << endl;
}