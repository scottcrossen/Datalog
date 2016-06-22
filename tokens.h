#include "debugger.h"
#include "token.h"
#pragma once
class Tokens{
 private:
  Debugger debug;
  vector<Token> token_list;
 public:
  Tokens(){
    debug=Debugger("Token A");
    debug.output("Token array object created.");
    debug.flag(1);
  }
  ~Tokens(){
    debug.output("Token array object deconstructed.");
    debug.flag(2);
  }
};
