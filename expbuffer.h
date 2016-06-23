#include "debugger.h"
#include "regexp.h"
#pragma once
class ExpBuffer{
 private:
  Debugger debug;
 public:
  ExpBuffer(){
    debug=Debugger("Buffer");
    debug.output("Buffer object created.");
    debug.flag(1);
  }
  ~ExpBuffer(){
    debug.output("Buffer object deconstructed.");
    debug.flag(2);
  }
};
