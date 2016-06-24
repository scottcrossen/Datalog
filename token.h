#include "debugger.h"
#include <string>
#include <sstream>
#pragma once

class Token{
 private:
  Debugger debug;
 public:
  string type;
  string value;
  int line;
  Token(string type, string value, int line){
    debug=Debugger("Token");
    debug.flag(1);
    this->type=type;
    this->value=value;
    this->line=line;
    debug.flag(4);
    debug.output("Token object created.");
  }
  ~Token(){
    debug.flag(2);
    debug.output("Token object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.turned_on=turn_on;
  }
  string display(){
    debug.flag(3);
    stringstream output;
    output << "(" << type << "," <<"\""<< value<<"\"" <<"," << line << ")";
    debug.output("Token display method accessed.");
    return output.str();
  }
};
