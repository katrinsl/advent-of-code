#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    ifstream inputfile("input.txt");

    if (!inputfile.is_open())
    {
        cout << "Could not open file.";
    }

    string line;
    string regStrLine = "|(\bone\b)|(\two\b)|(\bthree\b)|(\bfour\b)|(\bfive\b)|(\bsix\b)|(\bseven\b)|(\beight\b)|(\bnine\b)";
    regex const reg("([0-9])");
    const sregex_token_iterator end;

    int totalNr = 0;

    while (getline(inputfile, line))
    {
        vector<string> matches;

        for (sregex_token_iterator i(line.cbegin(), line.cend(), reg, 1); i != end; i++)
        {
            matches.push_back(*i);
        }
        string numberStr = matches[0] + matches[matches.size() - 1];

        totalNr += stoi(numberStr);
    }

    cout << totalNr << endl;
}