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

void convertStringToSeq(string &sequenceString, FastaFile &fastaFile) // less readable function name because "convertStringToSequence" seems to be a standard function name
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
    fastaFile.addOrChangeSequence(*newSequence, 0);
}

string checkSeqString(string &sequenceString, FastaFile &fastaFile) // checks if there are Acids in the SequenceString so they can be converted into a Sequence-Object
{
    if (!sequenceString.empty())
    {
        convertStringToSeq(sequenceString, fastaFile);
        sequenceString = ""; // after conversion, string is set to empty, to take up next sequence
    }
    return sequenceString;
}

FastaFile *readFastFile(const string &filePath)
{

    FastaFile *fastaFile = new FastaFile();
    ifstream inputFile(filePath);
    string line, sequenceString = "";

    while (getline(inputFile, line))
    {
        if (line[0] == '>')
        {
            sequenceString = checkSeqString(sequenceString, *fastaFile);
            string sequenceID = line.substr(1, line.find(" "));
            auto *newHeader = new Header(sequenceID, line);
            fastaFile->addOrChangeHeader(*newHeader, 0);
        }
        else if (line[0] == ';')
        {
            sequenceString = checkSeqString(sequenceString, *fastaFile);
            auto *newComment = new Comment(line);
            fastaFile->addOrChangeComment(*newComment, 0);
        }
        else
        {
            if (fastaFile->getLineWidth() == 0)
            {
                cout << " Changing line width to: " << line.length() << endl; // Testing
                fastaFile->setLineWidth(line.length());
                cout << " Line width is now: " << fastaFile->getLineWidth() << endl; // Testing
            }
            sequenceString += line;
        }
    }
    sequenceString = checkSeqString(sequenceString, *fastaFile);
    inputFile.close();
    return fastaFile;
}

int main()
{
    try
    {
        FastaFile *fastaFile = readFastFile("gene_s.fna");
        cout << " Line width is now: " << fastaFile->getLineWidth() << endl; // Testing
        fastaFile->writeFastaFile("output.fasta");
    }
    catch (const FastaException &e)
    {
        std::cerr << e.getMessage() << '\n';
    }

    return 0;
}