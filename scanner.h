#include <istream>
#include <fstream>
#include "tokens.h"
#include "debugger.h"
#include "regulars.h"
#pragma once
class Scanner{
 private:
  Debugger debug;
  void skip_ws(){};
 public:
  Scanner(){
    debug=Debugger("Scanner");
    debug.output("Scanner object created.");
    debug.flag(1);
    
  }
  ~Scanner(){
    debug.output("Scanner object deconstructed.");
    debug.flag(2);
  }
};
