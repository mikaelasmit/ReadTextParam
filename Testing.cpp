// A hello world program of the internet. 
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <numeric>

using namespace std;
 
// include the ParamReader class.
#include "CParamReader.h"
//#include "ParamReader.txt"

 
int main()
{


    // make a param reader object.
    CParamReader myReader;
    char fileName[] = "Params.txt";
    if(! myReader.setNewFileName(fileName))
	{
		cout << "File " << fileName << " doesn't exist." << endl; 
		return 1; 
	} else
	{
		cout << "File exists." << endl; 
	}

    char paramName[] = "vectorTest";
    int length;
    char* myValue = myReader.getParamString(paramName, length);
    cout << paramName << " = " << myValue << ": length = " << length << endl;
	cout << myValue << endl;


	// Lets convert string to vector 
	string ParamStr=myValue;
	
	cout << "The string parameter values: \t\t" << ParamStr << endl;

	stringstream ss;
	vector<double> data;
	ss << ParamStr;
	double a;
	while (ss >> a)
    data.push_back(a);
	
	cout << " Let's check output of our new vector: \t" << data[0] << " " << data[1] << " " <<data[2] << " " << data[3] << endl;
	

 
    return 0;
}