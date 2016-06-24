#include <iostream>
#include "debugger.h"
#include "scanner.h"

int main(){
  cout << "Program Compiled Successfully." << endl;
  Debugger debug=Debugger("Main");
  debug.flag(1);
  Scanner scanner=Scanner();
  scanner.debug_on(true);
  scanner.initialize();
  debug.flag(2);
  scanner.input_file("./test1.txt");
  scanner.output_file("./output1.txt");
  scanner.read_in();
  scanner.write_out();
  debug.output(3, "Test 1 output:");
  scanner.print();
  scanner.clear_tokens();
  scanner.input_file("./test2.txt");
  scanner.output_file("./output2.txt");
  scanner.read_in();
  scanner.write_out();
  debug.output(4, "Test 2 output:");
  scanner.print();
  scanner.clear_tokens();
  scanner.input_file("./test3.txt");
  scanner.output_file("./output3.txt");
  scanner.read_in();
  scanner.write_out();
  debug.output(5, "Test 3 output:");
  scanner.print();
  scanner.clear_tokens();
  scanner.input_file("./test4.txt");
  scanner.output_file("./output4.txt");
  scanner.read_in();
  scanner.write_out();
  debug.output(6, "Test 4 output:");
  scanner.print();
  scanner.clear_tokens();
  debug.output(7,"End of main reached.");
  return 0;
}
