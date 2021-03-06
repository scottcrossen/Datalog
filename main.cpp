#include "scanner.h"
#include "parser.h"
#include "parserclasses.h"
#include "database.h"
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
  Parser parser=Parser();
  Database database=Database();
  scanner.initialize();
  parser.initialize();
  database.initialize();
  scanner.input_file(input_file);
  scanner.output_file(output_file);
  scanner.read_in();
  scanner.write_out();
  parser.output_file(output_file);
  parser.read_in(scanner.get_tokens());
  parser.build();
  parser.write_out();
  database.read_in(parser.build_objects());
  database.build_database();
  database.output_file(output_file);
  database.apply_rules();
  database.apply_queries();
  database.write_out();
  scanner.clear_tokens();
  parser.clear();
  database.clear();
  cout << "Program finished Successfully." << endl;
  return 0;
}
