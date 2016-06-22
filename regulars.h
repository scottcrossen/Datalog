#include "debugger.h"
#include "regular.h"
#pragma once
class Regulars{
 private:
  Debugger debug;
  vector<Regular> regular_expression_list;
 public:
  Regulars(){
    debug=Debugger("Exp A");
    debug.output("Regular expression array object created.");
    debug.flag(1);
  }
  ~Regulars(){
    debug.output("Regular expression array object deconstructed.");
    debug.flag(2);
  }
};
