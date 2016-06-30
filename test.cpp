#include <iostream>
#include "debugger.h"
#include "scanner.h"
#include "parser.h"
using namespace std;
int main(){
  // Start program:
  cout << "Program Compiled Successfully." << endl;


  // Create objects:
  Debugger debug=Debugger("Main");
  Scanner scanner=Scanner();
  Parser parser=Parser();


  // Turn on debugs:
  debug.flag(1);
  //scanner.debug_on(true);
  parser.debug_on(true);


  // Initialize objects:
  debug.flag(2);
  scanner.initialize();
  parser.initialize();

  // Run tests:
  debug.flag(3);
/*
  scanner.input_file("./test_cases/in01.txt");
  scanner.output_file("./test_cases/output01.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(4, "Test 1 output:");
  //scanner.print();
  scanner.clear_tokens();
  
  scanner.input_file("./test_cases/in02.txt");
  scanner.output_file("./test_cases/output02.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(5, "Test 2 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in03.txt");
  scanner.output_file("./test_cases/output03.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(6, "Test 3 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in04.txt");
  scanner.output_file("./test_cases/output04.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(7, "Test 4 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in10.txt");
  scanner.output_file("./test_cases/output10.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(8, "Test 10 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in11.txt");
  scanner.output_file("./test_cases/output11.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(9, "Test 11 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in12.txt");
  scanner.output_file("./test_cases/output12.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(10, "Test 12 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in13.txt");
  scanner.output_file("./test_cases/output13.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(11, "Test 13 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in14.txt");
  scanner.output_file("./test_cases/output14.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(12, "Test 14 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in15.txt");
  scanner.output_file("./test_cases/output15.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(13, "Test 15 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in20.txt");
  scanner.output_file("./test_cases/output20.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(14, "Test 20 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in21.txt");
  scanner.output_file("./test_cases/output21.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(15, "Test 21 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in22.txt");
  scanner.output_file("./test_cases/output22.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(16, "Test 22 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in23.txt");
  scanner.output_file("./test_cases/output23.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(17, "Test 23 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in24.txt");
  scanner.output_file("./test_cases/output24.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(18, "Test 24 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in25.txt");
  scanner.output_file("./test_cases/output25.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(19, "Test 25 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in26.txt");
  scanner.output_file("./test_cases/output26.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(20, "Test 25 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in27.txt");
  scanner.output_file("./test_cases/output27.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(21, "Test 26 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in28.txt");
  scanner.output_file("./test_cases/output28.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(22, "Test 27 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in29.txt");
  scanner.output_file("./test_cases/output29.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(23, "Test 28 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in61.txt");
  scanner.output_file("./test_cases/output61.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(24, "Test 61 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./test_cases/in62.txt");
  scanner.output_file("./test_cases/output62.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(25, "Test 62 output:");
  //scanner.print();
  scanner.clear_tokens();

  scanner.input_file("./input.txt");
  scanner.output_file("./output.txt");
  scanner.read_in();
  scanner.write_out();
  //debug.output(26, "Test input output:");
  //scanner.print();
  scanner.clear_tokens();
*/

  // Finish program:
  debug.flag(27);
  cout << "Program Compiled Successfully." << endl;
  return 0;
}
