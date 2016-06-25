#include "debugger.h"
#include "regexp.h"
#include <string>
#pragma once
class ExpBuffer{
 public:
  ExpBuffer(RegExp* expression, string id){
    debug=Debugger("Buffer");
    debug.flag(1);
    this->expression=expression;
    this->id=id;
    current_state=1;
    debug.output(2,"Buffer object created.");
  }
  ~ExpBuffer(){
    debug.output(3,"Buffer object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.flag(4);
    debug.turned_on=turn_on;
    debug.output(5,"Debug turned on.");
  }
  //Return 0 for fail, 1 for incomplete, 2 for complete.
  int state(){
    debug.flag(6);
    return current_state;
  }
  int add_char(char c){
    debug.flag(7);
    if (current_state != 0){
      charbuf+=string(1,c);
      current_state=(expression->check(charbuf));
    }
    debug.flag(8);
    return current_state;
  }
  void reset(){
    debug.flag(9);
    charbuf=string();
    current_state=1;
    debug.flag(10);
  }
  string get_id(){debug.flag(11); return id;}
  string get_string(){debug.flag(12); return charbuf;}
 private:
  Debugger debug;
  RegExp* expression;
  int current_state;
  string charbuf;
  string id;
};
