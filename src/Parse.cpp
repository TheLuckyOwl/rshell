#include "Parse.h"
#include <iostream>

using namespace std;

int checkIgnores( unsigned int givenIndex, vector<unsigned int> givenIgnore ){
 for(unsigned int paranthesesChecker = 0; paranthesesChecker < givenIgnore.size(); paranthesesChecker++){
    if(givenIndex == givenIgnore[paranthesesChecker]){
      return 0;    
    }
 }

 return 1;
}

int Parse::errorCheckCharacters(string* commandLine){
  int errorFlag = 0;
  //unsigned int doubleQuoteChecked = 0;
  //unsigned int singleQuoteChecked = 0;
  //unsigned int paranthesesChecked = 0;
  
  vector<unsigned int> ignoreDoubleQuote;
  vector<unsigned int> ignoreSingleQuote;
  vector<unsigned int> ignoreParantheses;
  vector<unsigned int> ignoreBrackets;

  int checkParantheses;
  int checkSingleQuote;
  int checkDoubleQuote;
  int checkBrackets;

  for (unsigned int i = 0; i < commandLine->size(); i++){
    
  if (commandLine->at(i) == '#'){
    break;
  }
/*
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
*/
    if (commandLine->at(i) == '"'&&checkIgnores(i, ignoreDoubleQuote)){  //Checking for Double Quote Pairs.
      if (i != commandLine->size() - 1){
        for (unsigned int j = i + 1; j < commandLine->size(); j++){
          if (commandLine->at(j) == '"'){
            checkDoubleQuote = checkIgnores(j, ignoreDoubleQuote);
            if(checkDoubleQuote){           //If we find a double quote that isn't ignored.
              ignoreDoubleQuote.push_back(j);
              break; 
            }
          }
          if ( j == commandLine->size() - 1 ){
           cout << "Error: missing a double quotation mark \"." << endl;
           errorFlag = 1;
          }


       }

     }else {
        checkDoubleQuote = checkIgnores(i, ignoreDoubleQuote);
        if(checkDoubleQuote){
          cout << "Error: missing a double quotation mark \"." << endl;
          errorFlag = 1;
        }
     }

   }


    if (commandLine->at(i) == '\''&&checkIgnores(i, ignoreSingleQuote)){  //Checking for Single Quote Pairs.
      if (i != commandLine->size() - 1){
        for (unsigned int j = i + 1; j < commandLine->size(); j++){
          if (commandLine->at(j) == '\''){
            checkSingleQuote = checkIgnores(j, ignoreSingleQuote);
            if(checkSingleQuote){           //If we find a single quote that isn't ignored.
              ignoreSingleQuote.push_back(j);
              break; 
            }
          }
          if ( j == commandLine->size() - 1 ){
           cout << "Error: missing a single quotation mark \'." << endl;
           errorFlag = 1;
          }


       }

      }else {
        checkSingleQuote = checkIgnores(i, ignoreSingleQuote);
        if(checkSingleQuote){
          cout << "Error: missing a single quotation mark \'." << endl;
          errorFlag = 1;
        }
      }
    }

    if (commandLine->at(i) == '('){  //Checking for Parantheses Pairs.
      if (i != commandLine->size() - 1){
        for (unsigned int j = i + 1; j < commandLine->size(); j++){
          if (commandLine->at(j) == ')'){
            checkParantheses = checkIgnores(j, ignoreParantheses);
            if(checkParantheses){           //If we find a Parantheses that isn't ignored.
              ignoreParantheses.push_back(j);
              break; 
            }
          }
          if ( j == commandLine->size() - 1 ){
           cout << "Error: missing a closing parantheses )." << endl;
           errorFlag = 1;
          }


       }

      }else {

        cout << "Error: missing a closing parantheses )." << endl;
        errorFlag = 1;
      }
    }

    if(commandLine->at(i) == ')'){  //Checking for lone closing Paranthese.
      checkParantheses = checkIgnores(i, ignoreParantheses);
      if(checkParantheses){
        errorFlag = 1;
        cout << "Error: missing a opening parantheses [." << endl;
      }
    }

    if (commandLine->at(i) == '['){  //Checking for Bracket Pairs.
      if (i != commandLine->size() - 1){
        for (unsigned int j = i + 1; j < commandLine->size(); j++){
          if (commandLine->at(j) == ']'){
            checkBrackets = checkIgnores(j, ignoreBrackets);
            if(checkBrackets){           //If we find a Bracket that isn't ignored.
              ignoreBrackets.push_back(j);
              break; 
            }
          }
          if ( j == commandLine->size() - 1 ){
           cout << "Error: missing a closing bracket ]." << endl;
           errorFlag = 1;
          }


       }

      }else {

        cout << "Error: missing a closing bracket ]." << endl;
        errorFlag = 1;
      }
    }

    if(commandLine->at(i) == ']'){  //Checking for lone closing Bracket.
      checkBrackets = checkIgnores(i, ignoreBrackets);
      if(checkBrackets){
        errorFlag = 1;
        cout << "Error: missing a opening bracket [." << endl;
      }
    } 

    if(commandLine->at(i) == '&'){  //Checking for lone &.
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

    if(commandLine->at(i) == '|'){  //Checking for lone |.
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
  unsigned int writingWords = 0;
  unsigned int afterParantheses = 0;
  unsigned int beforeParantheses = 0;

  commandLine.erase(remove(commandLine.begin(), commandLine.end(), '\t'), commandLine.end());
  commandLine.erase(remove(commandLine.begin(), commandLine.end(), '\n'), commandLine.end());

  if ( errorCheckCharacters( &commandLine ) ){
    return;
  }

  for (unsigned int i = 0; i < commandLine.size(); i++){
    unsigned int currentPos = i;
    unsigned int outer = i;
    while (commandLine[i] != ' '&&commandLine[i] != ';'&&commandLine[i] != '&'&&commandLine[i] != '|'&&commandLine[i] != '#'&&commandLine[i] != '('&&commandLine[i] != ')'&&commandLine[i] != '['&&commandLine[i] != ']'&&i < commandLine.size()){
      
      //OLD QUOTATION CLIPPING METHOD
      /*if ( commandLine[i] == '"'){
        //if you are able to find another " cut out the first " and second ", if you can't output an error. 
        for(unsigned int k=i+1; k < commandLine.size();k++){
          if( commandLine[k] == '"' ){
            tempString = commandLine.substr(i + 1, k - i - 1);
            parseData.push_back(tempString);
            currentPos = k + 1;
            i = k;
            k = commandLine.size();
          }
        }
      }
    
      if ( commandLine[i] == '\''){
        //if you are able to find another ' cut out the first ' and second ', if you can't output an error. 
        for(unsigned int k=i+1; k < commandLine.size();k++){
          if( commandLine[k] == '\'' ){
            tempString = commandLine.substr(i + 1, k - i - 1);
            parseData.push_back(tempString);
            currentPos = k + 1;
            i = k;
            k = commandLine.size();
          }
        }
      }*/

      //NEW CLIPPING METHOD
      outer = i;
      if ( commandLine[i] == '"'){
        for ( unsigned int k=i+1; k < commandLine.size(); k++){
          if( commandLine[k] == '"'){
            outer = k;
          }

          if( commandLine[k] == ';' || commandLine[k] == '|' || commandLine[k] == '&' ){
            k = commandLine.size();
          }
        }

        if (outer != i){
          tempString = commandLine.substr(i + 1, outer - i - 1);
          tempString.erase(remove(tempString.begin(), tempString.end(), '"'), tempString.end());
          parseData.push_back(tempString);
          i = outer;
          currentPos = outer + 1;
        }
      }

      outer = i;
      if ( commandLine[i] == '\''){
        for ( unsigned int k=i+1; k < commandLine.size(); k++){
          if( commandLine[k] == '\''){
            outer = k;
          }

          if( commandLine[k] == ';' || commandLine[k] == '|' || commandLine[k] == '&' ){
            k = commandLine.size();
          }
        }

        if (outer != i){
          tempString = commandLine.substr(i + 1, outer - i - 1);
          tempString.erase(remove(tempString.begin(), tempString.end(), '\''), tempString.end());
          parseData.push_back(tempString);
          i = outer;
          currentPos = outer + 1;
        }
      }




      i++;
    }
  /*The following if statements check for exectution commands at the end of words.
   *If an execution command is detected at the end of a word such as : ";" "&" "|"
   *it will check the next to last character, if they match then they will be added
   *to the parseData vector.
   */
    if (i != currentPos){
      writingWords = 1;
      tempString = commandLine.substr(currentPos, i - currentPos);
      parseData.push_back(tempString);
      
      if(writingWords&&beforeParantheses){      //BEFORE
        cout << "Error: Unexpected token before Parantheses." << endl;
        return;
      }

      if(writingWords&&afterParantheses){
        cout << "Error: Unexpected token after Parantheses." << endl;
        return;
      }

      if(beforeParantheses){    //BEFORE
        beforeParantheses = 0;
      }

      if (commandLine[i] == ';'){
        writingWords = 0;
        afterParantheses = 0;
        parseData.push_back(";");
      }

      if(commandLine[i] == '#'){
        afterParantheses = 0;
        break;
      }

      if (commandLine[i] == '('){
        beforeParantheses = writingWords;            //BEFORE
        parseData.push_back("(");
      }

      if (commandLine[i] == ')'){
        beforeParantheses = 0;
        afterParantheses = 1;
        parseData.push_back(")");
      }

      if (commandLine[i] == '['){
        parseData.push_back("[");
      }

      if (commandLine[i] == ']'){
        parseData.push_back("]");
      }

    }else {

      if (commandLine[i] == ';') {
        afterParantheses = 0;
        writingWords = 0;
        parseData.push_back(";");
      }
    
      if (commandLine[i] == '#') {
        break;
      }

      if (commandLine[i] == '('){
        beforeParantheses = writingWords;   //BEFORE
        parseData.push_back("(");
      }

      if (commandLine[i] == ')'){
        afterParantheses = 1; //ADDED
        parseData.push_back(")");
      }

      if (commandLine[i] == '['){
        parseData.push_back("[");
      }

      if (commandLine[i] == ']'){
        parseData.push_back("]");
      }

      if (commandLine[i] == '&'&&i != 0) {
        if (commandLine[i - 1] == '&'){
          writingWords = 0;
          afterParantheses = 0;
          parseData.push_back("&&");
        }
      }

      if (commandLine[i] == '|'&&i != 0){
        if (commandLine[i - 1] == '|'){
          writingWords = 0;
          afterParantheses = 0;
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

//Use this loop to print out the parseData to see everything is being broken up
//correctly.

//  for (unsigned int erw = 0; erw < parseData.size(); erw++){
//    cout << parseData[erw] << endl;
//  }

  expander.expand(&parseData, exitFlag);  //Pass Data to Expansion object expander.
}
