Flags=-Wall -g -std=c++11
Source=test1.txt output1.txt
Main=main.cpp
Test=test.cpp
Output=program
CC=g++

.PHONY: all $(Output) clean
.PHONY: test $(Output) clean

all:
	$(CC) $(Flags) -o $(Output) $(Main) && ./$(Output) $(Source) && ./$(Output) && pmccabe *.h *.cpp && valgrind --leak-check=full ./$(Output) Source
test:
	$(CC) $(Flags) -o $(Output) $(Test) && ./$(Output) && pmccabe *.h *.cpp && valgrind --leak-check=full ./$(Output)