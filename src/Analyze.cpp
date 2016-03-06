#include "Analyze.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

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
  unsigned int finishedParantheses = 0;

  vector<int> resultVector;

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
      if(givenString->at(i)=="||"){
        resultVector.push_back(-2);
      }
      if(givenString->at(i)==";"){
        resultVector.push_back(-3);
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
      if(givenString->at(i)=="&&"){
        resultVector.push_back(-1);
      }
      if(givenString->at(i)==";"){
        resultVector.push_back(-3);
      }

    }else if ( (givenString->at(i)!="&&")&&(givenString->at(i)!="||")&&(givenString->at(i)!=";") ) {
      outer = i;
      if(givenString->at(i) == "("){
        if(commandVector.size()!= 0){
          cout << "Error: Unexpected token ";
          for (unsigned int unexp = 0; unexp < commandVector.size(); unexp++){
            cout << commandVector[unexp] << " ";
          }
          cout << endl;

          return 4;
        }
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


          finishedParantheses = 1;
          i = outer;
          result = analyzeString(&commandVector, exitFlag);
          resultVector.push_back(result);                   //RESULTVECTOR
          
          commandVector.clear();

          if (result == 4){
            return result;
          }

          if(result == 2){
            cout << "Error: Invalid Call to Command " << commandVector[0] << "." << endl;  
            result = 1;
          } 
        

        }
      
      }else{
        if(finishedParantheses){
          cout << "Error: Unexpected token ";
          while((givenString->at(i)!="&&")&&(givenString->at(i)!="||")&&(givenString->at(i)!=";")&&(i < givenString->size() - 1)){
            commandVector.push_back(givenString->at(i));
            i++;
          }
          if((givenString->at(i) != "&&")&&(givenString->at(i) != "||")&&(givenString->at(i)!=";")&&(i < givenString->size())){
            commandVector.push_back(givenString->at(i));
          }
          for (unsigned int unexp = 0; unexp < commandVector.size(); unexp++){
            cout << commandVector[unexp] << " ";
          }
          cout << endl;

          return 4;

        }else{
          commandVector.push_back(givenString->at(i));
        }
      }

    } else {
	  //execute the command and reset the commandVector, take the value from and decide what to do next based 
	  //on the connector

      if ( commandVector[0] == "exit" ) {
        *exitFlag = 1;
        break;
      }

      if ( commandVector[0] == "test" && commandVector.size() > 0 ) {
          //cout << "Entered Top" << endl;
          //cout << "Size of commandVector: " << commandVector.size() << "." << endl;
        if ( commandVector.size() != 3 && commandVector.size() != 2 ) {
          cout << "Error: Incorrect number of arguments for test command." << endl;
          commandVector.clear();
          break;
        }else{
          struct stat statObj;
          int defaultFlag = 0;
          int statResult = 0;
          if( commandVector.size() == 2 ){
            defaultFlag = 1;
            statResult = stat(commandVector[1].c_str(), &statObj);
          }else{
            statResult = stat(commandVector[2].c_str(), &statObj);
          }
          if ( commandVector[1] == "-e" || defaultFlag) {
 
            if(statResult){
              cout << "(False)" << endl;
              result = 1;
            }else if(statResult == -1){
              perror("stat error with -e flag."); 
              exit(EXIT_FAILURE);
            }else{
              cout << "(True)" << endl;
              result = 0;
            }      
          } else if ( commandVector[1] == "-f" ) {
            if(statResult){
              cout << "(False)" << endl;
              result = 1;
            }else if(statResult == -1){
              perror("stat error with -f flag.");
              exit(EXIT_FAILURE);
            }else{
              if(S_ISREG(statObj.st_mode)){
                cout << "(True)" << endl;
                result = 0;
              }else{
                cout << "(False)" << endl;
                result = 1;
              }
            } 
          } else if ( commandVector[1] == "-d" ) {
            if(statResult){
              cout << "(False)" << endl;
              result = 1;
            }else if(statResult == -1){
              perror("stat error with -d flag.");
              exit(EXIT_FAILURE);
            }else{
              if(S_ISDIR(statObj.st_mode)){
                cout << "(True)" << endl;
                result = 0;
              }else{
                cout << "(False)" << endl;
                result = 1;
              }
            }
          } else {
            cout << "Error: unreadable flags for test command." << endl;
            commandVector.clear();
            break;
          }
          //cout << "Reached Here" << endl;
          resultVector.push_back(result);                             //RESULTVECTOR
          //dontRun = 1;
        }
        commandVector.clear();
      }
      
      //cout << "dontRun: " << dontRun << endl;
      if(commandVector.size() != 0){
        //cout << "executed command: " << commandVector[0] << endl;
        result = commander.callCommand(commandVector);
        //cout << "RAN" << endl;
        resultVector.push_back(result);
      }
      if(result == 2){
        cout << "Error: Invalid Call to Command " << commandVector[0] << "." << endl;  
        result = 1;
      } 

      //cout << "result flag before && and || check: " << result << "." << endl;

      if (givenString->at(i)=="&&"){
        resultVector.push_back(-1);
        finishedParantheses = 0;
        if (result!=0){
          skipAndFlag = 1;
          finalResult = 1;
        }else{
          finalResult = 0;
        }
      }
      
      if (givenString->at(i)=="||"){
        resultVector.push_back(-2);
        finishedParantheses = 0;
        if (result==0){
          skipOrFlag = 1;
          finalResult = 0;
        }else{
          finalResult = 1;
        }
      }

      if (givenString->at(i)==";"){
        resultVector.push_back(-3);
        finishedParantheses = 0;
        
      }
      
        commandVector.clear();
   }

  }

  if(commandVector.size()>0){
    if (commandVector[0] == "exit"){
        *exitFlag = 1;
    }

    if (commandVector[0] == "test" && commandVector.size() > 0){
      //cout << "Entered Bottom" << endl;
       if ( commandVector.size() != 3 && commandVector.size() != 2 ) {
          cout << "Error: Incorrect number of arguments for test command." << endl;
        }else{
          struct stat statObj;
          int defaultFlag = 0;
          int statResult = 0;
          if( commandVector.size() == 2 ){
            defaultFlag = 1;
            statResult = stat(commandVector[1].c_str(), &statObj);
          }else{
            statResult = stat(commandVector[2].c_str(), &statObj);
          }
          if ( commandVector[1] == "-e" || defaultFlag) {
            if(statResult){
              cout << "(False)" << endl;
              result = 1;
            }else if(statResult == -1){
              perror("stat error with -e flag."); 
              exit(EXIT_FAILURE);
            }else{
              cout << "(True)" << endl;
              result = 0;
            }      
          } else if ( commandVector[1] == "-f" ) {
            if(statResult){
              cout << "(False)" << endl;
              result = 1;
            }else if(statResult == -1){
              perror("stat error with -f flag.");
              exit(EXIT_FAILURE);
            }else{
              if(S_ISREG(statObj.st_mode)){
                cout << "(True)" << endl;
                result = 0;
              }else{
                cout << "(False)" << endl;
                result = 1;
              }
            } 
          } else if ( commandVector[1] == "-d" ) {
            if(statResult){
              cout << "(False)" << endl;
              result = 1;
            }else if(statResult == -1){
              perror("stat error with -d flag.");
              exit(EXIT_FAILURE);
            }else{
              if(S_ISDIR(statObj.st_mode)){
                cout << "(True)" << endl;
                result = 0;
              }else{
                cout << "(False)" << endl;
                result = 1;
              }
            }
          } else {
            cout << "Error: unreadable flags for test command." << endl;
            commandVector.clear();
          }

          resultVector.push_back(result);
        }
 
    }

    if(commandVector[0] != "exit"&&commandVector[0] != "test"){
      result = commander.callCommand(commandVector);
      resultVector.push_back(result);
    }

    if(result == 2){
      cout << "Error: Invalid Call to Command " << commandVector[0] << "." << endl;
      result = 1;
      resultVector.push_back(result);
    }
  }
  /*cout << "Result Vector: ";
  for(unsigned int sizeResult = 0; sizeResult < resultVector.size(); sizeResult++){
    cout << resultVector[sizeResult] << " ";

    if(sizeResult < resultVector.size() -1 ){
      if(resultVector[sizeResult]==-3){
        resultVector[sizeResult+1] == 0;
      }else if(resultVector[sizeResult] == -2){
      
      }else if(resultVector[sizeResult] == -1){
      
      }else if(resultVector[sizeResult] == 0){
      
      }else if(resultVector[sizeResult] >= 1){
      
      }

    }else{
      if(resultVector[sizeResult-1] == -1){
        finalResult = resultVector[sizeResult];
      }else if(resultVector[sizeResult-1] == -2){
        finalResult = resultVector[sizeResult];
      }else if(resultVector[sizeResult-1] == -3){
        finalResult = 0;
      
      }
    }
  }
  cout << endl;*/

  if(resultVector.size()>=2){
    if(resultVector[resultVector.size()-1] == -2){
      if(resultVector[resultVector.size()-2]==-3){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]==-2){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]==-1){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]==0){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]>=1){
        finalResult = 0;
      }
    }else if(resultVector[resultVector.size()-1] == -1){
      if(resultVector[resultVector.size()-2]==-3){
        finalResult = 1;
      }
      if(resultVector[resultVector.size()-2]==-2){
        finalResult = 1;
      }
      if(resultVector[resultVector.size()-2]==-1){
        finalResult = 1;
      }
      if(resultVector[resultVector.size()-2]==0){
        finalResult = 1;
      }
      if(resultVector[resultVector.size()-2]>=1){
        finalResult = 1;
      } 
    }else if(resultVector[resultVector.size()-1] == 0){
      if(resultVector[resultVector.size()-2]==-3){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]==-2){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]==-1){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]==0){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]>=1){
        finalResult = 1;
      }
    }else if(resultVector[resultVector.size()-1] >= 1){
      if(resultVector[resultVector.size()-2]==-3){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]==-2){
        finalResult = 1;
      }
      if(resultVector[resultVector.size()-2]==-1){
        finalResult = 1;
      }
      if(resultVector[resultVector.size()-2]==0){
        finalResult = 0;
      }
      if(resultVector[resultVector.size()-2]>=1){
        finalResult = 1;
      }
    }
  }else if(resultVector.size()==1){
    finalResult = resultVector[0];
  }

  return finalResult;

}
