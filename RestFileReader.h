/****************************
 RestFileReader.h
 
 A class that models a single post
 Created by newcomp on 12/21/16.
 *******************************/
#ifndef RestFileReader_h
#define RestFileReader_h

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class RestFileReader{
    

/*! ===========================
 @function
 @discussion
 @param
 @return
 ============================= */
    void readFile(String fileContents);

/*! ===========================
 @function
 @discussion
 @param
 @return
 ============================= */
    uint32_t getDictionarySize;

/*! ===========================
 @function
 @discussion
 @param
 @return
 ============================= */
    String* getDictionary;
};
#endif // RestFileReader_h
