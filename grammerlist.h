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
  void build_terminal_list(){
    //populate what is considered a terminal? with set?
    for (unsigned iter=0; iter < grammer_list.size(); iter++)  
      if(grammer_list[iter].get_terminals().size() != 0)
	grammer_list[iter].set_terminals(find_terminals(iter));
  }
  vector<string> find_terminals(unsigned grammernum){
    vector<string> output;
    if(grammer_list[grammernum].get_equiv()[1].at(1) < 97 || grammer_list[grammernum].get_equiv()[1].at(1) > 123) // anything with a lowercase is not a token
      output.push_back(grammer_list[grammernum].get_equiv()[1]);
    else{
      for (unsigned iter =0; iter < grammer_list.size(); iter++)
	if(iter != grammernum && grammer_list[iter].get_keyword() == grammer_list[grammernum].get_equiv()[0])
	  output.insert(output.end(),find_terminals(iter).begin(),find_terminals(iter).end());
    }
    grammer_list[grammernum].set_terminals(output);
    return output;
  }
  void size(){return grammer_list.size()}
  vector<string> get_rule(int iter){
    return grammer_list[iter].get_equiv();
  }
 private:
  Debugger debug;
  vector<Grammer> grammer_list;
};
