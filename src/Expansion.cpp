#include "Expansion.h"

using namespace std;

void Expansion::expand( vector<string>* givenData, int* exitFlag ) {
	//Creates an analyzer object to take the string 
	//then pass it to the command class.


  //Remove closing square brackets and replace opening square brackets with
  //test.
  for( unsigned int expcnt = 0; expcnt < givenData->size(); expcnt++ ) {
    if( givenData->at(expcnt) == "[" ) {
      givenData->at(expcnt) = "test";
    }

    if ( givenData->at(expcnt) == "]" ) {
      givenData->erase(givenData->begin() + expcnt);
    }
  }

	analyzer.analyzeString( givenData, exitFlag );
}
