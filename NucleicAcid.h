#pragma once

#include "Acid.h"

using namespace std;

class NucleicAcid : public Acid
{
public:
    // static access
    static NucleicAcid *getStandardNucleicAcid(char i_oneLetterName);

    // Constructors
    NucleicAcid(char i_oneLetterName, string i_longName);

    NucleicAcid(const NucleicAcid &i_src); // copy c'tor

    // Destructor
    ~NucleicAcid();

    // Operators
    NucleicAcid &operator=(const NucleicAcid &i_src); // assignment operator
    bool operator==(const NucleicAcid &i_rhs) const;

    // interface functions
    virtual void print() const;

private:
    static void initStandardNucleicAcids(const string &standardNucleicAcidsFile);
    static vector<NucleicAcid *> sm_standardNucleicAcids;
};