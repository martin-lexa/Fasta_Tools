#pragma once

#include <map>
#include <string>

class FastaFileContent
{
public:
    enum class ContentType
    {
        Header,
        Sequence,
        Commment
    };

protected:
    // Constructors
    FastaFileContent(ContentType contentType, string &i_content);

    FastaFileContent(const FastaFileContent &i_src); // copy c'tor

    // Destructor
    ~FastaFileContent();

    // Assignment Operator
    FastaFileContent &operator=(const FastaFileContent &i_src);

public:
    // Static Access
    static const map<string, FastaFileContent *> &getAllFastaContent();

    // Operators
    bool operator==(const FastaFileContent &i_rhs) const;
    bool operator!=(const FastaFileContent &i_rhs) const;

    // setter
    void setContent(const string &i_content);

    // getter
    const string &getContent() const;

    // interface functions
    virtual void print() const;

private:
    static map<string, FastaFileContent *> sm_allContent;

    ContentType m_contentType;
    string m_content;
};

/*
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
};*/