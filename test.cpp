#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    cout << "test" << endl;

    struct AcidInfo
    {
        string longName;
        string threeLetterName;
        char oneLetterName;
        float molecularMass;
    };
    vector<AcidInfo> standardAcidInfos;

    ifstream inputFile("StandardAcids");
    string line;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string value;
        vector<string> values;
        while (getline(iss, value, ','))
        {
            values.push_back(value);
        }
        AcidInfo newAcidInfo = {values[0], values[1], values[2][0], stof(values[3])};
        standardAcidInfos.push_back(newAcidInfo);
    }

    inputFile.close();

    for (AcidInfo info : standardAcidInfos)
    {
        cout << info.longName << " " << info.threeLetterName << " " << info.oneLetterName << " " << info.molecularMass << endl;
    }

    return 0;
}