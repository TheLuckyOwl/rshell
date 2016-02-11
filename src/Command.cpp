#include "Command.h"
#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//Note: need to implement self-pipe trick to return whether execvp executed properly. less than 0 = failed.
//higher than 0 = succeeded.
//
using namespace std;

int Command::callCommand(string givenCommand, string givenArgument){
  char** commandArray;
  string tempString;
  int result=1;
  
  vector<string> commandVector;

  if(givenCommand != ""){
    
	for (unsigned int i = 0; i < givenArgument.size(); i++){
      unsigned int currentPos = i;

      while (givenArgument[i] != ' '){
        i++;
      }  

      if (i != currentPos){
        tempString = givenArgument.substr(currentPos, i - currentPos);
        commandVector.push_back(tempString);
      }
    }


	commandArray = new char* [commandVector.size()+2];


    commandArray[0] = (char*)givenCommand.c_str();
  
	for(unsigned int j=1; j < commandVector.size()+1; j++){
	  commandArray[j] = (char*)(commandVector[j-1].c_str());
	}

	commandArray[commandVector.size()+1] = NULL;

	result = forkFunction(commandArray);

	delete[] commandArray;

  }

  return result;
  //Call forkFunction(), we will pass the finished commandArray to this function.
  //Deallocate the array.
}

int Command::forkFunction(char** commandArray){
  pid_t currentPID = fork();
  
  if (currentPID < 0){  //PID < 0, means that something went wrong creating a child process.
    perror("Error creating child with fork!");
	exit(-1);
  }

  if (currentPID > 0){  //PID>0, which means we are in the parent process.
    int waitStatus;
	waitpid(currentPID, &waitStatus, 0);
	if(waitStatus < 0){
	  perror("Error in waitpid!");
	  exit(-1);
	}
  } else {  //PID == 0, which means we are in the child process.
    int execvpStatus = execvp(commandArray[0], commandArray);
	if (execvpStatus < 0){
	  perror("Error in execvp!");
	  exit(-1);
	}
  }

  return 1;
}
