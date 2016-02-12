#include "Expansion.h"

using namespace std;

void Expansion::expand(vector<string>* givenData){
	//Creates an analyzer object to take the string 
	//then pass it to the command class.
	analyzer.analyzeString(givenData);
}
