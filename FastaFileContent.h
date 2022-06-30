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