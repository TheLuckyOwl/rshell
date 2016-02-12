#include <iostream>
//#include "Parse.h"
#include "RShell.h"
using namespace std;

int main(){
	//This creates an rshell object that will then take objects from
	//the command line to run.
	RShell rshell;
	rshell.inputLoop();

	return 0;
}
