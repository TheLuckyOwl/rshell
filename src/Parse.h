#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Expansion.h"

using namespace std;

class Parse {
  private:
    vector<string> parseData;
    Expansion expander;

	int errorCheckCharacters(string *commandLine);
	int errorCheckConnectors(vector<string> parseData);

  public:
    void stringSplitter(string commandLine, int* exitFlag);		
};

#endif
