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
    nrMap["zero"] = 0;
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
    string regStrLine = "[0-9]|one|two|three|four|five|six|seven|eight|nine";
    regex const reg(regStrLine);
    const sregex_iterator end;

    int totalNr = 0;
    map<string, int> nrMap = setMap();

    while (getline(inputfile, line))
    {
        vector<string> matches;

        for (sregex_iterator i(line.begin(), line.end(), reg); i != end; i++)
        {
            string itemValue = i->str();
            if (nrMap[itemValue])
            {
                matches.push_back(to_string(nrMap[itemValue]));
            }
            else
            {
                matches.push_back(itemValue);
            }
        }

        cout << matches[0] << matches[matches.size() -1] << endl;
        string numberStr = matches[0] + matches[matches.size() - 1];

        totalNr += stoi(numberStr);
    }

    cout << totalNr << endl;
}