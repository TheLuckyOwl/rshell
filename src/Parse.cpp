#include "Parse.h"
#include <iostream>

using namespace std;

int Parse::errorCheckCharacters(string* commandLine){
  int errorFlag = 0;
  unsigned int doubleQuoteChecked = 0;
  unsigned int singleQuoteChecked = 0;

  for (unsigned int i = 0; i < commandLine->size(); i++){
    
	if (commandLine->at(i) == '#'){
	  break;
	}

    if (commandLine->at(i) == '"'&&i > doubleQuoteChecked){
	  if (i != commandLine->size() - 1){

	    for (unsigned int j = i + 1; j < commandLine->size(); j++){
	      if (commandLine->at(j) == '"'){
		    doubleQuoteChecked = j;
		    break;
		  }else if ( j == commandLine->size() - 1 ){
		    cout << "Error: missing an additional quotation mark \"." << endl;
		    errorFlag = 1;
		  }
	    }

	  }else {

	    cout << "Error: missing an additional quotation mark \"." << endl;
		errorFlag = 1;
	  }
    }

    if (commandLine->at(i) == '\''&&i > singleQuoteChecked){
	  if (i != commandLine->size() - 1){

	    for(unsigned int j = i + 1; j < commandLine->size(); j++){
	      if (commandLine->at(j) == '\''){
		    singleQuoteChecked = j;
		    break;
		  }else if ( j == commandLine->size() - 1 ){
		    cout << "Error: missing an additional quotation mark \'." << endl;
		    errorFlag = 1;
			return errorFlag;
		  }
	    }

	  }else {

	    cout << "Error: missing an additional quotation mark \'." << endl;
		errorFlag = 1;
		return errorFlag;
	  }
    }

    if(commandLine->at(i) == '&'){
	  if(i == commandLine->size() - 1){
        cout << "Error: unexpected token \"&\"" << endl;
		errorFlag = 1;
		return errorFlag;
      }else {
        if (commandLine->at(i+1) == '&') {
		  i++;
		  continue;
		}else {
		  cout << "Error: unexpected token \"&\"" << endl;
		  errorFlag = 1;
		  return errorFlag;
		}
	  }
	}

    if(commandLine->at(i) == '|'){
	  if(i == commandLine->size() - 1){
        cout << "Error: unexpected token \"|\"" << endl;
		errorFlag = 1;
		return errorFlag;
      }else {
        if (commandLine->at(i+1) == '|') {
		  i++;
		  continue;
		}else {
		  cout << "Error: unexpected token \"|\"" << endl;
		  errorFlag = 1;
		  return errorFlag;
		}
	  }
	}

  }
    //if (i != currentPos) etc. if its a " loop until you find another if you do reset i to old position,
    //if you reach end of string set flag.
    //if its a & or | check if its neighbor is a & if it is, check if theres another & next to that, if not
	//then its good skip to the next area. Making sure to jump over the other &. if you fail any of the 
	//checks set the flag since you have one & or more than two.
  return errorFlag;
}

int Parse::errorCheckConnectors(vector<string> parseData){
  int errorFlag = 0;

  for ( unsigned int i = 0; i < parseData.size(); i++ ){
    if ( parseData[i] == "||" || parseData[i] == "&&" || parseData[i] == ";" ){
	  if (i == parseData.size() - 1 || i == 0 ){
        
        errorFlag = 1;

		if ( parseData[i] == "&&" ){
		  cout << "Error: unexpected token \"&&\"." << endl;
		}

        if ( parseData[i] == "||" ){
		  cout << "Error: unexpected token \"||\"." << endl;
        }

		if ( parseData[i] == ";" ){
		  cout << "Error: unexpected token \";\"." << endl;
		}
        
        return errorFlag;

		} else {
        if ( parseData[i + 1] == "||" || parseData[i + 1] == "&&" || parseData[i + 1] == ";" ){
         
		  errorFlag = 1;

		  if ( parseData[i+1] == "&&" ){
		    cout << "Error: unexpected token \"&&\"." << endl;
		  }

          if ( parseData[i+1] == "||" ){
		    cout << "Error: unexpected token \"||\"." << endl;
          }

		  if ( parseData[i+1] == ";" ){
		    cout << "Error: unexpected token \";\"." << endl;
		  }

          return errorFlag;

        }
       }  
	  }
	}

  //go through the vector checking for connectors, if you find one check the next element and connector
  //set the error flag and exit. If you reach the end return with a zero.
return errorFlag;
}

void  Parse::stringSplitter(string commandLine, int* exitFlag){
  string tempString;
  string connectorString;
  parseData.clear();

  if ( errorCheckCharacters( &commandLine ) ){
    return;
  }

  for (unsigned int i = 0; i < commandLine.size(); i++){
    unsigned int currentPos = i;
    while (commandLine[i] != ' '&&commandLine[i] != ';'&&commandLine[i] != '&'&&commandLine[i] != '|'&&commandLine[i] != '#'&&i < commandLine.size()){
      
    /* if ( commandLine[i] == '"' ){
	 //if you are able to find another " cut out the first " and second ", if you can't output an error. 
	    for(unsigned int k=0; k < commandLine.size();k++){
	      if( commandLine[k] == '"' ){
	        tempString = commandLine.substr(i + 1, k - i - 1);
			cout << tempString << endl;
	        parseData.push_back(tempString);
			currentPos = k + 1;
			i = k + 1;
	      }
	    }
	  }
    */
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
	
//Down here check if the parsed string is good, if its not print an appropriate error.
//i.e. if it has a connector hanging in the beginning or end or double connectors next to
//each other.

  if ( errorCheckConnectors(parseData) ){
    return;
  }

  expander.expand(&parseData, exitFlag);  //Pass Data to Expansion object expander.
}
