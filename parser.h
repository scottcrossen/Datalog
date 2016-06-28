#include "debugger.h"
#include "tokenlist.h"
#include "token.h"
#include "grammerlist.h"
#pragma once
class Parser{
 public:
  Parser(){
    debug=Debugger("Parser");
    debug.output(1,"Parser object created.");
    grammer_list=GrammerList();
  }
  ~Parser(){
    debug.flag(2);
  }
  void initialize(){
    debug.flag(3);
    grammer_list.add_grammer("datalogProgram","SCHEMES COLON scheme schemeList");
    grammer_list.add_grammer("datalogProgram","FACTS COLON factList");
    grammer_list.add_grammer("datalogProgram","RULES COLON ruleList");
    grammer_list.add_grammer("datalogProgram","QUERIES COLON query queryList");
    grammer_list.add_grammer("schemeList","scheme schemeList");
    grammer_list.add_grammer("schemeList","epsilon");
    grammer_list.add_grammer("factList","fact factList");
    grammer_list.add_grammer("factList","epsilon");
    grammer_list.add_grammer("ruleList","epsilon");
    grammer_list.add_grammer("ruleList","epsilon");
    grammer_list.add_grammer("queryList","query queryList");
    grammer_list.add_grammer("queryList","epsilon");
    grammer_list.add_grammer("scheme","predicate");
    grammer_list.add_grammer("fact","predicate PERIOD");
    grammer_list.add_grammer("rule","predicate COLON_DASH predicate predicateList PERIOD");
    grammer_list.add_grammer("query","predicate Q_MARK");
    grammer_list.add_grammer("predicateList","COMMA predicate predicateList");
    grammer_list.add_grammer("predicateList","epsilon");
    grammer_list.add_grammer("predicate","ID LEFT_PAREN parameter parameterList RIGHT_PAREN");
    grammer_list.add_grammer("parameterList","COMMA parameter parameterList");
    grammer_list.add_grammer("parameterList","epsilon");
    grammer_list.add_grammer("parameter","STRING");
    grammer_list.add_grammer("parameter","ID");
    debug.flag(4);
  }
  void read_in(TokenList token_list){
    debug.flag(5);
    this->token_list=token_list;
    debug.flag(6);
  }
  void check_syntax(){
    debug.flag(7);
    void recur_check_syn(int token){
      for (int iter=0; iter < grammer_list.size() iter++){
	//THIS WONT WORK. INFINITE RECURSION IF ALLOWED DEPTH >1
      }
    }
    debug.flag(8);
  }
 private:
  Debugger debug;
  GrammerList grammer_list;
  TokenList token_list;
};