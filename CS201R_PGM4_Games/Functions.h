#pragma once
#include <iostream>
#include <string>

using namespace std;

// PRE: Input string
// POST: Returns true or false if the string is not a menu option
bool   isMenuItem(string s);
// PRE: None
// POST: returns a string of a character of what game the user wants to play
string menu();