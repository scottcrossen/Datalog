#include "debugger.h"
#include "regexp.h"
#include <string>
#define FAILED 0
#define INCOMPLETE 1
#define COMPLETE 2
#pragma once
class ExpBuffer{
 public:
  ExpBuffer(RegExp* expression, string id, int starting_line){
    debug=Debugger("Buffer");
    debug.flag(1);
    this->expression=expression;
    this->id=id;
    this->starting_line=starting_line;
    current_state=INCOMPLETE;
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
  void reset(int line){
    debug.flag(9);
    charbuf=string();
    current_state=INCOMPLETE;
    starting_line=line;
    debug.flag(10);
  }
  int get_line(){debug.flag(11); return starting_line;}
  string get_id(){debug.flag(12); return id;}
  string get_string(){debug.flag(13); return charbuf;}
 private:
  Debugger debug;
  RegExp* expression;
  int current_state;
  string charbuf;
  string id;
  int starting_line;
};
