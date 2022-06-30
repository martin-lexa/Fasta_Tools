#include "FastaException.h"

using namespace std;

FastaException::FastaException(const string &i_strErrorText)
    : exception(),
      m_strErrorText(i_strErrorText)
{
}

const string &FastaException::getMessage() const
{
    return m_strErrorText;
}