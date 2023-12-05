#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <map>

using namespace std;

map<string, int> setMap()
{
    map<string, int> nrMap;
    nrMap["one"] = 1;
    nrMap["two"] = 2;
    nrMap["three"] = 3;
    nrMap["four"] = 4;
    nrMap["five"] = 5;
    nrMap["six"] = 6;
    nrMap["seven"] = 7;
    nrMap["eight"] = 8;
    nrMap["nine"] = 9;

    return nrMap;
}

int main()
{
    ifstream inputfile("input.txt");

    if (!inputfile.is_open())
    {
        cout << "Could not open file.";
    }

    string line;
    string regStrLine = "([0-9])|(?=(one))|(?=(two))|(?=(three))|(?=(four))|(?=(five))|(?=(six))|(?=(seven))|(?=(eight))|(?=(nine))";
    regex const reg_exp(regStrLine);
    const sregex_iterator end;

    int totalNr = 0;
    map<string, int> nrMap = setMap();

    while (getline(inputfile, line))
    {
        vector<string> matches;

        for (sregex_iterator i(line.begin(), line.end(), reg_exp); i != end; ++i)
        {
            smatch regmatch = *i;
            if (regmatch.size())
            {
                for (size_t i = 1; i < regmatch.size(); ++i)
                {
                    if (regmatch[i].str().length())
                    {
                        string itemValue = regmatch[i].str();
                        // cout << "Value: " << itemValue << endl;
                        matches.push_back(itemValue);
                    }
                }
            }
        }

        for(int i = 0; i < matches.size(); ++i){
            string value = matches[i];
            if(nrMap[value]){
                matches[i] = to_string(nrMap[value]);
            }
            // cout << "Matches[" << i << "]: " << matches[i] << endl;
        }
        string numberString = matches[0] + matches[matches.size() - 1];
        totalNr += stoi(numberString);
    }

    cout << totalNr << endl;
}
