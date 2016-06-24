#include "debugger.h"
#include "regexp.h"
#include "expbuffer.h"
#include "token.h"
#include <vector>
#include <string>
#pragma once
class Rules{
 private:
  Debugger debug;
  vector<RegExp*> regular_expression_list;
  vector<ExpBuffer*> buffer_list;
 public:
  Rules(){
    debug=Debugger("Rules");
    debug.output("Rules object created.");
  }
  ~Rules(){
    debug.flag(2);
    for (vector<RegExp*>::iterator it=regular_expression_list.begin(); it !=regular_expression_list.end(); ++it){
      delete *it;
      debug.flag(4);
    }
    for (vector<ExpBuffer*>::iterator it=buffer_list.begin(); it != buffer_list.end(); ++it){
      delete *it;
      debug.flag(5);
    }
    debug.output("Rules object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.turned_on=turn_on;
    for (unsigned it=0; it < buffer_list.size(); it++) buffer_list[it]->debug_on(turn_on);
    for (unsigned it=0; it < regular_expression_list.size(); it++) regular_expression_list[it]->debug_on(turn_on);
  }
  void add_exp(string expression, string token){
    debug.flag(3);
    RegExp* new_exp=new RegExp(expression);
    regular_expression_list.push_back(new_exp);
    debug.output("Expression added: "+expression+" with token: "+token);
    buffer_list.push_back(new ExpBuffer(new_exp,token));
    debug.output("add_exp method accessed.");
  }
  vector<Token> add_char(char char_c, int line){
    debug.flag(4);
    vector<Token> output;
    for(unsigned iter=0;iter<=1;++iter){
      bool reset_time=true;
      for (unsigned it=0; it < buffer_list.size(); it++){
	debug.flag(5);
	if (buffer_list[it]->state() ==2){
	  debug.flag(6);
	  if (buffer_list[it]->add_char(char_c) == 0) output.push_back(Token(buffer_list[it]->get_id(), buffer_list[it]->get_string().substr(0,buffer_list[it]->get_string().size()-1), line));
	}
	if (buffer_list[it]->state() ==1){
	  debug.flag(9);
	  buffer_list[it]->add_char(char_c);
	  debug.flag(12);
	}
	debug.flag(10);
	if(buffer_list[it]->state() != 0) reset_time=false;
      }
      debug.flag(7);
      if(reset_time==true){
	if(iter==0) reset();
	else if(iter==1){ cout << "+"<< char_c <<"+"<< endl; output.push_back(Token("ERROR","Unknown Character",line)); debug.flag(10);}
      } else iter++;
    }
    debug.output("Added Char");
    return output;
  }
  void reset(){
    debug.flag(8);
    for (unsigned it=0; it < buffer_list.size(); it++) buffer_list[it]->reset();
    debug.output("Reset");
  }
  vector<Token> save_reset(int line){
    debug.flag(8);
    vector<Token> output;
    for (unsigned it=0; it < buffer_list.size(); it++){
      if(buffer_list[it]->state()==2) output.push_back(Token(buffer_list[it]->get_id(), buffer_list[it]->get_string(), line));
      buffer_list[it]->reset();
    }
    debug.output("Reset & Saved");
    return output;
  }
};
