#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using namespace std;

//Command class, will be used to call execvp and by extension commands.

class Command {
  private:
  string commandString;
	string argumentString;

	int forkFunction( char** commandArray );
  public:
    int callCommand( vector<string> givenVector ); 
};
#endif
