#include <istream>
#include <fstream>
#include "tokenlist.h"
#include "debugger.h"
#include "rules.h"
#pragma once
class Scanner{
 private:
  Debugger debug;
  void skip_ws(){};
  Rules rules;
 public:
  Scanner(){
    debug=Debugger("Scanner");
    debug.flag(1);
    debug.output("Scanner object created.");
    
  }
  ~Scanner(){
    debug.flag(2);
    debug.output("Scanner object deconstructed.");
  }
  void initialize(){
    debug.flag(3);
    rules.add_exp(",","COMMA");
    rules.add_exp(".","PERIOD");
    rules.add_exp("?","Q_MARK");
    rules.add_exp("(","LEFT_PAREN");
    rules.add_exp("(","RIGHT_PAREN");
    rules.add_exp(":","COLON");
    rules.add_exp(":=","COLON_DASH");
    rules.add_exp("Schemes","SCHEMES");
    rules.add_exp("Facts","FACTS");
    rules.add_exp("Rules","RULES");
    rules.add_exp("Queries","QUERIES");
    rules.add_exp("[A-Z][A-Z]*","ID");
    rules.add_exp("'[]*'","STRING");
    debug.output("Initialize method accessed.");
  }
};
