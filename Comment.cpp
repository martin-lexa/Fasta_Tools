#include <iostream>

#include "Comment.h"

using namespace std;

// Constructors
Comment::Comment(std::string &i_content)
    : FastaFileContent(ContentType::Comment),
      m_content(i_content)
{
}

Comment::Comment()
    : FastaFileContent(ContentType::Comment),
      m_content("")
{
}

Comment::Comment(const Comment &i_src) // copy c'tor
    : FastaFileContent(i_src)
{
    *this = i_src;
}

// Destructor
Comment::~Comment() {}

// Operators
Comment &Comment::operator=(const Comment &i_src) // assignment operator
{
    this->m_content = i_src.m_content;
    this->m_contentType = i_src.m_contentType;
}

// setter
void Comment::setContent(const string &i_content) { m_content = i_content; }

// getter
const string &Comment::getContent() const { return m_content; }

// interface functions
void Comment::print(ostream &os) const { os << m_content; }
string Comment::asString() const { return m_content; }