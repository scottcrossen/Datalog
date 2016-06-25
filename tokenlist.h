#include "debugger.h"
#include "token.h"
#include <sstream>
#include <string>
#include <vector>
#pragma once
class TokenList{
 public:
  TokenList(){
    debug=Debugger("Token A");
    debug.output(1,"Token array object created.");
  }
  ~TokenList(){
    debug.output(2,"Token array object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.flag(3);
    debug.turned_on=turn_on;
    for(unsigned iter=0; iter < token_list.size(); iter++){
      token_list[iter].debug_on(turn_on);
    }
    debug.output(4,"Debug turned on.");
  }
  void add(Token my_token){
    debug.flag(5);
    token_list.push_back(my_token);
    debug.flag(6);
  }
  void add(vector<Token> my_tokens){
    debug.flag(7);
    for(unsigned iter=0; iter< my_tokens.size(); iter++)
      token_list.push_back(my_tokens[iter]);
    debug.flag(8);
  }
  string print_out(){
    debug.flag(9);
    stringstream output;
    unsigned iter=0;
    for(iter=0; iter < token_list.size(); iter++){
      if(token_list[iter].type != "ERROR") output << token_list[iter].display() << endl;
      else{output << "Input Error on line " << token_list[iter].line << endl; break;}
    }
    if(iter==token_list.size()) output<< "Total Tokens = " << token_list.size();
    return output.str();
  }
  void remove_redundant(){
    debug.flag(10);
    for(unsigned iter=0; iter< token_list.size(); iter++){
      debug.flag(11);
      check_colondash(iter);
      check_id(iter);
    }
    debug.flag(12);
  }
  void clear(){
    debug.flag(13);
    for(unsigned iter=0; token_list.size() >0; iter++)
      token_list.pop_back();
    debug.output(14, "Tokens Cleared.");
  }
 private:
  Debugger debug;
  vector<Token> token_list;
  void check_colondash(unsigned iter){
    if(token_list[iter].value==":-"){
      for(unsigned iter2=iter; iter2 >=0 ; iter2--){
	if(token_list[iter2].value==":"){
	  token_list.erase(token_list.begin()+iter2);
	  break;
	}
      }
    }
  }
  void check_id(unsigned iter){
    if(token_list[iter].type=="ID"){
      for(unsigned iter2=0; iter2 <token_list.size(); iter2++){
	if(token_list[iter2].value == token_list[iter].value && token_list[iter2].type != "ID"){
	  token_list.erase(token_list.begin()+iter);
	  break;
	}
      }
    }
  }
};
