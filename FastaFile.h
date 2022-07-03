#pragma once

#include "Header.h"
#include "Sequence.h"
#include "Comment.h"

class FastaFile
{
public:
    // Constructor (maybe make all const?)
    FastaFile() = default;
    FastaFile(vector<Header *> &i_headers, vector<Sequence *> &i_sequences);
    FastaFile(vector<Header *> &i_headers, vector<Sequence *> &i_sequences, vector<Comment *> &i_comments);

    FastaFile(const FastaFile &i_src); // copy c'tor

    // Destructor
    ~FastaFile();

    // Operators
    FastaFile &operator=(const FastaFile &i_src); // assigment operator
    bool operator==(const FastaFile &i_rhs) const;
    bool operator!=(const FastaFile &i_rhs) const;

    // setter
    void setHeaders(const vector<Header *> &i_headers);
    void setSequences(const vector<Sequence *> &i_sequences);
    void setComments(const vector<Comment *> &i_commments);
    void setLineWidth(int i_lineWidth);

    void addOrChangeHeader(Header &i_header, int entryIndex); // entryIndex starts at 1 for the first entry, O pushes a new entry to the end of the FastaFile
    void addOrChangeSequence(Sequence &i_sequence, int entryIndex);
    void addOrChangeComment(Comment &i_comment, int entryIndex);

    // getter
    const Header &getHeader(int entryIndex) const;
    const Sequence &getSequence(int entryIndex) const;
    const Comment &getComment(int entryIndex) const;

    int getLineWidth() const;
    const vector<Header *> &getHeaders() const;
    const vector<Sequence *> &getSequences() const;
    const vector<Comment *> &getComments() const;

    // interface functions
    void writeFastaFile(const string &fileName) const;

private:
    int m_lineWidth;
    vector<Header *> m_headers;
    vector<Sequence *> m_sequences;
    vector<Comment *> m_comments;
};