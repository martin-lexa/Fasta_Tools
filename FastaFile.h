#pragma once

class FastaFileContent
{
};

class Header : public FastaFileContent
{
};

class Comment : public FastaFileContent
{
};

class Sequence : public FastaFileContent
{
};

class ProteinSequence : public Sequence
{
};

class NucleicAcidSequence : public Sequence
{
public:
    enum class NucleicAcidSequenceType
    {
        DNA,
        RNA
    };

private:
    NucleicAcidSequenceType nucleicAcidSequenceType;
};

class DNA_Sequence : public NucleicAcidSequence
{
public:
    enum class DNA_Bases // initialized with powers of 2 to enable bitwise OR ( | operator ) linking
    {
        A = 1,
        C = 2,
        G = 4,
        T = 8
    };

private:
    NucleicAcidSequenceType nucleicAcidSequenceType = NucleicAcidSequenceType::DNA;
};

class RNA_Sequence : public NucleicAcidSequence
{
public:
    enum class DNA_Bases
    {
        A = 1,
        C = 2,
        G = 4,
        U = 8
    };

private:
    NucleicAcidSequenceType nucleicAcidSequenceType = NucleicAcidSequenceType::RNA;
};

class FastaFile
{
public:
    // Constructor
    FastaFile(Header &i_header, Sequence &i_sequence);
    FastaFile(Header &i_header, Sequence &i_sequence, Comment &i_comment);

    FastaFile(const FastaFile &i_src);

    // Destructor
    ~FastaFile();

    // Operators
    FastaFile &operator=(const FastaFile &i_src);
    bool operator==(const FastaFile &i_rhs) const; // not in cpp

    // setter
    void setHeader(const Header &i_header);
    void setSequence(const Sequence &i_sequence);
    void setComment(const Comment &i_comment);

    // getter
    const Header &getHeader();
    const Sequence &getSequence();
    const Comment *getComment();

private:
    Header m_header;
    Sequence m_sequence;
    Comment m_comment;
};