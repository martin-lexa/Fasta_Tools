#include <iostream>

#include "Sequence.h"

using namespace std;

// Constructors
Sequence::Sequence(SequenceType i_sequenceType, vector<Acid *> &i_sequenceAcids)
    : FastaFileContent(ContentType::Sequence),
      m_sequenceType(i_sequenceType),
      m_sequenceAcids(i_sequenceAcids)
{
}

Sequence::Sequence(const Sequence &i_src) // copy c'tor
    : FastaFileContent(i_src)
{
    *this = i_src;
}

// Destructor
Sequence::~Sequence() {}

// Operators
Sequence &Sequence::operator=(const Sequence &i_src) // assignment operator
{
    this->m_contentType = i_src.m_contentType;
    this->m_sequenceType = i_src.m_sequenceType;
    this->m_sequenceAcids = i_src.m_sequenceAcids;
}

// setter
void Sequence::setSequenceType(const SequenceType i_sequenceType) { m_sequenceType = i_sequenceType; }
void Sequence::setSequenceAcids(const vector<Acid *> i_sequenceAcids) { m_sequenceAcids = i_sequenceAcids; }

// getter
const Sequence::SequenceType Sequence::getSequenceType() const { return m_sequenceType; }
const vector<Acid *> Sequence::getSequenceAcids() const { return m_sequenceAcids; }

// interface functions
void Sequence::print(ostream &os) const
{
    for (auto acid : m_sequenceAcids)
        cout << acid->getOneLetterName();
}
string Sequence::asString() const
{
    string sequenceAsString;
    for (auto acid : m_sequenceAcids)
    {
        sequenceAsString.push_back(acid->getOneLetterName());
    }
    return sequenceAsString;
}