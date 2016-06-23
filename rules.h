#include "debugger.h"
#include "regexp.h"
#include "expbuffer.h"
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
    debug=Debugger(false,false,"Rules");
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
  void add_exp(string expression, string token){
    debug.flag(3);
    regular_expression_list.push_back(new RegExp(expression));
    buffer_list.push_back(new ExpBuffer(*regular_expression_list.end(),token));
    debug.output("add_exp method accessed.");
  }
  vector<string> add_char(char char_c){
    debug.flag(4);
    vector<string> output;
    bool reset_time=true;
    for (unsigned it=0; it < buffer_list.size(); it++){
      debug.flag(5);
      if (buffer_list[it]->state() ==2){
	debug.flag(6);
	if (buffer_list[it]->add_char(char_c) == 0) output.push_back(buffer_list[it]->get_id());
	else reset_time=false;
      }
      if (buffer_list[it]->state() ==1){
	if(buffer_list[it]->add_char(char_c) != 0) reset_time=false;
      }
    }
    debug.flag(7);
    if(reset_time==true) reset();
    debug.output("Added Char");
    return output;
  }
  void reset(){
    debug.flag(8);
    for (unsigned it=0; it < buffer_list.size(); it++) buffer_list[it]->reset();
    debug.output("Reset");
    }
};
