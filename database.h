#include "parserclasses.h"
#pragma once
class Database{
 public:
  Database(){
    debug=Debugger("Database");
    debug.flag(1);
    debug.output(2,"Class instantiated.");
  }
  ~Database(){}
  void initialize(){
    debug.flag(2);
    debug.output(3,"Initialized");
  }
  void debug_on(bool turn_on){
    debug.flag(4);
    debug.turned_on=true;
    debug.output(5,"Debug turned on.");
  }
  void read_in(DatalogProgram program){
    debug.flag(6);
    this->program=program;
    debug.output(7,"Program read in");
  }
  void clear(){
    debug.flag(8);
    debug.output(9,"Cleared.");
  }
 private:
  DatalogProgram program;
  Debugger debug;
};
