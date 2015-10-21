/*
 * CParamReader.cpp
 *
 *  Created on: 12 Nov 2014
 *      Author: jtrusc
 *  Modified: 26 Nov 2014
 *		Author: Jie Yang
 */

#include "CParamReader.h"
#include <string.h>

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
char* CParamReader::getParamString(const char* paramName, int& nElements)
{
	// Do we have a file attached?
	paramFileStream.open(filePathString);

	if(!paramFileStream.is_open())
		return NULL;

	//int paramLength = strlen(paramName);

	bool found = false;
	char* paramString = NULL;
	char* token;
	// Run through the lines of the file for the parameter
	while(!paramFileStream.eof() && !found)
	{
		paramFileStream.getline(paramBuffer,BUFFER_SIZE-1);
		token = strtok(paramBuffer,"\t");
		// Anything on this line?
		if(token!=NULL)
		{
			// Line doesn't begin with # and matches param name?
			if(token[0]!='#' && strcmp(paramName,token)==0)
			{
				// Found it!
				found = true;
				paramString = strtok(NULL,"\t");
			}
		}
	}

	// 24/04/15: Remove any extra spaces from the end of the string (as long as the string isn't zero length).
	int nullTerminal = strlen(paramString);
	while(paramString[nullTerminal-1]==' ')
		nullTerminal--;

	paramString[nullTerminal] = '\0';

	// count the spaces. Single space separates values so length of vector is #spaces + 1.
	int count = 0;
	for(int j=0;j<nullTerminal;j++)
		if(paramString[j]==' ') count++;

	nElements = count+ 1;

	paramFileStream.close();

	return paramString;
}



