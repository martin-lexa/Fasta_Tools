#include <iostream>

#include "Header.h"

using namespace std;

// Constructors
Header::Header(string &i_sequenceID, string &i_content)
    : FastaFileContent(ContentType::Header),
      m_sequenceID(i_sequenceID),
      m_content(i_content)
{
}

Header::Header(const Header &i_src) // copy c'tor
    : FastaFileContent(i_src)
{
    *this = i_src;
}

// Destructor
Header::~Header() {}

// Operators
Header &Header::operator=(const Header &i_src) // assignment operator
{
    this->m_content = i_src.m_content;
    this->m_contentType = i_src.m_contentType;
    this->m_sequenceID = i_src.m_sequenceID;
}

// setter
void Header::setSequenceID(const string &i_sequenceID) { m_sequenceID = i_sequenceID; }
void Header::setContent(const string &i_content) { m_content = i_content; }

// getter
const string &Header::getSequenceID() const { return m_sequenceID; }
const string &Header::getContent() const { return m_content; }

// interface functions
void Header::print(ostream &os) const { cout << m_content; }
string Header::asString() const { return m_content; }