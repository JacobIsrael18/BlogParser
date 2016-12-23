/****************************
  BlogPost.cpp
  
A class that models a single post
  Created by Jacob Israel on 12/21/16.
*******************************/
#include "BlogPost.h"
#include <regex.h>

// Prototypes
string findStringForQuotedKeyInString(string key, string sourceString);
int findIntegerForQuotedKeyInString(string key, string sourceString);

/*! ===========================
 @function Constructor
 ============================= */
BlogPost::BlogPost(string dictionaryContents){
    
    userID = findIntegerForQuotedKeyInString("userId", dictionaryContents);
    blogID = findIntegerForQuotedKeyInString("id", dictionaryContents);
    title = findStringForQuotedKeyInString("title", dictionaryContents);
    body = findStringForQuotedKeyInString("body", dictionaryContents);
}

/*! ===========================
 @function   findStringForQuotedKeyInString
 
 ============================= */
string findStringForQuotedKeyInString(string key, string sourceString){
    
    key = "\"" + key + "\"";
    size_t index = sourceString.find(key);
    
    if(index >=  sourceString.length() || index == string::npos){
        printf("Warning key not found: %s\n", key.c_str() );
        return "";
    }
    index += key.length() ;
    
    sourceString = sourceString.substr(index, sourceString.length() - index);
    
    // There must be a double-quote
    char* lastCharacter = ((char*) sourceString.c_str() + sourceString.length() - 1);
    char* characterPtr = strstr(sourceString.c_str() , "\"" );
    if(characterPtr == NULL || characterPtr >= lastCharacter){
        return "";
    }
    
    characterPtr++ ;
    
    char* characterPtr2 = characterPtr + 1;
    while (characterPtr2 < lastCharacter && *characterPtr2 != '"') {
        characterPtr2++ ;
    }
    
    string resultString = characterPtr;
    resultString = resultString.substr(0, characterPtr2 - characterPtr);
    
    return resultString;
}

/*! ===========================
 @function
 ============================= */
int findIntegerForQuotedKeyInString(string key, string sourceString){
    key = "\"" + key + "\"";
    
    char* characterPtr = strstr(sourceString.c_str() , key.c_str() );
    if(characterPtr == NULL){
            return -1;
    }
    
    characterPtr += key.length();
    
    if (sourceString.length() == 0) {
        return -1;
    }
    
    // Find the first digit
    char* lastCharacter = ((char*) sourceString.c_str() + sourceString.length() - 1);
    while (characterPtr < lastCharacter && (*characterPtr < '0' || *characterPtr > '9' ) ) {
        characterPtr++ ;
    }
    
    if (characterPtr > lastCharacter) {
        return -1;
    }
    
    // Assignnment operator
    sourceString = characterPtr;
    
    int resultInteger = std::stoi (sourceString);
    return resultInteger;
}

/*! ===========================
 @function
 ============================= */
void BlogPost::setUserID(int newValue){
    userID = newValue;
}

/*! ===========================
 @function
 ============================= */
void BlogPost::setID(int newValue){
    blogID = newValue;
}

/*! ===========================
 @function
 ============================= */
void BlogPost::setTitle(string newValue){
    title = newValue;
}

/*! ===========================
 @function
 ============================= */
void BlogPost::setBody(string newValue){
    body = newValue;
}

/*! ===========================
 @function
 ============================= */
int BlogPost::getUserID(){
    return userID;
}

/*! ===========================
 @function
 ============================= */
int BlogPost::getID(){
    return blogID;
}

/*! ===========================
 @function
 ============================= */
string BlogPost::getTitle(){
    return title;
}

/*! ===========================
 @function
 ============================= */
string BlogPost::getBody(){
    return body;
}


/*! ===========================
 @function
 @discussion
 Bonus Points
  Change your program to be a dynamic library.
  Provide documentation on entry points into your library as well as a new executable application that consumes your library.
  Provide build steps on how to build both the library and application
 
 
 On Mac OS X, compile with:
 
 g++ -dynamiclib -flat_namespace myclass.cc -o myclass.so
 g++ class_user.cc -o class_user
 
 
 On Linux, compile with:
 
 g++ -fPIC -shared myclass.cc -o myclass.so
 g++ class_user.cc -ldl -o class_user
 @param
 @return
 ============================= */

/*! ===========================
 @function
 @discussion
 print method should loop over the list and print the posts
 
 Sample Ouput
 ---------------------------------------------------------------------
 Family Trip to the Grand Canyon
 This summer I took a trip with my family to the Grand Canyon.
 ---------------------------------------------------------------------
 I went Swimming in my Pool
 This summer I went swimming in my pool with my friends.
 ---------------------------------------------------------------------
 @param
 @return
 ============================= */
void BlogPost::print(){
    cout <<  title << endl << body << endl;
}

