#include "debugger.h"
#include "regexp.h"
#include <string>
#pragma once
class ExpBuffer{
 private:
  Debugger debug;
  RegExp* expression;
  int current_state;
  string charbuf;
  string id;
 public:
  ExpBuffer(RegExp* expression, string id){
    debug=Debugger("Buffer");
    debug.flag(1);
    this->expression=expression;
    this->id=id;
    current_state=1;
    debug.output("Buffer object created.");
  }
  ~ExpBuffer(){
    debug.output("Buffer object deconstructed.");
    debug.flag(2);
  }
  void debug_on(bool turn_on){
    debug.turned_on=turn_on;
  }
  //Return 0 for fail, 1 for incomplete, 2 for complete.
  int state(){
    debug.flag(3);
    debug.output("state method accessed");
    return current_state;
  }
  int add_char(char c){
    debug.flag(4);
    if (current_state != 0){
      charbuf+=string(1,c);
      debug.flag(6);
      debug.flags_display();
      debug.flags_clear();
      debug.output("charbuf= "+charbuf);
      current_state=(expression->check(charbuf));
      debug.flag(7);
      debug.flags_display();
      debug.flags_clear();
    }
    debug.output("Added Char");
    return current_state;
  }
  void reset(){
    debug.flag(5);
    charbuf=string();
    current_state=1;
    debug.output("Reset");
  }
  string get_id(){return id;}
  string get_string(){return charbuf;}
};
