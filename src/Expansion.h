#ifndef EXPANSION_H
#define EXPANSION_H

#include <vector>
#include <string>
#include "Analyze.h"

using namespace std;

// Expansion class, will be used to expand variables based on expansion rules
// inside of expand function.

class Expansion {
  private:
    vector<string>* parseData;
    Analyze analyzer;
  public:
    void expand( vector<string>* givenData, int* exitFlag );	
};
#endif
