#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "tokenlist.h"
#include "debugger.h"
#include "rules.h"
#include "token.h"
#pragma once
class Scanner{
 public:
  Scanner(){
    debug=Debugger("Scanner");
    debug.flag(1);
    rules=Rules();
    token_list=TokenList();
    input_name="test1.txt";
    output_name="output.txt";
    debug.output(2, "Scanner object created.");
  }
  ~Scanner(){
    debug.flag(3);
    debug.output(4,"Scanner object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.flag(5);
    debug.turned_on=turn_on;
    token_list.debug_on(turn_on);
    rules.debug_on(turn_on);
    debug.output(6,"Debug turned on.");
  }
  void initialize(){
    debug.flag(7);
    rules.add_exp(",","COMMA");
    rules.add_exp(".","PERIOD");
    rules.add_exp("?","Q_MARK");
    rules.add_exp("(","LEFT_PAREN");
    rules.add_exp(")","RIGHT_PAREN");
    rules.add_exp(":","COLON");
    rules.add_exp(":-","COLON_DASH");
    rules.add_exp("Schemes","SCHEMES");
    rules.add_exp("Facts","FACTS");
    rules.add_exp("Rules","RULES");
    rules.add_exp("Queries","QUERIES");
    rules.add_exp("[A-Za-z][A-Za-z0-9]*","ID");
    //rules.add_exp("'[]*'","STRING");
    debug.output(8,"Initialize method accessed.");
  }
  void read_in(){
    debug.flag(9);
    ifstream file_in;
    file_in.open(input_name.c_str());
    if ((file_in.fail())) {file_in.close(); return;}
    int state=1; // 1 reading, 2 string, 3 comment
    string found_string;
    int line_string;
    unsigned line=1;
    while(!(file_in.eof())){
      debug.flag(10);
      char char_c=file_in.get();
      if (char_c=='\n') line++;
      if (char_c=='\377'){ token_list.add(rules.save_reset(line)); debug.output(11,"End of file encountered.");}
      else{
	proccess_char(char_c, line, line_string, found_string, state);
      }
    }
    if( state==2){debug.output("Error: Unterminated string");
      token_list.add(Token("ERROR","Unterminated String",line_string));
    }
    token_list.add(Token("EOF"," ",line));
    token_list.remove_redundant();
    debug.output(12,"File read in. Tokens:\n"+token_list.print_out());
    file_in.close();
    return;
  }
  void input_file(string filename){
    debug.flag(13);
    this->input_name=filename;
    debug.output(14,"Input file renamed to "+filename);
  }
  void output_file(string filename){
    debug.flag(15);
    this->output_name=filename;
    debug.output(16,"Output file renamed to "+filename);
  }
  void print(){
    debug.flag(17);
    cout << token_list.print_out() << endl;
    debug.output(18,"Print method accessed.");
  }
  void write_out(){
    debug.flag(19);
    ofstream file_out;
    file_out.open(output_name.c_str());
    file_out << token_list.print_out();
    file_out.close();
    debug.output(20,"File written out.");
  }
  void clear_tokens(){
    debug.flag(21);
    token_list.clear();
    debug.output(22,"Tokens Cleared.");
  }
 private:
  Debugger debug;
  Rules rules;
  TokenList token_list;
  string input_name;
  string output_name;
  void proccess_char(char &char_c, unsigned &line, int &line_string, string &found_string, int &state){
    switch(state){
    case 1: case1(char_c, line, line_string, found_string, state);
      break;
    case 2: case2(char_c, line, line_string, found_string, state);
      break;
    case 3: case3(char_c, line, line_string, found_string, state);
      break;
    }
  }
  void case1(char &char_c, unsigned &line, int &line_string, string &found_string, int &state){
    if (char_c =='#') state=3;
    else if (char_c =='\''){ state=2; token_list.add(rules.save_reset(line)); line_string=line;}
    else if (char_c != '\377' && char_c != ' ' && char_c !='\t' && char_c !='\n') token_list.add(rules.add_char(char_c,line));
  }
  void case2(char &char_c, unsigned &line, int &line_string, string &found_string, int &state){
    found_string+=char_c;
    if (char_c == '\''){state=1;token_list.add(Token("STRING","'"+found_string+"'",line));}

  }
  void case3(char &char_c, unsigned &line, int &line_string, string &found_string, int &state){
    if (char_c =='\n') state=1;
  }
};
