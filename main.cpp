#include "FastaFile.h"
#include "FastaFileContent.h"
#include "SequenceElement.h"
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