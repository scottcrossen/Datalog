Flags=-Wall
Source=test.cpp
Output=test
CC=g++

.PHONY: all $(Output) clean

all:
	$(CC) $(Flags) -o $(Output) $(Source) && ./$(Output)
