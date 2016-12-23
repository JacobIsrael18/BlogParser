/****************************
RestFileReader.cpp
 
 A class that models a single post
 Created by newcomp on 12/21/16.
 *******************************/

#include <regex>
#include "RestFileReader.h"
// #include <string>

private:
uint32_t dictionaryListSize;

// typedef pair<const Key, T> value_type;
map<string, string, compare, allocator> dictionaryList;
//template < class Key,                                     // map::key_type
//class T,                                       // map::mapped_type
//class Compare = less<Key>,                     // map::key_compare
//class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
//> class map;

public:


void readFile(string fileContents){
    // The file should e surrounded by square brackets.
    // Ignore characters before/after these (Stops some Microsoft bugs)
    uint32_t startIndex = fileContents.lfind("[");
    uint32_t endIndex = fileContents.lfind("]");
    
    if(startIndex >= endIndex){
        //  @TODO Throw an Error
        printf("FAILURE 8172531324 Invalid input. %d >= %d", startIndex, endIndex );
        return;
    }
    
    // Remove the square brackets
    startIndex++ ;
    endIndex-- ;
    fileContents = fileContents.substr(startIndex, endIndex - startIndex));
    
    // Iterate through
    regex integer("(\\+|-)?[[:digit:]]+");
    
    
    if(regex_match(input,integer)){
        
        
        
    }
}
