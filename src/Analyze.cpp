#include "Analyze.h"
#include <iostream>

using namespace std;

void Analyze::analyzeString(vector<string>* givenString, int* exitFlag){
  vector<string> commandVector;
  int result = 0;
  int passFlag = 0;

  for (unsigned int i = 0;i < givenString->size();i++){
    if ( (givenString->at(i)!="&&")&&(givenString->at(i)!="||")&&(givenString->at(i)!=";") ) {
      commandVector.push_back(givenString->at(i));
    } else {
	  //execute the command and reset the commandVector, take the value from and decide what to do next based 
	  //on the connector
      if (commandVector[0] == "exit"){
        *exitFlag = 1;
        break;
      }

      result = commander.callCommand(commandVector);

      if(result){
        cout << "Error: Invalid Call to Command " << commandVector[0] << "." << endl;  
      } 

      if (givenString->at(i)=="&&"){
        if (result!=0){
          passFlag = 1;
          break;
        }
      }
      
      if (givenString->at(i)=="||"){
        if (result==0){
          passFlag = 1;
          break;
        }
      }
	  
      commandVector.clear();
   }

  }
  
  if(commandVector.size()>0&&!passFlag){
    if (commandVector[0] == "exit"){
        *exitFlag = 1;
    }

    //if (commandVector[0] == "test"){}

    if(commandVector[0] != "exit"){
      result = commander.callCommand(commandVector);
    }

    if(result){
      cout << "Error: Invalid Call to Command " << commandVector[0] << "." << endl;
    }
  }

}
