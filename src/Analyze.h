#ifndef ANALYZE_H
#define ANALYZE_H

#include <vector>
#include <string>
#include "Command.h"

using namespace std;

//Analyze class, will be used to analyze vector string of connectors, commands,
//and operators.

class Analyze {
  private:
    vector<string>* parseData;
	  Command commander;
  public:
    int analyzeString( vector<string>* givenData, int* exitFlag );
};
#endif
