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
    debug.turned_on=turn_on;
    for(set<RelationNode>::iterator iter2= relations.begin(); iter2 !=relations.end(); iter2++){
      iter2->debug_on(turn_on);
    }
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
    current_output=string();
    relations.clear();
    debug.output(9,"Cleared.");
  }
  void build_database(){
    debug.flag(16);
    vector<Predicate> schemes=program.return_schemes();
    for(unsigned iter1=0; iter1 < schemes.size(); iter1++)
      relations.insert(RelationNode(schemes[iter1]));
    //debug_on(true);
    current_output+="Scheme Evaluation\n\n";
    vector<Predicate> facts=program.return_facts();
    for(unsigned iter1=0; iter1 < facts.size(); iter1++){
      bool found_relation=false;
      for(set<RelationNode>::iterator iter2= relations.begin(); iter2 !=relations.end(); iter2++){
	if(iter2->node.return_ID() == facts[iter1].return_ID()){
	  found_relation=true;
	  iter2->add(facts[iter1]);
	  break;
	}
      }
      if(!(found_relation))  debug.abort(18);
    }
    current_output+="Fact Evaluation\n\n";
    stringstream output;
    for(set<RelationNode>::iterator iter=relations.begin(); iter!=relations.end(); iter++){
      output<< (*iter).node.return_ID() <<endl;
      for(set<vector<Parameter>>::iterator iter2=(*iter).tuples.begin(); iter2 != (*iter).tuples.end(); iter2++){
	output << " ";
	for(unsigned iter3=0; iter3 < (*iter).columns.size(); iter3++)
	  output <<" "<< (*iter).columns[iter3].return_ID()<<"="<<(*iter2)[iter3].return_ID();
	output << endl;
      }
    }
    output << endl;
    current_output+=output.str();
    debug.output(17,"Database created from object.");
  }
  void apply_queries(){
    debug.flag(10);
    current_output+="Query Evaluation\n\n";
    stringstream output;
    
    current_output+=output.str();
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
    RelationNode(){
      debug=Debugger("Relation");
      debug.flag(1);
      debug.output(2,"Class instantiated.");}
    RelationNode(Predicate predicate){
      debug=Debugger("Relation");
      debug.flag(1);
      this->node=Parameter(predicate.return_ID());
      this->columns=predicate.return_parameter_list();
      debug.output(2,"Class instantiated.");
    }
    ~RelationNode(){}
    void add(Predicate predicate) const{
      tuples.insert(predicate.return_parameter_list());
      stringstream status;
      status << "Added tuples: ";
      for(auto iter: predicate.return_parameter_list())
	status<< iter.return_ID() <<" ";
      status << "to relation " <<node.return_ID()<<" with columns";
      for(auto iter: columns)
	status<<" "<< iter.return_ID();
      status<< "which now has size " << tuples.size() <<endl;
      debug.output(status.str());
    }
    bool operator< (const RelationNode& second) const{
      if(this->node < second.node) return true;
      else return false;
    }
    bool operator> (const RelationNode& second) const{
      if(this->node > second.node) return true;
      else return false;
    }
    bool operator== (const RelationNode& second) const{
      if(this->node== second.node) return true;
      else return false;
    }
    void debug_on(bool turn_on) const{
      debug.turned_on=turn_on;
      debug.output("Debug turned on.");
    }
    Parameter node;
    vector<Parameter> columns;
    mutable set<vector<Parameter>> tuples;
    Debugger debug;
  };
  Debugger debug;
  set<RelationNode> relations;
  string out_file;
  string current_output;
  DatalogProgram program;
};
