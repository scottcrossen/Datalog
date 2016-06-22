#include "debugger.h"
#include "regular.h"
#pragma once
class Regulars{
 private:
  Debugger regularsio;
  vector<Regular> regular_expression_list;
 public:
  Regulars(){
    regularsio=Debugger("Exp A");
    regularsio.output("Regular expression array object created.");
    regularsio.flag(1);
  }
  ~Regulars(){
    regularsio.output("Regular expression array object deconstructed.");
    regularsio.flag(2);
  }
};
