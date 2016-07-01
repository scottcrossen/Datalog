#include "debugger.h"
#include "tokenlist.h"
#include "token.h"
#include "grammerlist.h"
#include "programobject.h"
#include <stack>
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
    grammer_list.add_grammer("datalogProgram","SCHEMES COLON scheme schemeList datalogProgram");
    grammer_list.add_grammer("datalogProgram","FACTS COLON factList datalogProgram");
    grammer_list.add_grammer("datalogProgram","RULES COLON ruleList datalogProgram");
    grammer_list.add_grammer("datalogProgram","QUERIES COLON query queryList datalogProgram");
    grammer_list.add_grammer("datalogProgram","epsilon");
    grammer_list.add_grammer("schemeList","scheme schemeList");
    grammer_list.add_grammer("schemeList","epsilon");
    grammer_list.add_grammer("factList","fact factList");
    grammer_list.add_grammer("factList","epsilon");
    grammer_list.add_grammer("ruleList","rule ruleList");
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
    grammer_list.add_grammer("epsilon","EPSILON");
    grammer_list.build_terminal_list();
    //debug.output(11,"Grammers:\n"+grammer_list.print());
    debug.flag(4);
  }
  void read_in(TokenList *token_list){
    debug.flag(5);
    for(int iter=0; iter < token_list->size(); iter++)
      this->token_list.add(token_list->get(iter));
    debug.flag(6);
  }
  void write_out(){
    debug.flag(11);
    stringstream output;
    set<string> errors;
    program.find_error("Syntax", errors);
    if (errors.size() != 0){
      output << "Failure!"<<endl;
      for(set<string>::iterator iter=errors.begin(); iter != errors.end(); iter++){
	output << "  " << (*iter) <<endl;
	break;
      }
      //debug.output(8,"Syntax Error:\n"+program.print());
    }
    else{
      output << "Success!"<< endl;
      set<string> schemes;
      program.find_print("scheme", schemes);
      output << "Schemes("<<schemes.size()<<"):"<<endl;
      for(set<string>::iterator iter=schemes.begin(); iter != schemes.end(); iter++)
	output << "  " << (*iter) <<endl;
      set<string> facts;
      program.find_print("fact", facts);
      output << "Facts("<<facts.size()<<"):"<<endl;
      for(set<string>::iterator iter=facts.begin(); iter != facts.end(); iter++)
	output << "  " << (*iter).substr(0,(*iter).size()-1)<<endl;
      set<string> rules;
      program.find_print("rule", rules);
      output << "Rules("<<rules.size()<<"):"<<endl;
      for(set<string>::iterator iter=rules.begin(); iter != rules.end(); iter++)
	output << "  " << (*iter).substr(0,(*iter).size()-1)<<endl;
      set<string> queries;
      program.find_print("query", queries);
      output << "Queries("<<queries.size()<<"):"<<endl;
      for(set<string>::iterator iter=queries.begin(); iter != queries.end(); iter++)
	output << "  " << (*iter).substr(0,(*iter).size()-1)<<endl;
      set<string> domain;
      program.find_print("STRING", domain);
      output << "Domain("<<domain.size()<<"):"<<endl;
      for(set<string>::iterator iter=domain.begin(); iter !=domain.end(); iter++)
	output << "  " << *iter<<endl;
    }
    ofstream file_out;
    file_out.open(out_file.c_str());
    file_out << output.str();
    file_out.close();
    //debug.output(23,"Program Output:\n"+output.str());
    debug.output(12,"Objects Written to file");
  }
  void output_file(string file){
    debug.flag(13);
    out_file=file;
    debug.output(14,"Output file changed to "+file);
  }
  void debug_on(bool turn_on){
    debug.flag(9);
    debug.turned_on=turn_on;
    grammer_list.debug_on(turn_on);
    token_list.debug_on(turn_on);
    debug.output(10,"Debug turned on.");
  }
  void clear(){
    debug.flag(15);
    token_list.clear();
    program.clear();
    debug.flag(22);
  }
  void build(){
    debug.flag(7);
    stack<string> current;
    program.clear();
    program=ProgramObject("Program",2);
    current.push("EOF");
    current.push("datalogProgram");
    bool fail=false;
    while(current.size() !=0 && !(fail)){
      fail=true;
      string next=current.top();
      //debug.output(17,"Comparing stack value "+next+" with token type "+token_list.top().type+" and value "+token_list.top().value);
      if(token_list.top().type == next){
	//debug.output(17,"Stack value "+next+" matched with token "+token_list.top().type+" and value "+token_list.top().value);
	fail=false;
	match(current, fail);
      }
      else{
	if (next.at(0) <97 || next.at(0) >123){
	  syntax(token_list.top());
	  fail=true;
	}
	else{
	  //debug.output(17,"Querying grammers for "+next+" with terminal "+token_list.top().type+" and value "+token_list.top().value);
	  fail=false;
	  push_new(current, next, fail);
	}
      }
    }
    if(token_list.virtual_size() != 0)
      syntax(token_list.top());
    //debug.output(8,"program:\n"+program.print());
    debug.output(8,"Program syntax built.");
  }
 private:
  void syntax(Token error){
    program.clear();
    program.type="Syntax";
    program.extend();
    //cout << error.type <<" " <<error.value << " " << error.line <<"+"<< endl;
    program.add(new Token(error.type,error.value,error.line));
  }
  void match(stack<string> &current,bool &fail){
    debug.flag(19);
    if(!(program.add(new Token(token_list.top().type,token_list.top().value,token_list.top().line)))){
      syntax(token_list.top());
      fail=true;
    }
    token_list.pop();
    current.pop();
    debug.flag(20);
  }
  void push_new(stack<string> &current, string &next, bool &fail){
    fail=false;
    debug.flag(21);
    vector<string> replace=grammer_list.search(next, token_list.top().type);
    int list=0;
    if(replace.size()>1){
      if(replace[replace.size()-1]=="Syntax") {
	syntax(token_list.top());
	fail=true;
      }
      if(replace[replace.size()-1] == current.top() && !(fail)){
	program.extend();
	list=1;
      }
    }
    if (!(fail)){
      if(!(program.add(new ProgramObject(current.top(),replace.size()-list)))){
	syntax(token_list.top());
	fail=true;
      }
      current.pop();
      for(int iter2=replace.size()-1;iter2>=0;iter2--){
	current.push(replace[iter2]);
      }
    }
    debug.flag(22);
  }
  Debugger debug;
  string out_file;
  GrammerList grammer_list;
  TokenList token_list;
  ProgramObject program;
};
