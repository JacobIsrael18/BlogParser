/****************************
 SimpleHTTP.cpp
 
 Created by Jacob Israel on 12/21/16.
 *******************************/
#include "SimpleHTTP.h"

//  Network
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include<errno.h>

const static uint32_t BUFFER_SIZE = 4096;

/*! ===========================
  @function     Constructor
  @discussion
 Set the hostName for this instance
 ============================= */
SimpleHTTP::SimpleHTTP(string newHostName) : hostName(newHostName){
    lastResponse = "";
}

/*! ===========================
 @function       getRemoteIPAddressForAddressOnPort:
 @discussion
 Go to the hardware and ask for a lookup based on hostname.
 Then get the IP Address (IPv4 / IPv6)
 Make sure it is not the LOOPBACK adddress.
 
 1. Create a addrinfo hint
 2. Use the hint to get an addrinfo* linked-list
 3. Search the linked-list for an IPv4 and/or IPv6 address
 sockaddr_in    sockaddr_in6
 @param
 A String containing the host name
 @param
 The port number to bind to in LITTLE ENDIAN FORMAT
 @return
 A new sockaddr_storage, which really contains a
 sockaddr_in or  sockaddr_in6
 ============================= */
struct sockaddr_storage getRemoteIPAddressForAddressOnPort(string remoteAddress, uint16_t remotePortNumber) {
    
    uint16_t networkPortNumber = htons(remotePortNumber);
    char remotePortString[6]; // Five characters plus the NULL terminator
    sprintf(remotePortString, "%d",  networkPortNumber);
    remotePortString[5] = '\0';
    
    const char* addressString = remoteAddress.c_str();
    
    struct addrinfo addressInformationHint = {0};
    memset(&addressInformationHint, 0, sizeof(addressInformationHint));
    /*
     int             ai_flags;
     int             ai_family;
     int             ai_socktype;
     int             ai_protocol;
     size_t          ai_addrlen;
     char            *ai_canonname;
     struct sockaddr  *ai_addr;
     struct addrinfo  *ai_next;
     */
    
    // addressInformationHint.ai_flags = AI_PASSIVE;//AI_DEFAULT; //    AI_NUMERICHOST;//// AI_PASSIVE;
    addressInformationHint.ai_family = PF_UNSPEC;   // IPv4 or IPv6       AF_UNSPEC
    addressInformationHint.ai_socktype = SOCK_STREAM;
    addressInformationHint.ai_protocol = IPPROTO_TCP;
    //    memcpy(addressInformationHint.ai_addr->sa_data,  &networkPortNumber,  sizeof(uint16_t ));
    //    memcpy(addressInformationHint.ai_addr->sa_data + 2,  &addressString,  remoteAddress.length() );
    
    struct sockaddr_storage addressCopy;
    addressCopy.ss_family = AF_UNSPEC;
    
    struct addrinfo* addressInformationLinkedList;
    
    // printf("getaddrinfo() Address: %s  Port: %s  \n",  addressString,  remotePortString);
    
    
    int returnCode = getaddrinfo(addressString, remotePortString, &addressInformationHint, &addressInformationLinkedList);
    //    int returnCode = getaddrinfo(
    //                addressString,    //  "www.companyWebsite.com" or IP
    //                remotePortString,    //   port number or "http" or "ftp" or "telnet" or "smtp"         remotePortString,
    //                &addressInformationHint, // struct addrinfo  Hints
    //                &addressInformationLinkedList // <=== return value
    //    );
    
    if (addressInformationLinkedList == NULL) {
        const char* errorString = gai_strerror(returnCode);
        printf("FAILURE: 02913764 Didn't to get an  addrinfo      Linked List is NULL\n%s \n", errorString);
        return addressCopy; // Error     sa_family = AF_UNSPEC;
    }
    
    struct addrinfo* addressInformationPtr = addressInformationLinkedList;
    
    for( ; addressInformationPtr != NULL ; addressInformationPtr = addressInformationPtr->ai_next) {
        
        // *** Looking ONLY for TCP at this time. ***
        if (addressInformationPtr->ai_socktype == SOCK_DGRAM || addressInformationPtr->ai_protocol ==  IPPROTO_UDP) {
            continue;
        }
        
        
        if(addressInformationPtr->ai_addr->sa_family == AF_INET || addressInformationPtr->ai_addr->sa_family == AF_INET6){
            // _____IPv4____________________
            if(addressInformationPtr->ai_addr->sa_family == AF_INET){
                
                
                struct sockaddr_in ipv4Address;
                ipv4Address.sin_family = AF_INET;
                ipv4Address.sin_len = sizeof(struct sockaddr_in);
                
                // Port number takes the first 2 bytes
                ipv4Address.sin_port = addressInformationPtr->ai_addr->sa_data[0];
                ipv4Address.sin_port += addressInformationPtr->ai_addr->sa_data[1] << 8;
                
                ipv4Address.sin_addr.s_addr = 0;
                
                for(uint8_t i = 0 ; i < 4 ; i++){
                    ipv4Address.sin_addr.s_addr +=  addressInformationPtr->ai_addr->sa_data[i+2] << (i * 8);
                }
                
                if( ipv4Address.sin_addr.s_addr == htonl(INADDR_LOOPBACK)){
                    continue;
                }
                
                if( ipv4Address.sin_addr.s_addr ==  INADDR_LOOPBACK){
                    continue;
                }
                
                ipv4Address.sin_port = networkPortNumber;
                
                // We are done with the linked list
                freeaddrinfo(addressInformationLinkedList);
                
                //      printf("\n\n%d   %d  \n\n", ipv4Address.sin_port ,  ipv4Address.sin_addr.s_addr );
                
                return *(struct sockaddr_storage*)&ipv4Address;
            }
            // _____IPv6____________________
            else{ // AF_INET6     @TODO IPV6 CODE HAS NOT BEEN TESTED
                struct sockaddr_in6 ipv6Address;
                ipv6Address.sin6_family = AF_INET6;
                ipv6Address.sin6_len = sizeof(struct sockaddr_in6);
                memcpy(ipv6Address.sin6_addr.__u6_addr.__u6_addr8 , addressInformationPtr->ai_addr->sa_data + 2, sizeof(ipv6Address.sin6_addr.__u6_addr));
                
                bool isIPv6LoopBack = true;
                for(int j = 0 ; j < 16 ; j++){
                    if( ipv6Address.sin6_addr.s6_addr[j] == in6addr_loopback.s6_addr[j] ){
                        isIPv6LoopBack = false;
                        break;
                    }
                }
                if(isIPv6LoopBack){
                    continue;
                }
                
                ipv6Address.sin6_port = networkPortNumber;
                
                // We are done with the linked list
                freeaddrinfo(addressInformationLinkedList);
                return *(struct sockaddr_storage*)&ipv6Address;
            }
        }
    }
    
    // We are done with the linked list
    freeaddrinfo(addressInformationLinkedList);
    
    return addressCopy;
}

/*! ===========================
 @function  connectToHost
 @discussion 
 Get the server's IP address and connect to it (TCP)
 @return the socket we are connected on
 ============================= */
int SimpleHTTP::connectToHost(){
    int result;
    sockaddr_storage ipAddress = getRemoteIPAddressForAddressOnPort(hostName, PORT_80);
    //    struct sockaddr_in* remoteIPv4Address;
    //    struct sockaddr_in6* remoteIPv6Address;
    socklen_t sizeOfServerAddress;
    
    if(ipAddress.ss_family == AF_INET){ // IPv4
        //        remoteIPv4Address = (struct sockaddr_in*)&ipAddress ;
        sizeOfServerAddress = sizeof(struct sockaddr_in);
    }
    else{ // AF_INET6
        //        remoteIPv6Address = (struct sockaddr_in6*)&ipAddress;
        sizeOfServerAddress = sizeof(struct sockaddr_in6);
    }
    
    int socketNumber = socket(ipAddress.ss_family, SOCK_STREAM,0);
    if(socketNumber <= 0){
        printf("FAILURE 1209785243  socket() falied for %d. Error: %d", ipAddress.ss_family, errno);
    }
    else{
        result = connect(socketNumber, (const struct sockaddr*) &ipAddress, sizeOfServerAddress);
        
        if(result != 0){
            close(socketNumber);
            printf("FAILURE 457148253 connect() falied. Error: %d  %d\n", errno, result);
            return - 1;
        }
    }
    return socketNumber;
}

/*! ===========================
 @function    sendFileRequestToHostOnSocket(string fileName, int socketNumber)
 @discussion
 @param fileName - the resource we are looking for
 @param socketNumber - the socket to use
 @return number of bytes that were sent or -1 from send()
 ============================= */
int SimpleHTTP::sendFileRequestToHostOnSocket(string fileName, int socketNumber)
{
    string newLine = "\r\n";
    
    string httpMessage  = "GET " + fileName + " HTTP/1.1" + newLine + "Host: " + hostName + newLine + "Connection: keep-alive" + newLine + "Cache-Control: max-age=0" + newLine + "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8" + newLine + "Upgrade-Insecure-Requests: 1" + newLine + "Accept-Encoding: gzip, deflate, lzma, sdch" + newLine + "Accept-Language: en-US,en;q=0.8" + newLine + newLine;
    
    // printf("sendFileRequestToHostOnSocket  \n%s\nSocket:\n%d\n", httpMessage.c_str() , socketNumber);
    
    int bytesToSend = httpMessage.length();
    
    ///                                       socket                       buffer                   size       flags
    int bytesSent = send(socketNumber, (char*)httpMessage.c_str(), bytesToSend , 0);
    if(bytesSent != bytesToSend){
        printf("FAILURE 86285394  send() %d != %d\n", bytesSent, bytesToSend);
    }
    
    return bytesSent;
}

/*! ===========================
 @function     waitForResponseOnSocket(int socketNumber)
 @discussion
 This is a seperate function so that we can eventually call it 
 on a background thread and add a callback.
 @param the socket to use
 ============================= */
//                                                                                          (void)(*callBack)()
void SimpleHTTP::waitForResponseOnSocket(int socketNumber){///string remoteAddress, string message){
    
    // @TODO loop data into buffer and move it to  lastResponse
    char inputBuffer[BUFFER_SIZE];
    
    //  . . . .  . . . .  . . . .  . . . . Blocking call . . . .  . . . .  . . . .  . . . .  . . . .
    int totalBytes = recv(socketNumber, inputBuffer, sizeof(inputBuffer) - 1, 0);
    
    if(totalBytes <= 0) {
        printf("FAILURE 012973654 Could not receive any return message.  %d", totalBytes);
        return;
    }
    if(totalBytes > 0 && totalBytes < BUFFER_SIZE){
        inputBuffer[totalBytes] = '\0'; /// end terminate string
    }
    inputBuffer[BUFFER_SIZE - 1] = '\0'; /// end terminate for safety
    
    messageResponseReceived = true;
    
    // printf("messageResponseReceived %d bytes   \n%s\n", totalBytes,  inputBuffer);
    
    if(totalBytes > 0){
        lastResponse = inputBuffer;
    }
    
    // Clear the buffer  (Security)
    memset(inputBuffer, 0, sizeof(inputBuffer) );
}

/*! ===========================
 @function     getLastResponse
 @discussion
 Normally, you would call this right after a callback notified you 
 that there was a sever response.
Optionally, we could hold an array or responses, 
 or a dictionary, keyed by aa request tag.
 @return The last response fom the server.
 ============================= */
string SimpleHTTP::getLastResponse(){
    return lastResponse;
}

/*! ===========================
 @function   trimWhiteSpace
 @discussion
 Not used yet
 @param the string to trim
 @return the trimmed result
 ============================= */
string trimWhiteSpace(string inputString){
    
    size_t index = 0, index2 = inputString.length();
    while (index < inputString.length() && inputString[index] <= ' ') {
        index++ ;
    }
    
    while (index2 > 0 && inputString[index2 - 1] <= ' ') {
        index2-- ;
    }
    return inputString.substr(index, index2 - index);
}

/*! ===========================
 @function    closeSocket
 @discussion
 We could just call close()
 But, this class may eventually hold its socket number internally
 @param The socket we no longer need.
 ============================= */
void SimpleHTTP::closeSocket(int socketNumber){
    close(socketNumber);
    // int temp = mySocketNumber;
    // mySocketNumber = INVALID_SOCKET;
    //  close(temp);
}
