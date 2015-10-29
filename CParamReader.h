/*
 * CParamReader.h
 *
 *  Created on: 12 Nov 2014
 *      Author: jtrusc
 *
 *      Each informative line of the param file should have the form:
 *      paramNumber (tab) Value (tab) ## Comments
 *      OR for vectors:
 *      paramNumber (tab) Value1 (single space) Value2 (single space) Value3 etc (tab) ## Comments
 *      Any line starting with '#' is completely ignored.
 *
 */ 

#ifndef CPARAMREADER_H_
#define CPARAMREADER_H_

#include <fstream>

#define BUFFER_SIZE 1024		// Define Buffer-size - dwefine piece of memory where it can stick things

class CParamReader
{
public:
    CParamReader();
    virtual ~CParamReader();	// destructor
    
    bool setNewFileName(char* filePath);		// return true or false
    char* getParamString(const char* paraName, int& nElements, int& rows, int& columns);		//
    
    
    // Members...
    std::ifstream paramFileStream;
    char* paramBuffer;
    char* filePathString;
};

#endif /* CPARAMREADER_H_ */