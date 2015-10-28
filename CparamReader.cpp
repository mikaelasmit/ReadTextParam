/*
 * CParamReader.cpp
 *
 *  Created on: 12 Nov 2014
 *      Author: jtrusc
 *  Modified: 26 Nov 2014
 *		Author: Jie Yang
 */
#include <iostream>

#include <string.h>

#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <numeric>

#include "CParamReader.h"

using namespace std;

// Class Constructor
CParamReader::CParamReader()
{
    paramBuffer = new char[BUFFER_SIZE];
    filePathString = NULL;
}

// Class Destructor
CParamReader::~CParamReader()
{
    delete[] paramBuffer;
    if(filePathString!=NULL)
        delete[] filePathString;
}


// Set the file name and check that it exists.
// unattaches previous file if necessary.
bool CParamReader::setNewFileName(char* filePath)
{
    // If there's a file attached, remove it.
    if(paramFileStream.is_open())
        paramFileStream.close();
    
    paramFileStream.open(filePath);
    
    if(!paramFileStream.is_open())
        return false;
    
    paramFileStream.close(); // Just checking, close it
    
    filePathString = new char[strlen(filePath)+1];
    strcpy(filePathString, filePath);
    
    return true;
}

// Return a string containing parameter data or NULL and also the length of the vector.
char* CParamReader::getParamString(const char* paramName, int& nElements, int& rows, int& columns)
{
    // Do we have a file attached?
    paramFileStream.open(filePathString);
    
    if(!paramFileStream.is_open())
        return NULL;
    
    
    // Declare variables needed
    int paramLength = strlen(paramName);
    bool found = false;
    string paramString;
    string paramContainer;
    //char charContainer[1000];
    char* token;
    //int count;
    int nullTerminal;
    
    
    // Run through the lines of the file for the parameter
    while(!paramFileStream.eof() && !found)
    {
        paramFileStream.getline(paramBuffer,BUFFER_SIZE-1);
        token = strtok(paramBuffer,"\t");		// This reads the first bit until 'tab' "\t"
        
        // Anything on this line?
        if(token!=NULL)
        {
            // Line doesn't begin with # and matches param name?
            if(token[0]!='#'&& token[0]!=';' && strcmp(paramName,token)==0)
            {
                columns=0;
				rows=0;
                cout << "Token: " << token << endl;
                
                
                while (token[0]!=';')
                {
                    
                    // Lets get the next line and first line of data
                    paramFileStream.getline(paramBuffer,BUFFER_SIZE-1);
                    cout << "Token: " << token << endl;
                    paramString = strtok(token,"\t");
                    cout << "paramString: " << paramString << endl;
                    
                    if (token[0]!=';'){
                        
                        
                        // 24/04/15: Remove any extra spaces from the end of the string (as long as the string isn't zero length).
                        nullTerminal = strlen(token);		// This gets the length of the char string
                        cout << "nullTerminal: " << nullTerminal << endl;
                        while(token[nullTerminal-1]==' ')  // This removes all extra spaces
                        {
                            nullTerminal--;							// means minus minus (e.g. from 3 to 2)
                            cout << "we removed the spaces " << endl;
                            cout << "nullTerminal: " << nullTerminal << endl;
                        }
                        
                        token[nullTerminal] = '\0';		// ends the string in a specific way
                        
                        
                        
                        
                        // Lets add this data to the paramContainer
                        if (rows==0)
                        {
                            paramContainer=token;
                            nullTerminal=paramContainer.length();
                            cout << "Terminal length: " << nullTerminal << endl;
                            columns=0;
                            for(int c=0; c<nullTerminal; c++)
                            {
                                if (paramContainer[c]==' ')
                                {
                                    columns++;
                                    cout << "Columns!!!: " << columns << " C: " << c << endl;
                                }
                            }
                            columns=columns+1;
                            cout << "!!!ParamContainer: " << paramContainer << " nr_columns: " << columns << endl;
                        }
                        else if (rows>0)
                        {
                            
                            paramString=token;
                            paramContainer.append(" ");
                            paramContainer.append(paramString);
                            cout << "ParamString: " << paramString << " and paramContainer: " << paramContainer << endl;
                            
                            //strcat(charContainer, " ");
                            //strcat(charContainer, paramString);
                        }
                        rows++;
                        
                        
                        cout << "Round 2: " << endl;
                        cout << "ParamStr: \t" << paramString << endl;
                        cout << "Container: \t" << paramContainer << endl;
                        
                    }
                    else
                    {
                        found = true;
                        paramContainer=paramContainer;
;
                        cout << "FINAL: " <<paramContainer << " rows: " << rows << " columns: " << columns << endl;
                    }
                    
                }
                found = true;
            }
        }
    }
    
    
    // count the spaces. Single space separates values so length of vector is #spaces + 1.
    char* charContainer = new char[paramContainer.length() +1];
    strcpy(charContainer, paramContainer.c_str());
	cout << "charContainer: " << charContainer << endl;
    nullTerminal = strlen(charContainer);		// This gets the length of the char string
    int count = 0;
    for(int j=0;j<nullTerminal;j++)
        if(paramContainer[j]==' ') count++;
    
    //nElements = count+ 1;
    nElements=count + 1;
    cout << "NElements: " << nElements << endl;
    
    paramFileStream.close();
    
    return charContainer;
}



