#ifndef EXPANSION_H
#define EXPANSION_H

#include <vector>
#include <string>
#include "Analyze.h"

using namespace std;

class Expansion {
  private:
    vector<string>* parseData;
    Analyze analyzer;
  public:
    void expand(vector<string>* givenData, int* exitFlag);	
};
#endif
