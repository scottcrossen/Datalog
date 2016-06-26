#include "debugger.h"
#include "grammer.h"
#include <vector>
#pragma once
class GrammerList{
 public:
  GrammerList(){
    debug=Debugger(false, false, "Grammer A");
    debug.output(1,"Grammer List created.");
  }
  ~GrammerList(){
    debug.flag(2);
  }
  void add_grammer(string keyword, string equivalence){
    debug.flag(3);
    grammer_list.push_back(Grammer(keyword, equivalence));
    debug.flag(4);
  }
  void size(){return grammer_list.size()}
  vector<string> get_rule(int iter){
    return grammer_list[iter].return_equiv();
  }
 private:
  Debugger debug;
  vector<Grammer> grammer_list;
};
