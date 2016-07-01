#include "programobject.h"
#include "debugger.h"
#include <string>
#include <sstream>
#pragma once

class Token : public ProgramObject{
 public:
  //string type;
  string value;
  int line;
  Token(string type, string value, int line){
    debug=Debugger("Token");
    debug.flag(1);
    this->type=type;
    this->value=value;
    this->line=line;
    debug.output(2,"Token object created.");
  }
  ~Token(){
    debug.output(3,"Token object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.flag(4);
    debug.turned_on=turn_on;
    debug.output(5,"Debug turned on.");
  }
  string display(){
    debug.flag(6);
    stringstream output;
    output << "(" << type << "," <<"\""<< value<<"\"" <<"," << line << ")";
    debug.output("Token display method accessed.");
    debug.flag(7);
    return output.str();
  }
  string obj_print(int tabs){
    stringstream output;
    for(int iter=0; iter<tabs; iter++ ) output<<" ";
    output << "(" << type << "," <<"\""<< value<<"\"" <<"," << line << ")" <<endl;
    return output.str();
  }
  string to_string(){
    return value;
  }
 private:
  Debugger debug;
};
