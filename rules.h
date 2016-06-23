#include "debugger.h"
#include "regexp.h"
#include "expbuffer.h"
#include <list>
#pragma once
class Rules{
 private:
  Debugger debug;
  list<RegExp*> regular_expression_list;
 public:
  Rules(){
    debug=Debugger("Rules");
    debug.output("Rules object created.");
  }
  ~Rules(){
    debug.flag(2);
    for (list<RegExp*>::iterator it=regular_expression_list.begin(); it !=regular_expression_list.end(); ++it){
      delete *it;
      debug.flag(4);
    }
    debug.output("Rules object deconstructed.");
  }
  void add_exp(string expression){
    debug.flag(3);
    regular_expression_list.push_back(new RegExp(expression));
    debug.output("add_exp method accessed.");
  }
};
