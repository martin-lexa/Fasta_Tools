#pragma once

#include "FastaFileContent.h"
#include "AminoAcid.h"
#include "NucleicAcid.h"

using namespace std;

class Sequence : public FastaFileContent
{
public:
    enum class SequenceType : char
    {
        Protein,
        RNA,
        DNA
    };
    // Constructors
    Sequence(SequenceType i_sequenceType, vector<Acid *> &i_sequenceAcids);

    Sequence() = default;

    Sequence(const Sequence &i_src); // copy c'tor

    // Destructor
    ~Sequence();

    // Operators
    Sequence &operator=(const Sequence &i_src); // assignment operator

    // setter
    void setSequenceType(const SequenceType i_sequenceType);
    void setSequenceAcids(const vector<Acid *> i_sequenceAcids);

    // getter
    const SequenceType getSequenceType() const;
    const vector<Acid *> getSequenceAcids() const;

    // interface functions
    virtual void print(ostream &os) const override;
    virtual string asString() const override;

private:
    SequenceType m_sequenceType;
    vector<Acid *> m_sequenceAcids;
};