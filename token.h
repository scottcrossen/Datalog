#include "debugger.h"
#include <string>
#include <sstream>
#pragma once
enum TOKENTYPE {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, EOF1};

class Token{
 private:
  Debugger debug;
  TOKENTYPE type;
  string value;
  int line;
  const string token_types[EOF1+1]={"COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "EOF"};
 public:
  Token(TOKENTYPE type, string value, int line){
    debug=Debugger("Token");
    debug.output("Token object created.");
    debug.flag(1);
    this->type=type;
    this->value=value;
    this->line=line;
    debug.flag(4);
  }
  ~Token(){
    debug.output("Token object deconstructed.");
    debug.flag(2);
  }
  string display(){
    debug.output("Token display method accessed.");
    debug.flag(3);
    stringstream output;
    output << "(" << token_types[type] << "," << value <<"," << line << ")";
    return output.str();
  }
};
