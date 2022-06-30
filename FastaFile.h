#pragma once

#include "FastaFileContent.h"

class FastaFile
{
public:
    // Constructor (maybe make all const?)
    FastaFile(Header &i_header, Sequence &i_sequence);
    FastaFile(Header &i_header, Sequence &i_sequence, Comment &i_comment);

    FastaFile(const FastaFile &i_src); // copy c'tor

    // Destructor
    ~FastaFile();

    // Operators
    FastaFile &operator=(const FastaFile &i_src);  // assigment operator
    bool operator==(const FastaFile &i_rhs) const; // not in cpp

    // setter
    void setHeader(const Header &i_header);
    void setSequence(const Sequence &i_sequence);
    void setComment(const Comment &i_comment);

    // getter
    const Header &getHeader() const;
    const Sequence &getSequence() const;
    const Comment &getComment() const;

private:
    Header m_header;
    Sequence m_sequence;
    Comment m_comment;
};