/*
 * Creator: Matthew Rossi
 * Date 6/30/2015
 * Purpose: Random source code that reverse any file
 * sent to it through the command line.
 */

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "logger.h"
using namespace std;

#define maximum_len 50
void reverseFile(ifstream &, ofstream &);
void Prompt(const char * message, char * target, int max_len);

int main()
{
    Logger::OpenLogFile("main.log");
    ifstream inData;
    ofstream outData;
    char inFileName[50], outFileName[54];
    Prompt("Enter the name of the file", inFileName, maximum_len);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
    }
    strcpy(outFileName, inFileName);
    strncat(outFileName, ".out", 4);
    inData.open(inFileName);
    outData.open(outFileName);
    cout << "Reversing text in " << inFileName << endl;
    cout << "Reversed text will be store in " << inFileName << ".out" << endl;
    reverseFile(inData, outData);
    cout << "Process complete" << endl;
    inData.close();
    outData.close();
    Logger::CloseLogFile();
    return 0;
}
void reverseFile(ifstream &in, ofstream &out)
{
    LogStart2(&in, &out);
    if (in.eof())
        return;
    char character;
    in.get(character);
    reverseFile(in, out);
    out << character;
    LogEnd2(&in, &out);
}
void Prompt(const char * message, char * target, int max_len)
{
    LogStart3(message, target, max_len);
    do
    {
        cout << message << endl;
        cin >> setw(max_len) >> target;  // The setw command prevents typing more than max_len chars
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Input can only have " << max_len << "characters.\n";
            continue;
        }
        break;
    } while (true);
    LogEnd3(message, target, max_len);
}
