#include "debugger.h"
#pragma once
using namespace std;
class Regular{
 private:
  Debugger debug;
 public:
  Regular(){
    debug=Debugger("Exp");
    debug.output("Regular expression object created.");
    debug.flag(1);
  }
  ~Regular(){
    debug.output("Regular expression object deconstructed.");
    debug.flag(2);
  }
};
