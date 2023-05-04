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
#include <map>

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
    // insert empty comment if no comment exists, so my sloppy logic works
    if (fastaFile.getSequences().size() > fastaFile.getComments().size())
    {
        auto *newComment = new Comment();
        fastaFile.addOrChangeComment(*newComment, 0);
    }
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

FastaFile *readFastaFile(const string &filePath)
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
                fastaFile->setLineWidth(line.length());
            sequenceString += line;
        }
    }
    sequenceString = checkSeqString(sequenceString, *fastaFile);
    inputFile.close();
    return fastaFile;
}

void calculateGCContent(Sequence &sequence, int sequenceNumber)
/* Only works properly if sequence contains nothing but the 5 different nucleic acids.
A function that properly estimates GC-content for files with ambiguous codes (e.g. 'Y' for "C, T or G", 'D' for "not C" etc.)
isn't much harder to program, but rather a long function full of simple maths. */
{
    map<char, int> elementCounts;
    for (auto acid : sequence.getSequenceAcids())
    {
        char oneLetterName = acid->getOneLetterName();
        if (elementCounts.count(oneLetterName) == 0)
            elementCounts[oneLetterName] = 1;
        else
            elementCounts[oneLetterName]++;
    }
    cout << "Statistics for sequence number " << sequenceNumber << endl;
    for (pair<char, int> elementCount : elementCounts)
    {
        cout << elementCount.first << ": " << elementCount.second << endl;
    }
    cout << "GC-Content: " << float(float(elementCounts.at('G') + elementCounts.at('C')) / float(sequence.getSequenceAcids().size())) * 100 << "%" << endl;
}

void drawAAHistogram(Sequence &sequence, int sequenceNumber)
{
    map<Acid *, int> elementCounts;
    int numberOfElements = sequence.getSequenceAcids().size();
    for (auto acid : sequence.getSequenceAcids())
    {
        if (elementCounts.count(acid) == 0)
            elementCounts[acid] = 1;
        else
            elementCounts[acid]++;
    }
    cout << "Histogramm of amino acids of sequence number " << sequenceNumber << endl;
    for (pair<Acid *, int> elementCount : elementCounts)
    {
        Acid *acid = elementCount.first;
        cout << acid->getOneLetterName() << " (" << acid->getLongName() << "): " << elementCount.second << endl;
        int scaledBarLength;
        if (numberOfElements > 400)
            scaledBarLength = int(float((float)elementCount.second / (float)numberOfElements) * 100);
        else
            scaledBarLength = elementCount.second;
        for (int i = 0; i < scaledBarLength; i++)
            cout << "+";
        cout << endl;
    }
}

int main(int argc, char *argv[]) // FileName of FASTA-file to read can be given as argument
{
    string fastaFileName;
    if (argc == 2)
        fastaFileName = argv[1];
    else
        fastaFileName = "gene.fna";

    try
    {
        FastaFile *fastaFile = readFastaFile(fastaFileName);

        int sequenceNumber = 1;
        for (auto seq : fastaFile->getSequences())
        {
            if (seq->getSequenceType() == Sequence::SequenceType::DNA || seq->getSequenceType() == Sequence::SequenceType::RNA)
                calculateGCContent(*seq, sequenceNumber);
            else
                drawAAHistogram(*seq, sequenceNumber);
            sequenceNumber++;
        }

        fastaFile->writeFastaFile("output.fasta");
    }
    catch (const FastaException &e)
    {
        std::cerr << e.getMessage() << '\n';
    }

    return 0;
}