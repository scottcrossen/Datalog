#include "debugger.h"
#include "token.h"
#pragma once
class TokenList{
 private:
  Debugger debug;
  vector<Token> token_list;
 public:
  TokenList(){
    debug=Debugger("Token A");
    debug.output("Token array object created.");
    debug.flag(1);
  }
  ~TokenList(){
    debug.output("Token array object deconstructed.");
    debug.flag(2);
  }
};
