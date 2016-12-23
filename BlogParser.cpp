/****************************
 BlogParser.cpp
 
 A class that models a single post
 Created by Jacob Israel on 12/21/16.
 *******************************/
#include "BlogPost.h"
#include "SimpleHTTP.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

/*! ===========================
 @function
 @discussion
 @param
 ============================= */
void processHTTPResponse(string response){
    
    string okString = "200 OK";
    string lineBreak = "-----------------------------------------------------------------------\n";
    
    size_t index = response.find(okString);
    if ( index >= response.length() ){
        printf("FAILURE 896534234 Server Response is NOT 200 OK\n%s\n", response.c_str() );
        return;
    }
    
    string contentString = "Content-Length:";
    
    index = response.find(contentString);
    if ( index >= response.length() ){
        printf("Warning: Server Response has no Content-Length\n");
    }
    else{
        response = response.substr(index, response.length() - index);
    }
    
    index = 0;
    // Trim away any newlines or spaces
    while (index < response.length() && response[index] <= ' ') {
        index++ ;
    }
    
    if(index < response.length() ){
        response = response.substr(index, response.length() - index);
    }
    
    index = response.find("[");
    size_t index2 = response.find_last_of("]");
    
    if(index > response.length() || index2 > response.length() ||  index >= index2 ||  index == string::npos ||  index2 == string::npos){
        printf("FAILURE 0945123123 Response has no array %lu >= %lu", index, index2);
        return;
    }
    
    response = response.substr(index+1, index2 - index - 1);
    //  printf("TRIMMED RESPONSE:\n%s\n\n", response.c_str() );
    
    index = index2 = 0;
    
    while(index < response.length() && index2 < response.length() && index2 != string::npos) {
        index = response.find("{");
        index2 = response.find("}");
        
        if(index < response.length() && index2 < response.length() && index < index2 && index2 < response.length() && index2 != string::npos){
            index += 1;
            string nextString = response.substr(index, index2 - index);
            index2 += 1;
            if(index2 < response.length() && index2 != string::npos){
                response = response.substr(index2, response.length() - index2);
            }
            cout << lineBreak;
            BlogPost blogPost = BlogPost(nextString);
            
            blogPost.print();
        }
    }
    cout << lineBreak;
}


/*! ===========================
 @function   main
 @discussion
 ============================= */
int main(int argc, char *argv[])
{
    //#define DEBUG
    
    string  hostName = "demo7701733.mockable.io";
    // IP Address	216.58.193.83          - 558,698 other sites hosted on this server
    //   IP Location	United States - California - Mountain View - Google Inc.
    
    SimpleHTTP simpleHTTP = SimpleHTTP(hostName);
#ifdef DEBUG
    printf("Connecting to %s\n", hostName.c_str() );
#endif
    int socketNumber = simpleHTTP.connectToHost();
    
    if(socketNumber > 0){
#ifdef DEBUG
        printf("Connected to host. Socket number : %d\n", socketNumber);
#endif
        int bytesDelivered = simpleHTTP.sendFileRequestToHostOnSocket("/posts", socketNumber);
        if(bytesDelivered > 0){
#ifdef DEBUG
            printf("Bytes Delivered %d\n", bytesDelivered);
#endif
            simpleHTTP.waitForResponseOnSocket(socketNumber);
            string responseString = simpleHTTP.getLastResponse();
            simpleHTTP.closeSocket(socketNumber);
            
            if(responseString.length() > 0){
                //     printf("Got response \n");
                cout << endl;
                processHTTPResponse(responseString);
            }
        }
    }
    
    return 0;
}

