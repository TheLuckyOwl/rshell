#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>


using namespace std;

class RShell {
	private:
		string commandLine;
		int exitStatus;
		//Parse parser;

		void parseString(string givenString);
	public:
		void inputLoop();
		void outputString(string givenString);
		void setExit();
		string readCommandLine();

};
#endif
