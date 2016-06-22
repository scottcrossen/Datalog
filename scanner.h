#include <istream>
#include <fstream>
#include "tokens.h"
#include "debugger.h"
#pragma once
using namespace std;
class Debugger{
 private:
  Debugger scannerio;
  skip_ws(){};
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
