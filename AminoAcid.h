#pragma once

#include "Acid.h"

using namespace std;

class AminoAcid : public Acid
{
public:
    // static access
    static AminoAcid *getStandardAminoAcid(char i_oneLetterName);

    // Constructors
    AminoAcid(char i_oneLetterName, string &i_longName);

    AminoAcid(const AminoAcid &i_src); // copy c'tor

    // Destructor
    ~AminoAcid();

    // Operators
    AminoAcid &operator=(const AminoAcid &i_src); // assignment operator

    // setter
    void setThreeLetterName(const string &i_threeLetterName);
    void setMolecularMass(float i_molecularMass);

    // getter
    const string &getThreeLetterName() const;
    float getMolecularMass() const;

    // interface functions
    virtual void print() const;

private:
    static void initStandardAminoAcids(const string &standardAminoAcidsFile);
    static vector<AminoAcid *> sm_standardAminoAcids;

    string m_threeLetterName;
    float m_molecularMass;
};
