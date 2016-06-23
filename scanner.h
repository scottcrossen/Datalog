#include <istream>
#include <fstream>
#include "tokenlist.h"
#include "debugger.h"
#include "rules.h"
#pragma once
class Scanner{
 private:
  Debugger debug;
  void skip_ws(){};
  Rules rules;
 public:
  Scanner(){
    debug=Debugger("Scanner");
    debug.flag(1);
    debug.output("Scanner object created.");
    
  }
  ~Scanner(){
    debug.flag(2);
    debug.output("Scanner object deconstructed.");
  }
  void initialize(){
    debug.flag(3);
    rules.add_exp("ASS[]");
    debug.output("Initialize method accessed.");
  }
};
