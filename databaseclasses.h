#pragma once
class QueryParam{
 public:
  QueryParam(string value){
    if(value.substr(0,1)=="'"){
      natural=value;
      reset_to=value;
      current_value=value;
      is_assigned=true;
    }
    else {
      natural=value;
      reset_to=string();
      current_value=string();
      is_assigned=false;
    }
  }
  bool compare(Parameter parameter){
    if(is_assigned==true)
      return (current_value==parameter.return_ID());
    else {
      current_value=parameter.return_ID();
      is_assigned=true;
      return true;
    }
  }
  void reset(){
    current_value=reset_to;
    is_assigned=(current_value==natural);
  }
  bool operator== (const QueryParam& second) const{
    if(this->return_natural()== second.return_natural()) return true;
    else return false;
  }
  string return_natural() const{
    return natural;
  }
  string return_value() const{
    return current_value;
  }
  bool return_assigned() const{
    return is_assigned;
  }
 private:
  string natural;
  string reset_to;
  string current_value;
  bool is_assigned;
};
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
