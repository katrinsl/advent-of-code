#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

using namespace std;

map<string, int> setMap(){
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
    ifstream inputfile("01_example_2.txt");

    if (!inputfile.is_open())
    {
        cout << "Could not open file.";
    }

    string line;

    string regStrLine = "|(\bone\b)|(\two\b)|(\bthree\b)|(\bfour\b)|(\bfive\b)|(\bsix\b)|(\bseven\b)|(\beight\b)|(\bnine\b)";
    regex const reg("([0-9])" + regStrLine);
    const sregex_token_iterator end;

    map<string, int> nrMap;
    nrMap = setMap();

    int totalNr = 0;

    while (getline(inputfile, line))
    {
        vector<string> matches;

        for (sregex_token_iterator i(line.cbegin(), line.cend(), reg, 1); i != end; i++)
        {
            matches.push_back(*i);
        }
        
        string firstNum = matches[0];
        string secondNum = matches[matches.size() - 1];

        if(!stoi(firstNum)){
            firstNum = nrMap[firstNum];
        }
        if(!stoi(secondNum)){
            secondNum = nrMap[secondNum];
        }

        string numberStr = firstNum + secondNum;

        totalNr += stoi(numberStr);
    }

    cout << totalNr << endl;
}