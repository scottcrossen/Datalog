#include "debugger.h"
#pragma once
using namespace std;
class Regular{
 private:
  Debugger regulario;
 public:
  Regular(){
    regulario=Debugger(true,true);
    regulario.output("Regular expression object created.");
    regulario.flag(1);
  }
  ~Regular(){
    regulario.output("Regular expression object deconstructed.");
    regulario.flag(2);
  }
};
