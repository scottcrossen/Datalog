Flags=-Wall -g -std=c++11
Source=input.txt output.txt
Main=main.cpp
Test=test
Output=program
CC=g++

.PHONY: all $(Output) clean
.PHONY: test $(Output) clean

all:
	$(CC) $(Flags) -o $(Output) $(Main) && ./$(Output) $(Source) && pmccabe *.h *.cpp && valgrind --leak-check=full ./$(Output) $(Source)
test:
	mv ./$(Test) ./$(Test).cpp && $(CC) $(Flags) -o $(Output) $(Test).cpp && ./$(Output) && pmccabe *.h *.cpp && valgrind --leak-check=full ./$(Output) && mv ./$(Test).cpp ./$(Test)