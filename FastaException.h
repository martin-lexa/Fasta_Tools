#pragma once

#include <string>

using namespace std;

class FastaException : public exception
{
public:
    FastaException(const string &i_strErrorText);

    const string &getMessage() const;

private:
    string m_strErrorText;
};