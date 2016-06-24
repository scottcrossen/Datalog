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
 private:
  Debugger debug;
  Rules rules;
  TokenList token_list;
  string input_name;
  string output_name;
 public:
  Scanner(){
    debug=Debugger("Scanner");
    debug.flag(1);
    rules=Rules();
    token_list=TokenList();
    debug.output("Scanner object created.");
    input_name="test1.txt";
    output_name="output.txt";
  }
  ~Scanner(){
    debug.flag(2);
    debug.output("Scanner object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.turned_on=turn_on;
    token_list.debug_on(turn_on);
    rules.debug_on(turn_on);
  }
  void initialize(){
    debug.flag(3);
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
    debug.output("Initialize method accessed.");
  }
  void read_in(){
    ifstream file_in;
    file_in.open(input_name.c_str());
    if ((file_in.fail())) {file_in.close(); return;}
    int state=1; // 1 reading, 2 string, 3 comment
    string found_string;
    int line_string;
    unsigned line=1;
    while(!(file_in.eof())){
      char char_c=file_in.get();
      if (char_c=='\n') line++;
      if (char_c=='\377'){ token_list.add(rules.save_reset(line)); debug.output("End of file encountered.");}
      else if (char_c =='#' && state==1) state=3;
      else if (char_c =='\n' && state == 3) state=1;
      else if (char_c =='\'' && state==1){ state=2; token_list.add(rules.save_reset(line)); line_string=line;}
      else if (char_c == '\'' && state==2){state=1;token_list.add(Token("STRING","'"+found_string+"'",line));}
      else if (state == 2) found_string+=char_c;
      else if (char_c != ' ' && char_c !='\t' && char_c !='\n' && state==1) token_list.add(rules.add_char(char_c,line));
      }
    if( state==2){debug.output("Error: Unterminated string");
      token_list.add(Token("ERROR","Unterminated String",line_string));
    }
    token_list.add(Token("EOF"," ",line));
    token_list.remove_redundant();
    debug.output("Output of file:\n"+token_list.print_out());
    file_in.close();
    return;
  }
  void input_file(string filename){
    this->input_name=filename;
  }
  void output_file(string filename){
    this->output_name=filename;
  }
  void print(){
    cout << token_list.print_out() << endl;
  }
  void write_out(){
    debug.flag(4);
    ofstream file_out;
    file_out.open(output_name.c_str());
    file_out << token_list.print_out();
    file_out.close();
  }
  void clear_tokens(){
    token_list.clear();
  }
};
