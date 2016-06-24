#include "debugger.h"
#include "token.h"
#include <sstream>
#include <string>
#include <vector>
#pragma once
class TokenList{
 private:
  Debugger debug;
  vector<Token> token_list;
 public:
  TokenList(){
    debug=Debugger(false,false,"Token A");
    debug.output("Token array object created.");
    debug.flag(1);
  }
  ~TokenList(){
    debug.output("Token array object deconstructed.");
    debug.flag(2);
  }
  void add(Token my_token){
    token_list.push_back(my_token);
  }
  void add(vector<Token> my_tokens){
    for(unsigned iter=0; iter< my_tokens.size(); iter++)
      token_list.push_back(my_tokens[iter]);
  }
  string print_out(){
    stringstream output;
    unsigned iter=0;
    for(iter=0; iter < token_list.size(); iter++){
      if(token_list[iter].type != "ERROR") output << token_list[iter].display() << endl;
      else{output << "Input Error on line " << token_list[iter].line; break;}
    }
    if(iter==token_list.size()) output<< "Total Tokens = " << token_list.size();
    return output.str();
  }
  void remove_redundant(){
    for(unsigned iter=0; iter< token_list.size(); iter++){
      if(token_list[iter].value==":-"){
	for(unsigned iter2=iter; iter2 >=0 ; iter2--){
	  if(token_list[iter2].value==":"){
	    token_list.erase(token_list.begin()+iter2);
	    break;
	  }
	}
      }
      if(token_list[iter].type=="ID"){
	for(unsigned iter2=0; iter2 <token_list.size(); iter2++){
	  if(token_list[iter2].value == token_list[iter].value && token_list[iter2].type != "ID"){
	    token_list.erase(token_list.begin()+iter);
	    break;
	  }
	}
      }
    }
  }
  void clear(){
    for(unsigned iter=0; token_list.size() >0; iter++)
      token_list.pop_back();
  }
};
