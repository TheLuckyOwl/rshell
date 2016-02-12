#include "Parse.h"
#include <iostream>

using namespace std;

void  Parse::stringSplitter(string commandLine, int* exitFlag){
  string tempString;
  string connectorString;
  parseData.clear();
  for (unsigned int i = 0; i < commandLine.size(); i++){
    unsigned int currentPos = i;
    while (commandLine[i] != ' '&&commandLine[i] != ';'&&commandLine[i] != '&'&&commandLine[i] != '|'&&commandLine[i] != '#'&&i < commandLine.size()){
      
     // if ( commandLine[i] = '"' ){
	  //cut out the "  
	 // }

      i++;
    }
	/*The following if statements check for exectution commands at tghe end of words.
	 *If an exectution command is detected at the end of a word such as : ";" "&" "|"
	 *it will check the next to last character, if they match then they will be added
	 *to the parseData vector.
	 */
    if (i != currentPos){
      tempString = commandLine.substr(currentPos, i - currentPos);
      parseData.push_back(tempString);

      if (commandLine[i] == ';'){
        parseData.push_back(";");
      }
	  if(commandLine[i] == '#'){
	    break;
	  }

    }else {

      if (commandLine[i] == ';') {
        parseData.push_back(";");
      }
	  
      if (commandLine[i] == '#') {
	    break;
	  }

      if (commandLine[i] == '&'&&i != 0) {
        if (commandLine[i - 1] == '&'){
          parseData.push_back("&&");
        }
      }

      if (commandLine[i] == '|'&&i != 0){
        if (commandLine[i - 1] == '|'){
          parseData.push_back("||");
        }
      }

    }
  }
	
  //TEST PRINT LOOP
  for (unsigned int i = 0; i < parseData.size(); i++){
    cout << parseData[i] << endl;
  }
//Down here check if the parsed string is good, if its not print an appropriate error.
//
  expander.expand(&parseData, exitFlag);  //Pass Data to Expansion object expander.
}
