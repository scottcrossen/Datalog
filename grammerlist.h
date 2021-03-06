#include "debugger.h"
#include "grammer.h"
#include <vector>
#pragma once
class GrammerList{
 public:
  GrammerList(){
    debug=Debugger("Gram A");
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
    debug.flag(5);
    //populate what is considered a terminal? with set?
    unsigned iter_max=0;
    bool flag=true;
    while(flag && iter_max <100){
      flag=false;
      for (unsigned iter=0; iter < grammer_list.size(); iter++){
	if(grammer_list[iter].get_terminals().size() == 0){
	  find_terminals(iter);
	  flag=true;
	}
      }
      iter_max++;
    }
    debug.output(6,"Terminal list built.");
  }
  vector<string> get_rule(int iter){
    debug.flag(7);
    return grammer_list[iter].get_equiv();
  }
  void debug_on(bool turn_on){
    debug.flag(8);
    debug.turned_on=turn_on;
    /*for(unsigned iter=0; iter <grammer_list.size(); iter++)
      grammer_list[iter].debug_on(turn_on);*/
    debug.output(9,"Debug turned on.");
  }
  string print(){
    debug.flag(10);
    stringstream output;
    unsigned iter=0;
    for(iter=0; iter < grammer_list.size(); iter++){
      output << grammer_list[iter].get_keyword() << "->";
      for(unsigned iter2=0; iter2 < grammer_list[iter].get_equiv().size(); iter2++)
	output << grammer_list[iter].get_equiv()[iter2] << " ";
      output << endl <<"\t";
      for(unsigned iter2=0; iter2 < grammer_list[iter].get_terminals().size(); iter2++)
	output << grammer_list[iter].get_terminals()[iter2] << " ";
      output << endl;
    }
    debug.flag(11);
    return output.str();
  }
  string print(unsigned iter){
    debug.flag(12);
    stringstream output;
    output << grammer_list[iter].get_keyword() << "->";
    for(unsigned iter2=0; iter2 < grammer_list[iter].get_equiv().size(); iter2++)
      output << grammer_list[iter].get_equiv()[iter2] << " ";
    output << endl <<"\t";
    for(unsigned iter2=0; iter2 < grammer_list[iter].get_terminals().size(); iter2++)
      output << grammer_list[iter].get_terminals()[iter2] << " ";
    output << endl;
    debug.flag(13);
    return output.str();
  }
  void clear(){
    debug.flag(14);
    for(unsigned iter=0; grammer_list.size() >0; iter++)
      grammer_list.pop_back();
    debug.output(15, "Grammers Cleared.");
  }
  Grammer get(int spot){
    debug.flag(16);
    return grammer_list[spot];
  }
  vector<string> search(string keyword, string terminal){
    debug.flag(17);
    vector<string> output;
    output=is_match(keyword,terminal);
    if (output.size() !=0) return output;
    output=is_eps(keyword);
    if (output.size() ==0) return output;
    vector<string> dummy;
    dummy.push_back("Syntax");
    debug.output(18,"Rule not found.");
    return dummy;
  }
 private:
  vector<string> is_match(string &keyword, string &terminal){
    debug.flag(19);
    for(unsigned iter=0; iter < grammer_list.size(); iter++)
      if(grammer_list[iter].get_keyword()==keyword)
	for(unsigned iter2=0; iter2 < grammer_list[iter].get_terminals().size(); iter2++)
	  if(grammer_list[iter].get_terminals()[iter2]==terminal)
	    return grammer_list[iter].get_equiv();
    vector<string> dummy;
    debug.flag(20);
    return dummy;
  }
  vector<string> is_eps(string &keyword){
    debug.flag(21);
    for(unsigned iter=0; iter < grammer_list.size(); iter++)
      if(grammer_list[iter].get_keyword()==keyword)
	for(unsigned iter2=0; iter2 < grammer_list[iter].get_terminals().size(); iter2++)
	  if(grammer_list[iter].get_terminals()[iter2]=="EPSILON"){
	    vector<string> dummy;
	    return dummy;
	  }
    vector<string> dummy;
    dummy.push_back("Failed");
    debug.flag(22);
    return dummy;
}
  void find_terminals(unsigned &iter){
    debug.flag(23);
    if(grammer_list[iter].get_equiv()[0].at(0) < 97 || grammer_list[iter].get_equiv()[0].at(0) > 123){ // anything with a lowercase is not a token
      vector<string> output2;
      output2.push_back(grammer_list[iter].get_equiv()[0]);
      grammer_list[iter].set_terminals(output2);
    }
    else
      look_for_terminals(iter);
    debug.flag(24);
  }
  void look_for_terminals(unsigned &iter){
    debug.flag(25);
    bool found_all=true;
    vector<string> output2;
    for (unsigned iter2 =0; iter2 < grammer_list.size(); iter2++)
      if(iter != iter2 && grammer_list[iter2].get_keyword() == grammer_list[iter].get_equiv()[0]){
	if(grammer_list[iter2].get_terminals().size() != 0){
	  for(unsigned iter3=0; iter3<grammer_list[iter2].get_terminals().size(); iter3++)
	    output2.push_back(grammer_list[iter2].get_terminals()[iter3]);
	}
	else found_all=false;
      }
    if (found_all)
      grammer_list[iter].set_terminals(output2);
    debug.flag(26);
  }
  Debugger debug;
  vector<Grammer> grammer_list;
};
