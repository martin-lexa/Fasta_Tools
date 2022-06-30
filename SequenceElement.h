#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

class SequenceElement
{
};

class AminoAcid : public SequenceElement
{
public:
    // static access
    static AminoAcid *getStandardAcid(char i_oneLetterName);

    static const map<char, AminoAcid *> &getAllAcids();

    // Constructors
    AminoAcid(char i_oneLetterName);

    AminoAcid(const AminoAcid &i_src); // copy c'tor

    // Destructor
    ~AminoAcid();

    // Operators
    AminoAcid &operator=(const AminoAcid &i_src);  // assignment operator
    bool operator==(const AminoAcid &i_rhs) const; // not in cpp

    // setter
    void setLongName(const string &i_longName);
    void setThreeLetterName(const string &i_threeLetterName);
    void setOneLetterName(char i_oneLetterName);
    void setMolecularMass(float i_molecularMass);

    // getter
    const string &getLongName() const;
    const string &getThreeLetterName() const;
    char getOneLetterName() const;
    float getMolecularMass() const;

    // interface functions
    void print() const;

private:
    static void initStandardAcids(string &standardAcidsFile);
    static vector<AminoAcid *> sm_standardAcids;
    static map<char, AminoAcid *> sm_allAcids;

    string m_longName;
    string m_threeLetterName;
    char m_oneLetterName;
    float m_molecularMass;
};

class Nucleotide : public SequenceElement
{
};