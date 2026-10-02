#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int ReadInt(string Message, int Min, int Max);
double ReadPositiveDouble(string Message);
vector<string> SplitString(string S1, string Delim);
void AddDataLineToFile(string FileName, string stDataLine);
string ReadClientNumber();