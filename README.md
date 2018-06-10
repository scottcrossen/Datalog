# Datalog

A declarative language.

### Description

I originally built this project to pass off the requirements for a class assignment.

### Explanatory Note

I created this project before I learned better practices. As such, it's not my best work, but it does help demonstrate the creativity I had even when I was learning.

### Instructions

- A Makefile is included.
  - "make all" makes the final product with input file named "input.txt" and output file named "output.txt".
  - "make test" makes a testing code with the debug console turned on. It runs the included test files and displays errors. The test.cpp is renamed in the process so when the code is turned in and finalized, the .cpp won't be used.
  - each makefile execution also runs a complexity test and a valgrind memory check.
- A "Debug.h" class is included. This allows for the functionality to have a status-print type interface helpful when debugging. It is easily turned off (for when the code is finalized.) by changing the argument in the constructor to Debugger(false) rather than Debugger(true) (which turns it on).

### Contributors

1. Scott Leland Crossen  
<http://scottcrossen.com>  
<scottcrossen42@gmail.com>  
