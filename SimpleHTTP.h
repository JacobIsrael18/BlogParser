/****************************
 SimpleHTTP.h
 
 A class that models a single post
 Created by newcomp on 12/21/16.
 *******************************/
#ifndef SimpleHTTP_h
#define SimpleHTTP_h

#define PORT_80 80
#define PORT_6969 6969

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class SimpleHTTP{

private:
    bool messageResponseReceived;
    string hostName;
    string lastResponse;
public:
    SimpleHTTP(string newHostName) ;
    string urlEncode(string inputString);
    string urlDecode(string inputString);
    int connectToHost();
    int sendFileRequestToHostOnSocket(string fileName, int socketNumber);
    void waitForResponseOnSocket(int socketNumber);
    string getLastResponse();
    void processHTTPResponse(string response);
    void closeSocket(int socketNumber);

};
#endif // SimpleHTTP_h
