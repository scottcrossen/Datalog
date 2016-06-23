#include "debugger.h"
#pragma once
using namespace std;
class RegExp{
 private:
  Debugger debug;
 public:
  RegExp(){
    debug=Debugger("Exp");
    debug.output("Regular expression object created.");
    debug.flag(1);
  }
  ~RegExp(){
    debug.output("Regular expression object deconstructed.");
    debug.flag(2);
  }
};
