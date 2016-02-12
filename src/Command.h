#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {
  private:
    string commandString;
	string argumentString;

	int forkFunction(char** commandArray);
  public:
    int callCommand(vector<string> givenVector); 
};
#endif
