#include "RShell.h"
#include <unistd.h>
#include <limits.h>

using namespace std;

string RShell::readCommandLine(){
  string tempString;
  getline(cin, tempString);
  return tempString;
}

void RShell::inputLoop(){

  exitStatus = 0;

  char hostname[HOST_NAME_MAX];
  char username[LOGIN_NAME_MAX];

  if (gethostname(hostname, HOST_NAME_MAX)){
    cout << "Error getting host name" << endl;
    return;
  }
  
  if (getlogin_r(username, LOGIN_NAME_MAX)){
    cout << "Error getting user name" << endl;
    return;
  }

  do{
    cout << username << "@" << hostname << "$ ";
    commandLine = readCommandLine();
	parseString();
  }while (!exitStatus);

}

void RShell::outputString(string givenString){
  cout << givenString;
}

void RShell::parseString(){
  parser.stringSplitter(commandLine);
}

void RShell::setExit(){
  exitStatus = 1;
}
