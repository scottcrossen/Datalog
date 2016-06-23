#include "debugger.h"
#include "regexp.h"
#include "expbuffer.h"
#pragma once
class Rules{
 private:
  Debugger debug;
  vector<RegExp> regular_expression_list;
 public:
  Rules(){
    debug=Debugger("Exp A");
    debug.output("Regular expression array object created.");
    debug.flag(1);
  }
  ~Rules(){
    debug.output("Regular expression array object deconstructed.");
    debug.flag(2);
  }
};
