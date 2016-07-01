#include "scanner.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[]){
  cout << "Program Compiled Successfully." << endl;
  string input_file;
  string output_file;
  
  if (argc>3 || argc <3){
    cout << "Only " << argc-1 << " arguments supplied, Usage is <file_in> <file_out>" << endl;
    exit(0);
  } else {
    input_file=string(argv[1]);
    output_file=string(argv[2]);
  }
  cout << "Reading in from file:  " << input_file << endl;
  cout << "Writing out from file: " << output_file << endl;
  Scanner scanner=Scanner();
  scanner.initialize();
  scanner.input_file(input_file);
  scanner.output_file(output_file);
  scanner.read_in();
  scanner.write_out();
  parser.output_file(output_file);
  parser.read_in(scanner.get_tokens());
  parser.build();
  parser.write_out();
  scanner.clear_tokens();
  parser.clear();
  cout << "Program finished Successfully." << endl;
  return 0;
}
