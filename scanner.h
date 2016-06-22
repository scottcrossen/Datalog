#include <istream>
#include <fstream>
#include "tokens.h"
#include "debugger.h"
#include "regulars.h"
#pragma once
class Scanner{
 private:
  Debugger scannerio;
  void skip_ws(){};
 public:
  Scanner(){
    scannerio=Debugger(true,true);
    scannerio.output("Scanner object created.");
    scannerio.flag(1);
    
  }
  ~Scanner(){
    scannerio.output("Scanner object deconstructed.");
    scannerio.flag(2);
  }
};
