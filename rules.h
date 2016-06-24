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
    debug.output(1,"Rules object created.");
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
    debug.output(3,"Rules object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.flag(4);
    debug.turned_on=turn_on;
    for (unsigned it=0; it < buffer_list.size(); it++) buffer_list[it]->debug_on(turn_on);
    for (unsigned it=0; it < regular_expression_list.size(); it++) regular_expression_list[it]->debug_on(turn_on);
    debug.output(5,"Debug turned on.");
  }
  void add_exp(string expression, string token){
    debug.flag(6);
    RegExp* new_exp=new RegExp(expression);
    regular_expression_list.push_back(new_exp);
    buffer_list.push_back(new ExpBuffer(new_exp,token));
    debug.output(7,"Expression added: "+expression+" with token: "+token);
  }
  vector<Token> add_char(char char_c, int line){
    debug.flag(8);
    vector<Token> output;
    for(unsigned iter=0;iter<=1;++iter){
      bool reset_time=true;
      for (unsigned it=0; it < buffer_list.size(); it++){
	debug.flag(9);
	if (buffer_list[it]->state() ==2){
	  if (buffer_list[it]->add_char(char_c) == 0) output.push_back(Token(buffer_list[it]->get_id(), buffer_list[it]->get_string().substr(0,buffer_list[it]->get_string().size()-1), line));
	}
	if (buffer_list[it]->state() ==1){
	  buffer_list[it]->add_char(char_c);
	}
	if(buffer_list[it]->state() != 0) reset_time=false;
      }
      debug.flag(10);
      if(reset_time==true){
	if(iter==0) reset();
	else if(iter==1){ cout << "+"<< char_c <<"+"<< endl; output.push_back(Token("ERROR","Unknown Character",line)); debug.flag(10);}
      } else iter++;
    }
    debug.flag(11);
    return output;
  }
  void reset(){
    debug.flag(12);
    for (unsigned it=0; it < buffer_list.size(); it++) buffer_list[it]->reset();
    debug.output(13,"Reset");
  }
  vector<Token> save_reset(int line){
    debug.flag(14);
    vector<Token> output;
    for (unsigned it=0; it < buffer_list.size(); it++){
      if(buffer_list[it]->state()==2) output.push_back(Token(buffer_list[it]->get_id(), buffer_list[it]->get_string(), line));
      buffer_list[it]->reset();
    }
    debug.output(15,"Reset & Saved");
    return output;
  }
};
