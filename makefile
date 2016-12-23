CHOSEN_COMPILER=g++
COMPILER_OPTIONS= -Wall
SOURCE_FILES=BlogParser.cpp BlogPost.cpp SimpleHTTP.cpp
OBJECTS=$(SOURCE_FILES:.cpp=.o)
EXECUTABLE=BlogParser

all: BlogParser BlogPost.o SimpleHTTP.o BlogPost.cpp BlogPost.h SimpleHTTP.cpp SimpleHTTP.h

BlogParser : BlogParser.cpp BlogPost.o SimpleHTTP.o
	$(CHOSEN_COMPILER) $(COMPILER_OPTIONS) -o BlogParser BlogParser.cpp BlogPost.o SimpleHTTP.o

BlogPost.o : BlogPost.cpp BlogPost.h
	$(CHOSEN_COMPILER) $(COMPILER_OPTIONS) -c BlogPost.cpp

SimpleHTTP.o : SimpleHTTP.cpp SimpleHTTP.h
	$(CHOSEN_COMPILER) $(COMPILER_OPTIONS) -c SimpleHTTP.cpp

clean:
	rm *.o
	rm BlogParser
	ls
