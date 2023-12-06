#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <map>

using namespace std;

int main()
{
    int MAX_RED = 12;
    int MAX_GREEN = 13;
    int MAX_BLUE = 14;

    regex const reg_exp("([0-9]+)\\:(.*)");
    regex const game_reg_exp("\\;");
    regex const color_set_reg_exp("([0-9]+)\\s(red|blue|green)");
    sregex_iterator end;
    sregex_token_iterator token_end;

    string exampleString = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    // Game id: value before the colon (1)
    // Each game set: split by the semi-colon (["3 blue, 4 red", "1 red, 2 green", ...])
    // Each color set: split by comma (map<string, int>, where map[stringValue] = nrOfCubes)

    ifstream inputfile("input.txt");

    if (!inputfile.is_open())
    {
        cout << "Could not open file.";
    }

    string line;

    int sumOfLegalGameIDs = 0;
    int sumOfPowers = 0;

    while (getline(inputfile, line))
    {
        string gameId;
        vector<string> gameSets;

        for (sregex_iterator i(line.begin(), line.end(), reg_exp); i != end; ++i)
        {
            smatch regmatch = *i;

            string gameStr;

            if (regmatch.size())
            {
                gameId = regmatch[1].str();
                gameStr = regmatch[2].str();
            }

            bool isLegal = true;

            map<string, int> highestColorValues;

            // For each game set
            for (sregex_token_iterator game_iter(gameStr.begin(), gameStr.end(), game_reg_exp, -1); game_iter != token_end; ++game_iter)
            {
                string gameSet = *game_iter;

                map<string, int> colorSets;

                for (sregex_iterator color_iter(gameSet.begin(), gameSet.end(), color_set_reg_exp); color_iter != end; ++color_iter)
                {
                    smatch colormatch = *color_iter;
                    // cout << "Nr: " << colormatch[1].str() << endl;
                    // cout << "Color: " << colormatch[2].str() << endl;
                    // cout << endl;

                    colorSets[colormatch[2].str()] = stoi(colormatch[1].str());
                }

                if (colorSets["red"] > MAX_RED || colorSets["green"] > MAX_GREEN || colorSets["blue"] > MAX_BLUE)
                {
                    isLegal = false;
                }

                // PART TWO
                if (colorSets["red"] > highestColorValues["red"])
                {
                    highestColorValues["red"] = colorSets["red"];
                }
                if (colorSets["green"] > highestColorValues["green"])
                {
                    highestColorValues["green"] = colorSets["green"];
                }
                if (colorSets["blue"] > highestColorValues["blue"])
                {
                    highestColorValues["blue"] = colorSets["blue"];
                }
            }
            // cout << "GAME ID: " << gameId << endl;
            // cout << "Red: " << highestColorValues["red"] << endl;
            // cout << "Green: " << highestColorValues["green"] << endl;
            // cout << "Blue: " << highestColorValues["blue"] << endl;

            int powerOfSet = highestColorValues["red"] * highestColorValues["green"] * highestColorValues["blue"];
            // cout << "Power of the set: " << powerOfSet << endl;
            // cout << endl;

            sumOfPowers += powerOfSet;
            if (isLegal)
            {
                sumOfLegalGameIDs += stoi(gameId);
            }
        }
    }
    cout << "Sum of legal GameIds: " << sumOfLegalGameIDs << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Sum of powers: " << sumOfPowers << endl;
}