Hello,

If you want to run this project as a Dynamic Library, please go to:

    https://github.com/JacobIsrael18/BlogParserLibrary


To compile and run this code:

1. Please place all files in a single folder.
.cpp  .h and the makefile

2. use the 'make' utility by opening a Terminal and typing:

         make <press enter>

3. You should see output like:
g++ -Wall -c BlogPost.cpp
g++ -Wall -c SimpleHTTP.cpp
g++ -Wall -o BlogParser BlogParser.cpp BlogPost.o SimpleHTTP.o

4. To run the App, make sure you have a network connection and type:

    ./BlogParser  <press enter>

                  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

Please note:
A. There is no way to catch every error.
This is an assignment and covering for every possible fault (especially with network code) would take many more hours.
B. Very often, the server appears to ignore our request for a connection, resulting in an ETIMEDOUT.
Other times, the server gives a 404 claiming that:

HTTP/1.1 404 Not Found
Date: Fri, 23 Dec 2016 03:08:48 GMT
Server: Apache
Content-Length: 203
Connection: close
Content-Type: text/html; charset=iso-8859-1

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>404 Not Found</title>
</head><body>
<h1>Not Found</h1>
<p>The requested URL /posts was not found on this server.</p>
</body></html>

But, there seems to be no reason why the
/posts  url
is suddenly non-existent.

Seconds or minutes later, everything suddenly works again:

-----------------------------------------------------------------------
Family Trip to the Grand Cannon
This summer I took a trip with my family to the Grand Canyon.  It was a long drive and my sister got sick in the car.  It was great!
-----------------------------------------------------------------------
I went Swimming in my Pool
This summer I went swimming in my pool with my friends.  We had a great time and I got sun burned
-----------------------------------------------------------------------
We got a Dog
My Dad got us a Dog, his name is Ruffles.  He is brown and went potty on the kitchen floor.
-----------------------------------------------------------------------
I went to Camp
I went to summer camp and we went to the Zoo and the Water Park.
-----------------------------------------------------------------------
Slept In
My Mom let me sleep as late as I wanted.  One day I stayed in my pajamas all day!
-----------------------------------------------------------------------

Using WireShark on the browser reveals SSL packets going back and forth between the browser and Google's' REST Server. This is because the browser sends "Upgrade-Insecure-Requests: 1" for its Content-Security-Policy. Maybe this assignment is a little more advanced than I anticipated.

Thank you,
Jacob
