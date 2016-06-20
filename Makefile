Flags=-Wall
Source=NULL
main=NULL
Test=test.cpp
Output=program
CC=g++

.PHONY: all $(Output) clean
.PHONY: test $(Output) clean

all:
	$(CC) $(Flags) -o $(Output) $(Main) && ./$(Output)
test:
	$(CC) $(Flags) -o $(Output) $(Test) && ./$(Output)