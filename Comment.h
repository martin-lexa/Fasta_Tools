#pragma once

#include "FastaFileContent.h"

using namespace std;

class Comment : public FastaFileContent
{
public:
    // Constructors
    Comment(string &i_content);

    Comment();

    Comment(const Comment &i_src); // copy c'tor

    // Destructor
    ~Comment();

    // Operators
    Comment &operator=(const Comment &i_src); // assignment operator

    // setter
    void setContent(const string &i_content);

    // getter
    const string &getContent() const;

    // interface functions
    virtual void print(ostream &os) const override;
    virtual string asString() const override;

private:
    string m_content;
};