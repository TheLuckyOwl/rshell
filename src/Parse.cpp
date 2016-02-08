/*#include <iostream>
#include <sstream>
#include "Parse.h"

using namespace std;

class Parse
{
	private:
		vector <string> parseData;
	public:
		string line;
		vector <string> finalData
		Parse()
		{

		}
		~Parse()
		{

		}

		void stringSplitter(string commandLine)
		{
			while(getline(commandLine,line))
			{
				istringstream istream(line);
				string output;
				while(istream>>output)
				{
					parseData.push_back(output);
				}
			}
			for(int i =0; i<parseData.size();i++)
			{
				string work;
				parseData[i] = work;
				if(work != "&&" && work != "||")
				{
					if(work.back() == ';')
					{
						work.erase(work.end());
						finalData.push_back(work);
						finalData.push_back(';');
					}
					else if(work.back() == '|')
					{
						work.erase(work.end());
						work.erase(work.end());
						finalData.push_back(work);
						finalData.push_back('||');
					}
					else if(work.back() == '&')
					{
						work.erase(work.end());
						work.erase(work.end());
						finalData.push_back(work);
						finalData.push_back('&&');
					}
					else
					{
						finalData.push_back(work);
					}
				}
				else
				{
					finalData.push_back(work);
				}
			}
			
		}
}*/
