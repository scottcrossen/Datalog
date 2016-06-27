#include "debugger.h"
#pragma once
class Grammer{
 public:
  Grammer(string keyword, string equivalence){
    debug=Debugger(true,true,"Grammer");
    debug.flag(1);
    unsigned last_space=0;
    unsigned iter;
    for(iter=0; iter < equivalence.length(); iter++)
      if(equivalence.substr(iter,1) ==" "){
	equiv.push_back(equivalence.substr(last_space, iter-last_space));
	//debug.output(6,"word added: "+equivalence.substr(last_space, iter-last_space));
	last_space=iter+1;
      }
    if(last_space != iter) equiv.push_back(equivalence.substr(last_space, iter-last_space));
    debug.output(2,"Grammer object created.");
  }
  ~Grammer(){
    debug.flag(3);
  }
  void debug_on(bool turn_on){
    debug.flag(4);
    debug.turned_on=turn_on;
    debug.output(5,"Debug turned on.");
  }
  void set_terminals(vector<string> terminals){
    debug.flag(6);
    this->terminals=terminals;
    debug.flag(7);
  }
  vector<string> get_terminals(){
    debug.flag(8);
    return terminals;
  }
  vector<string> get_equiv(){ return equiv;}
 private:
  Debugger debug;
  string keyword;
  vector<string> equiv;
  vector<string> terminals;
};
