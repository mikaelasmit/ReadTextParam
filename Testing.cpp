// A hello world program of the internet.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>



using namespace std;



// include the ParamReader class.

#include "CParamReader.h"



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

    

    

    //char v[] = "vectorTest";
    char ParamName[] = "vectorTest";
    int length ;
    int nr_rows;
    int nr_columns;

    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);

    cout << ParamName << " = " << myValue << ": length = " << length << " nr_rows: " << nr_rows << " nr_columns: " << nr_columns << endl;
    
    // Lets convert string to vector
    //string ParamStr;
    
    cout << "The string parameter values: \t\t" << myValue << endl;
    
    stringstream ss;
    vector<double> data;
    ss << myValue;
    double a;
    while (ss >> a)
        data.push_back(a);
    
    cout << " Let's check output of our new vector: \t" << data[0] << " " << data[1] << " " <<data[2] << " " << data[3] << endl;
    

    
    cout << myValue << endl;
    
	system("pause");
    return 0;

}





