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
  /*The following if statements will check to get the 
   * current host and the current login. If not possible
   * an error statement will display letting the user know.
   */
  if (gethostname(hostname, HOST_NAME_MAX)){
    cout << "Error getting host name" << endl;
    return;
  }
  
  if (getlogin_r(username, LOGIN_NAME_MAX)){
    cout << "Error getting user name" << endl;
    return;
  }
  /*While the program is running this do statement will display
   * the current user name and the current host name to the terminal.
   */
  do{
    cout << username << "@" << hostname << "$ ";
    commandLine = readCommandLine();
	parseString();
  }while (!exitStatus);

}

void RShell::outputString(string givenString){
  cout << givenString;
}
/*This function creates a Parser object to take the command
 * line string to seperate the commands, comments, arguments,
 * and the connectors. This way they can be used to exectue.
 */
void RShell::parseString(){
  parser.stringSplitter(commandLine);
}

void RShell::setExit(){
  exitStatus = 1;
}
