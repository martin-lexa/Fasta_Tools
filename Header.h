#pragma once

#include "FastaFileContent.h"

using namespace std;

class Header : public FastaFileContent
{
public:
    // Constructors
    Header(string &i_sequenceID, string &i_content);
    Header() = default;

    Header(const Header &i_src); // copy c'tor

    // Destructor
    ~Header();

    // Operators
    Header &operator=(const Header &i_src); // assignment operator

    // setter
    void setSequenceID(const string &i_sequenceID);
    void setContent(const string &i_content);

    // getter
    const string &getSequenceID() const;
    const string &getContent() const;

    // interface functions
    virtual void print(ostream &os) const override;
    virtual string asString() const override;

private:
    string m_content;
    string m_sequenceID;
};