#include <string>
#include <map>

#include "FastaFileContent.h"

// Constructors
FastaFileContent::FastaFileContent(ContentType contentType, string &i_content)
    : m_content(i_content)
{
}

FastaFileContent::FastaFileContent(const FastaFileContent &i_src) { *this = i_src; } // copy c'tor

// Destructor
FastaFileContent::~FastaFileContent() {}

// Assignment Operator
FastaFileContent &FastaFileContent::operator=(const FastaFileContent &i_src)
{
    this->m_contentType = i_src.m_contentType;
    this->m_content = i_src.m_content;
    return *this;
}

// Static Access
const map<string, FastaFileContent *> &FastaFileContent::getAllFastaContent()
{
    // TODO
}

// Operators
bool FastaFileContent::operator==(const FastaFileContent &i_rhs) const
{
    return i_rhs.m_content == m_content;
}
bool FastaFileContent::operator!=(const FastaFileContent &i_rhs) const
{
    return i_rhs.m_content != m_content;
}

// setter
void FastaFileContent::setContent(const string &i_content) { m_content = i_content; }

// getter
const string &FastaFileContent::getContent() const { return m_content; }

// interface functions
void FastaFileContent::print() const
{
}

/*
class Header : public FastaFileContent
{
};

class Sequence : public FastaFileContent
{
};

class Comment : public FastaFileContent
{
}; */