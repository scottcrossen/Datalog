  /$$$$$$   /$$$$$$         /$$$$$$   /$$$$$$   /$$$$$$ 
 /$$__  $$ /$$__  $$       /$$__  $$ /$$__  $$ /$$__  $$
| $$  \__/| $$  \__/      |__/  \ $$|__/  \ $$| $$  \__/
| $$      |  $$$$$$         /$$$$$$/   /$$$$$/| $$$$$$$ 
| $$       \____  $$       /$$____/   |___  $$| $$__  $$
| $$    $$ /$$  \ $$      | $$       /$$  \ $$| $$  \ $$
|  $$$$$$/|  $$$$$$/      | $$$$$$$$|  $$$$$$/|  $$$$$$/
 \______/  \______/       |________/ \______/  \______/ 
 
BYU CS 236 project
OWNER: Scott Leland Crossen
CONTRIBUTERS:  Scott Leland Crossen

SUMMARY:
For the CS 236 class of byu, a long-term project is required. This is the repository including all of the code used.

INSTRUCTIONS:
- A Makefile is included.
  - "make all" makes the final product with input file named "input.txt" and output file named "output.txt".
  - "make test" makes a testing code with the debug console turned on. It runs the included test files and displays errors. The test.cpp is renamed in the process so when the code is turned in and finalized, the .cpp won't be used.
  - each makefile execution also runs a complexity test and a valgrind memory check.
- A "Debug.h" class is included. This allows for the functionality to have a status-print type interface helpful when debugging. It is easily turned off (for when the code is finalized.) by changing the argument in the constructor to Debugger(false) rather than Debugger(true) (which turns it on).

CONTACT:
Scott Leland Crossen	  scottcrossen42@gmail.com  	scottcrossen42.com
