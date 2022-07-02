#include "FastaFile.h"
#include "AminoAcid.h"
#include "NucleicAcid.h"
#include "FastaException.h"

#include <iostream>

int main()
{
    try
    {
        /* code */
    }
    catch (const FastaException &e)
    {
        std::cerr << e.getMessage() << '\n';
    }

    return 0;
}