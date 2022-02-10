#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
using namespace std;

bool isWord(string search){
	bool ans;
	search = "#"+search+"#";

	ifstream fin;
	fin.open("GameDict.txt");

	if(fin.fail())
	{
		exit(1);
	}

	bool isFound = 0;
	while(!fin.eof())
	{
		string temp = "";
		getline(fin,temp);
		for(int i=0; i<search.size(); i++)
		{
			if(temp[i]==search[i])
				isFound = 1;
			else
			{
				isFound = 0;
				break;
			}
		}
		if(isFound)
		{
			ans=1;
			break;
		}
	}
	if( fin.eof() && (!isFound) )
	{
		ans=0;
	}
	fin.close();
	
	return ans;
}