#include "FastaFileContent.h"
#include "FastaException.h"

using namespace std;

// Constructors
FastaFileContent::FastaFileContent(ContentType i_contentType)
    : m_contentType(i_contentType)
{
    // sm_allContent.push_back(this);
}

FastaFileContent::FastaFileContent(const FastaFileContent &i_src)
{
    *this = i_src;
} // copy c'tor

// Destructor
FastaFileContent::~FastaFileContent() {}

// Assignment Operator
FastaFileContent &FastaFileContent::operator=(const FastaFileContent &i_src)
{
    this->m_contentType = i_src.m_contentType;
    return *this;
}

// Static Access
/*const vector<FastaFileContent *> &FastaFileContent::getAllFastaContent()
{
    return sm_allContent;
}*/

// Operators
bool FastaFileContent::operator==(const FastaFileContent &i_rhs) const
{
    return i_rhs.asString() == this->asString();
}
bool FastaFileContent::operator!=(const FastaFileContent &i_rhs) const
{
    return i_rhs.asString() != this->asString();
}

// setter
void FastaFileContent::setContentType(const ContentType i_contentType) { m_contentType = i_contentType; }

// getter
FastaFileContent::ContentType FastaFileContent::getContentType() const { return m_contentType; }

// interface functions
std::ostream &operator<<(std::ostream &os, FastaFileContent const &data)
{
    data.print(os);
    return os;
}