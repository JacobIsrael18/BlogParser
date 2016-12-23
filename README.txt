Hello,

To compile and run this code:

1. Please place all files in a single folder.
.cpp  .h and the makefile

2. use the 'make' utility by opening a Terminal and typing make <press enter>'

3. You should see output like
g++ -Wall -c BlogPost.cpp
g++ -Wall -c SimpleHTTP.cpp
g++ -Wall -o BlogParser BlogParser.cpp BlogPost.o SimpleHTTP.o

4. To run the App, make sure you have a network connection and type
 ./BlogParser  <press enter>


Please note:
A. There is no way to catch every error.
This is an assignment and covering for every possible fault (especially with network code) would take many more hours.
B. Very often, the server appears to ignore our request for a connection, resulting in an ETIMEDOUT.
Other times, the server gives a 404 claiming that:
""


Thank you,
Jacob
