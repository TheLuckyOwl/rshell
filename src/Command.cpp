#include "Command.h"
#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sysexits.h>
#include <cstring>

//If 0 succeeded else failed.
using namespace std;

int Command::callCommand(vector<string> givenVector){
  char** commandArray;
  int result=0;

	commandArray = new char* [givenVector.size() + 1];
  
	for(unsigned int j = 0; j < givenVector.size(); j++){
	  commandArray[j] = (char*)(givenVector[j].c_str());
	}

	commandArray[givenVector.size()] = NULL;

	result = forkFunction(commandArray);

	delete[] commandArray;

  return result;
  //Call forkFunction(), we will pass the finished commandArray to this function.
  //Deallocate the array.
}

int Command::forkFunction(char** commandArray){
  
  pid_t currentPID = fork();
  int pipefd[2];
  int count, error;
  
  if (pipe(pipefd)){
    perror("Error failed to create pipeline.");
	return EX_OSERR;
  }
  
  if (fcntl(pipefd[1], F_SETFD, fcntl(pipefd[1], F_GETFD) | FD_CLOEXEC)) {
    perror("Error failed to set file descriptor flags.");
	return EX_OSERR;
  }

  if (currentPID < 0){  //PID < 0, means that something went wrong creating a child process.
    perror("Error creating child with fork!");
	exit(-1);
  }

  if (currentPID > 0){  //PID>0, which means we are in the parent process.
    close(pipefd[1]);
	while ((count = read(pipefd[0], &error, sizeof(errno))) == -1){
	  if (errno != EAGAIN && errno != EINTR){ 
	    break;
	  }
	}

	if (count) {
	  return EX_UNAVAILABLE;
	}
    close(pipefd[0]);

	waitpid(currentPID, &error, 0);
	if (error < 0){
	  perror("Error in waitpid!");
	  exit(-1);
	}

  if(WIFEXITED(error)){}else{
    error = 2;
  }

  } else {  //PID == 0, which means we are in the child process.
    close(pipefd[0]);
	int execvpStatus = execvp(commandArray[0], commandArray);
	write(pipefd[1], &errno, sizeof(int));
	if (execvpStatus < 0){
	  perror("Error in execvp!");
	  exit(-1);
	}
  }

  return error;
}
