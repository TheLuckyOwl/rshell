#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <vector>
#include <string>
#include "Expansion.h"

using namespace std;

class Parse {
  private:
    vector<string> parseData;
    Expansion expander;
  public:
    void stringSplitter(string commandLine);		
};

#endif
