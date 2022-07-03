#include <fstream>

#include "FastaFile.h"

using namespace std;

// Constructors
FastaFile::FastaFile(vector<Header *> &i_headers, vector<Sequence *> &i_sequences)
    : FastaFile(i_headers, i_sequences, m_comments)
{
}

FastaFile::FastaFile(vector<Header *> &i_headers, vector<Sequence *> &i_sequences, vector<Comment *> &i_comments)
    : m_headers(i_headers),
      m_sequences(i_sequences),
      m_comments(i_comments)
{
}

// copy constructor
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
    m_headers = i_src.m_headers;
    m_sequences = i_src.m_sequences;
    m_comments = i_src.m_comments;

    return *this;
}

bool FastaFile::operator==(const FastaFile &i_rhs) const
{
    return (m_headers == i_rhs.m_headers && m_sequences == i_rhs.m_sequences && m_comments == i_rhs.m_comments);
}
bool FastaFile::operator!=(const FastaFile &i_rhs) const
{
    return (m_headers != i_rhs.m_headers || m_sequences != i_rhs.m_sequences || m_comments != i_rhs.m_comments);
}

/* overload ==operator for comparison between string and FastaFile-Objects (either whole Object or Header/Sequence/Comment-Header)
bool operator==(const string &i_lhs, const FastaFile &i_rhs)
{
}

bool operator==(const FastaFile &i_lhs, const string &i_rhs)
{
} */

// setter
void FastaFile::setHeaders(const vector<Header *> &i_headers) { m_headers = i_headers; }
void FastaFile::setSequences(const vector<Sequence *> &i_sequences) { m_sequences = i_sequences; }
void FastaFile::setComments(const vector<Comment *> &i_comments) { m_comments = i_comments; }
void FastaFile::setLineWidth(int i_lineWidth) { m_lineWidth = i_lineWidth; }

void FastaFile::addOrChangeHeader(Header &i_header, int entryIndex)
{
    if (entryIndex == 0)
    {
        m_headers.push_back(&i_header);
    }
    else
    {
        m_headers[entryIndex - 1] = &i_header;
    }
}
void FastaFile::addOrChangeSequence(Sequence &i_sequence, int entryIndex)
{
    if (entryIndex == 0)
    {
        m_sequences.push_back(&i_sequence);
    }
    else
    {
        m_sequences[entryIndex - 1] = &i_sequence;
    }
}
void FastaFile::addOrChangeComment(Comment &i_comment, int entryIndex)
{
    if (entryIndex == 0)
    {
        m_comments.push_back(&i_comment);
    }
    else
    {
        m_comments[entryIndex - 1] = &i_comment;
    }
}

// getter
const Header &FastaFile::getHeader(int entryIndex) const { return *m_headers[entryIndex]; }
const Sequence &FastaFile::getSequence(int entryIndex) const { return *m_sequences[entryIndex]; }
const Comment &FastaFile::getComment(int entryIndex) const { return *m_comments[entryIndex]; }

const int FastaFile::getLineWidth() const { return m_lineWidth; }
const vector<Header *> &FastaFile::getHeaders() const { return m_headers; }
const vector<Sequence *> &FastaFile::getSequences() const { return m_sequences; }
const vector<Comment *> &FastaFile::getComments() const { return m_comments; }

// interface functions
void FastaFile::writeFastaFile(const string &fileName) const
{
    ofstream outputFile;
    outputFile.open(fileName);
    int currentLineWidth = 0;
    for (int i = 0; i < m_sequences.size(); i++)
    {
        outputFile << *m_headers[i] << endl;
        for (auto acid : m_sequences[i]->getSequenceAcids())
        {
            outputFile << acid->getOneLetterName();
            currentLineWidth++;
            if (currentLineWidth == m_lineWidth)
                outputFile << endl;
        }
        if (!m_comments[i]->getContent().empty())
            outputFile << *m_comments[i] << endl;
    }
    outputFile.close();
}
