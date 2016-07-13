#include "parserclasses.h"
#include <vector>
#include <set>
#pragma once
class Database{
 public:
  Database(){
    debug=Debugger("Database");
    debug.flag(1);
    debug.output(2,"Class instantiated.");
  }
  ~Database(){}
  void initialize(){
    debug.flag(2);
    debug.output(3,"Initialized");
  }
  void debug_on(bool turn_on){
    debug.flag(4);
    debug.turned_on=true;
    debug.output(5,"Debug turned on.");
  }
  void read_in(DatalogProgram program){
    debug.flag(6);
    this->program=DatalogProgram(program.return_schemes(),program.return_facts(),program.return_rules(),program.return_queries(),program.return_domain());
    debug.output(7,"Program object read in.");
  }
  void clear(){
    debug.flag(8);
    this->program= DatalogProgram();
    debug.output(9,"Cleared.");
  }
  void build_database(){
    debug.flag(16);
    vector<Predicate> schemes=program.return_schemes();
    for(unsigned iter1=0; iter1 < schemes.size(); iter1++)
      relations.insert(RelationNode(schemes[iter1]));
    vector<Predicate> facts=program.return_schemes();
    for(unsigned iter1=0; iter1 < facts.size(); iter1++){
      bool found_relation=false;
      for(auto iter2: relations){
	if(iter2.node.return_ID() == facts[iter1].return_ID()){
	  found_relation=true;
	  iter2.add(facts[iter1]);
	  break;
	}
      }
      if(!(found_relation))  debug.abort(18);
    }
    debug.output(17,"Database created from object.");
  }
  void apply_queries(){
    debug.flag(10);
    
    debug.output(11,"Queries applied.");
  }
  void output_file(string file){
    debug.flag(12);
    out_file=file;
    debug.output(13,"Output file changed to "+file);
  }
  void write_out(){
    debug.flag(14);
    ofstream file_out;
    file_out.open(out_file.c_str());
    file_out << current_output;
    file_out.close();
    debug.output(15,"Output file written.");
  }
 private:
  class RelationNode{
  public:
    RelationNode(){}
    RelationNode(Predicate predicate){
      this->node=Parameter(predicate.return_ID());
      this->columns=predicate.return_parameter_list();
    }
    ~RelationNode(){}
    void add(Predicate predicate){
      tuples.insert(predicate.return_parameter_list());
    }
    Parameter node;
    vector<Parameter> columns;
    set<vector<Parameter>> tuples;
    bool operator< (const RelationNode& second){
      if(this->node.return_ID() < second.node.return_ID()) return true;
      else return false;
    }
    bool operator> (const RelationNode& second){
      if(this->node.toString() > second.node.toString()) return true;
      else return false;
    }
    bool operator== (const RelationNode& second){
      if(this->node.toString()== second.node.toString()) return true;
      else return false;
    }
  };
  Debugger debug;
  set<RelationNode> relations;
  string out_file;
  string current_output;
  DatalogProgram program;
};
