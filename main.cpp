#include "FastaFile.h"
#include "Header.h"
#include "Sequence.h"
#include "Comment.h"
#include "Acid.h"
#include "AminoAcid.h"
#include "NucleicAcid.h"
#include "FastaException.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Sequence::SequenceType determineSequenceType(string &sequenceString)
{
    int nucleicAcidCodesAmount = 0, tAmount = 0, uAmount = 0;
    string nucleicAcidCodes = "ACGTURYKMSWBDHVN-";
    for (char c : sequenceString)
    {
        if (nucleicAcidCodes.find(toupper(c) != string::npos))
            nucleicAcidCodesAmount++;
        if (toupper(c) == 'T')
            tAmount++;
        if (toupper(c) == 'U')
            uAmount++;
    }
    if ((nucleicAcidCodesAmount / sequenceString.length()) < 0.9)
        return Sequence::SequenceType::Protein;
    else if (tAmount > uAmount)
        return Sequence::SequenceType::DNA;
    else
        return Sequence::SequenceType::RNA;
}

Sequence convertStringToSeq(string &sequenceString) // less readable function name because "convertStringToSequence" seems to be a standard function name
{
    if (!sequenceString.empty())
    {
        vector<Acid *> sequenceAcids;
        Sequence::SequenceType seqType = determineSequenceType(sequenceString);
        if (seqType == Sequence::SequenceType::Protein)
        {
            for (char c : sequenceString)
            {
                sequenceAcids.push_back(AminoAcid::getStandardAminoAcid(toupper(c)));
            }
        }
        else
        {
            for (char c : sequenceString)
            {
                sequenceAcids.push_back(NucleicAcid::getStandardNucleicAcid(toupper(c)));
            }
        }
        Sequence *newSequence = new Sequence(seqType, sequenceAcids);
        return *newSequence;
    }
}

FastaFile readFastFile(const string &filePath)
{

    FastaFile *fastaFile = new FastaFile();
    ifstream inputFile(filePath);
    string line, sequenceString = "";
    while (getline(inputFile, line))
    {

        if (line[0] == '>')
        {
            convertStringToSeq(sequenceString);
            string sequenceID = line.substr(1, line.find(" "));
            auto *newHeader = new Header(sequenceID, line);
            fastaFile->addOrChangeHeader(*newHeader, 0);
        }
        else if (line[0] == ';')
        {
            auto *newComment = new Comment(line);
            fastaFile->addOrChangeComment(*newComment, 0);
        }
        else
        {
            if (fastaFile->getLineWidth() == 0)
                fastaFile->setLineWidth(line.length());
            sequenceString += line;
        }
    }
    inputFile.close();
    return *fastaFile;
}

int main()
{
    try
    {
        FastaFile fastaFile = readFastFile("gene.fna");
        fastaFile.writeFastaFile("output.fasta");
    }
    catch (const FastaException &e)
    {
        std::cerr << e.getMessage() << '\n';
    }

    return 0;
}