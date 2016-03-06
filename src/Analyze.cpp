#include "Analyze.h"
#include <iostream>

using namespace std;

int Analyze::analyzeString(vector<string>* givenString, int* exitFlag){
  vector<string> commandVector;
  int result = 0;
  int finalResult = 0;
  int skipAndFlag = 0;
  int skipOrFlag = 0;
  unsigned int outer = 0;
  unsigned int paranthesesCount = 0;
  unsigned int insideQuotes = 0;

  for (unsigned int i = 0;i < givenString->size();i++){

    if(skipAndFlag){    //MODIFY THESE SKIP LOOPS SO THEY WILL SKIP OVER && OR || OR ; IF ITS IN ()
      skipAndFlag = 0;
      insideQuotes = 0;
      result = 1;
      while(((givenString->at(i)!="||"&&givenString->at(i)!=";")||insideQuotes)&& i < givenString->size()-1){
        if(givenString->at(i)=="("){
          insideQuotes = 1;
        }

        if(givenString->at(i)==")"){
          insideQuotes = 0;
        }
        i++;
      }

    }else if(skipOrFlag){
      skipOrFlag = 0;
      insideQuotes = 0;
      result = 0;
      while(((givenString->at(i)!="&&"&&givenString->at(i)!=";")||insideQuotes)&&i < givenString->size()-1){
        if(givenString->at(i)=="("){
          insideQuotes = 1;
        }

        if(givenString->at(i)==")"){
          insideQuotes = 0;
        }
        i++;
      }

    }else if ( (givenString->at(i)!="&&")&&(givenString->at(i)!="||")&&(givenString->at(i)!=";") ) {
      outer = i;
      if(givenString->at(i) == "("){
        paranthesesCount = 0;
        for (unsigned int k=i+1; k < givenString->size(); k++){
          if( givenString->at(k)== ")" ){
            if(paranthesesCount == 0){
              outer = k;
              k = givenString->size();
            }else{
              paranthesesCount--;
            }
          }else if( givenString->at(k) == "("){
            paranthesesCount++;
          }
        }

        if (outer != i){
          //create and call subvector then return its result.
          for(unsigned int outcnt = i+1; outcnt < outer; outcnt++){  //for everything between i and outer.
            commandVector.push_back(givenString->at(outcnt));
          }
          //Output sub vector.
          /*cout << "Created SubVector: ";
          for (unsigned int tempcnt = 0; tempcnt < commandVector.size(); tempcnt++){
            cout << commandVector[tempcnt] << " ";
          }
          cout << endl;*/



          i = outer;
          result = analyzeString(&commandVector, exitFlag);
          
          commandVector.clear();

          if (result == 2){
            return result;
          }

        }
      
      }else{
        commandVector.push_back(givenString->at(i));
      }

    } else {
	  //execute the command and reset the commandVector, take the value from and decide what to do next based 
	  //on the connector

      if (commandVector[0] == "exit"){
        *exitFlag = 1;
        break;
      }
      if(commandVector.size() != 0){
        //cout << "executed command: " << commandVector[0] << endl;
        result = commander.callCommand(commandVector);}

      if(result == 2){
        cout << "Error: Invalid Call to Command " << commandVector[0] << "." << endl;  
        return result;
      } 

      //cout << "result flag before && and || check: " << result << "." << endl;

      if (givenString->at(i)=="&&"){
        if (result!=0){
          skipAndFlag = 1;
          finalResult = 1;
        }else{
          finalResult = 0;
        }
      }
      
      if (givenString->at(i)=="||"){
        if (result==0){
          skipOrFlag = 1;
          finalResult = 0;
        }else{
          finalResult = 1;
        }
      }
      
        commandVector.clear();
   }

  }

  if(commandVector.size()>0){
    if (commandVector[0] == "exit"){
        *exitFlag = 1;
    }

    //if (commandVector[0] == "test"){}

    if(commandVector[0] != "exit"){
      result = commander.callCommand(commandVector);
    }

    if(result == 2){
      cout << "Error: Invalid Call to Command " << commandVector[0] << "." << endl;
      return result;
    }
  }
  //cout << "Final Result: " << finalResult << "." << endl;
  return finalResult;

}
