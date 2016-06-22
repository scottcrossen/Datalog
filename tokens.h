#include "debugger.h"
#include "token.h"
#pragma once
class Tokens{
 private:
  Debugger tokensio;
  vector<Token> token_list;
 public:
  Tokens(){
    tokensio=Debugger("Token A");
    tokensio.output("Token array object created.");
    tokensio.flag(1);
  }
  ~Tokens(){
    tokensio.output("Token array object deconstructed.");
    tokensio.flag(2);
  }
};
