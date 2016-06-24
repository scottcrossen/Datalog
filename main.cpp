#include "scanner.h"
#include <iostream>
using namespace std;
int main(){
  cout << "Program Compiled Successfully." << endl;
  Scanner scanner=Scanner();
  scanner.initialize();
  scanner.input_file("./test1.txt");
  scanner.output_file("./output1.txt");
  scanner.read_in();
  scanner.write_out();
  scanner.clear_tokens();
  scanner.input_file("./test2.txt");
  scanner.output_file("./output2.txt");
  scanner.read_in();
  scanner.write_out();
  scanner.clear_tokens();
  scanner.input_file("./test3.txt");
  scanner.output_file("./output3.txt");
  scanner.read_in();
  scanner.write_out();
  scanner.clear_tokens();
  scanner.input_file("./test4.txt");
  scanner.output_file("./output4.txt");
  scanner.read_in();
  scanner.write_out();
  scanner.clear_tokens();
  return 0;
}
