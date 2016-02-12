#ifndef ANALYZE_H
#define ANALYZE_H

#include <vector>
#include <string>
#include "Command.h"

using namespace std;

class Analyze {
  private:
    vector<string>* parseData;
	Command commander;
  public:
    void analyzeString(vector<string>* givenData, int* exitFlag);	//I don't think we need a parseData internal variable?
};
#endif
