#pragma once

#include <vector>
#include <string>

using namespace std;

class FastaFileContent
{
public:
    enum class ContentType : char
    {
        Header,
        Sequence,
        Comment
    };

protected:
    // Constructors
    FastaFileContent(ContentType i_contentType);

    FastaFileContent() = default;

    FastaFileContent(const FastaFileContent &i_src); // copy c'tor

    // Destructor
    ~FastaFileContent();

    // Assignment Operator
    FastaFileContent &operator=(const FastaFileContent &i_src);

public:
    // Static Access
    // static const vector<FastaFileContent *> &getAllFastaContent();

    // Operators
    bool operator==(const FastaFileContent &i_rhs) const;
    bool operator!=(const FastaFileContent &i_rhs) const;

    // setter
    void setContentType(const ContentType);

    // getter
    ContentType getContentType() const;

    // interface functions
    virtual void print(ostream &os) const = 0;
    virtual string asString() const = 0;

    friend std::ostream &operator<<(std::ostream &os, FastaFileContent const &data);

protected:
    // static vector<FastaFileContent *> sm_allContent;

    ContentType m_contentType;
};
