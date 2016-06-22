#include "debugger.h"
#include "regular.h"
#include <string>
#include <sstream>
#pragma once
enum TOKENTYPE {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, EOF1};

class Token{
 private:
  Debugger tokenio;
  TOKENTYPE type;
  string value;
  int line;
  const string token_types[EOF1+1]={"COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "EOF"};
 public:
  Token(TOKENTYPE type, string value, int line){
    tokenio=Debugger("Token");
    tokenio.output("Token object created.");
    tokenio.flag(1);
    this->type=type;
    this->value=value;
    this->line=line;
    tokenio.flag(4);
  }
  ~Token(){
    tokenio.output("Token object deconstructed.");
    tokenio.flag(2);
  }
  string display(){
    tokenio.output("Token display method accessed.");
    tokenio.flag(3);
    stringstream output;
    output << "(" << token_types[type] << "," << value <<"," << line << ")";
    return output.str();
  }
};
