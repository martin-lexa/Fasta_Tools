#include <iostream>

#include "FastaFile.h"

using namespace std;

/* class FastaFileContent
{
};

class Header : public FastaFileContent
{
};

class Sequence : public FastaFileContent
{
};

class Comment : public FastaFileContent
{
}; */

// FastaFile
Comment *emptyComment = nullptr; // --> comment will always have to be checked if nullptr
// Constructor
FastaFile::FastaFile(Header &i_header, Sequence &i_sequence)
    : FastaFile(i_header, i_sequence, *emptyComment)
{
}

FastaFile::FastaFile(Header &i_header, Sequence &i_sequence, Comment &i_comment)
    : m_header(i_header),
      m_sequence(i_sequence),
      m_comment(i_comment)
{
}

FastaFile::FastaFile(const FastaFile &i_src)
{
    *this = i_src;
}

// Destructor
FastaFile::~FastaFile()
{
    // might implement a question if FastaFile should be saved --> call writeFastaFile()
}

// Operators
FastaFile &FastaFile::operator=(const FastaFile &i_src)
{
    m_header = i_src.m_header;
    m_sequence = i_src.m_sequence;
    m_comment = i_src.m_comment; // might need to be a pointer? (because of nullpointer)

    return *this;
}

// overload ==operator for comparison between string and FastaFile-Objects (either whole Object or Header/Sequence/Comment-Header)
bool operator==(const string &i_lhs, const FastaFile &i_rhs)
{
}

bool operator==(const FastaFile &i_lhs, const string &i_rhs)
{
}

// setter
void FastaFile::setHeader(const Header &i_header) { m_header = i_header; }
void FastaFile::setSequence(const Sequence &i_sequence) { m_sequence = i_sequence; }
void FastaFile::setComment(const Comment &i_comment) { m_comment = i_comment; }

// getter
const Header &FastaFile::getHeader() { return m_header; }
const Sequence &FastaFile::getSequence() { return m_sequence; }
const Comment *FastaFile::getComment() { return &m_comment; }
