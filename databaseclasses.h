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
  void operator= (const RelationNode& second){
    this->node=second.node;
    this->columns=second.columns;
    this->tuples=tuples;
  }
  RelationNode operatorU (const RelationNode& second){
    debug.abort(3, this->columns != second.columns);
    RelationNode output=(*this);
    for(set<vector<Parameter>>::iterator iter1=second.tuples.begin(); iter1 !=second.tuples.end(); iter1++)
      output.tuples.insert(*iter1);
    return output;
  }
  RelationNode operatorX (const RelationNode& second){
    RelationNode output;
    output.node=string();
    vector<QueryParam*> new_columns;
    vector<QueryParam*> first_columns;
    vector<QueryParam*> second_columns;
    // First create the vectors that should match to make a new tuple
    for(vector<Parameter>::iterator iter1=this->columns.begin(); iter1 !=this->columns.begin(); iter1++){
      bool found_match=false;
      for(vector<QueryParam*>::iterator iter2=new_columns.begin(); iter2 != new_culmns.end();iter2++)
	if ((*iter1).return_ID() == (*iter2)->return_natural()){
	  found_match=true;
	  first_columns.push_back(*iter2);
	  break;
	}
      if (!(found_match)){
	QueryParam* new_queryparam=new QueryParam((*iter1).return_ID());
	new_columns.push_back(new_queryparam);
	first_columns.push_back(new_queryparam);
      }
    }
    for(vector<Parameter>::iterator iter1=second.columns.begin(); iter1 !=second.columns.begin(); iter1++){
      bool found_match=false;
      for(vector<QueryParam*>::iterator iter2=new_columns.begin(); iter2 != new_culmns.end();iter2++)
	if ((*iter1).return_ID() == (*iter2)->return_natural()){
	  found_match=true;
	  second_columns.push_back(*iter2);
	  break;
	}
      if (!(found_match)){
	QueryParam* new_queryparam=new QueryParam((*iter1).return_ID());
	new_columns.push_back(new_queryparam);
	second_columns.push_back(new_queryparam);
      }
    }
    // Iterate through set and add matching tuples.
    for(set<vector<Parameter>>::iterator iter1=this->tuples.begin();iter1 !=this->tuples.end();iter1++)
      for(set<vector<Parameter>>::iterator iter2=second.tuples.begin();iter2 !=second.tuples.end();iter2++){
	for(vector<QueryParam>::iterator iter3=new_columns.begin(); iter3 !=new_columns.end(); iter3++)
	  iter3->reset();
	bool matches=true;
	for(unsigned iter3=0;iter3<first_columns.size();iter3++){
	  matches=first_columns[iter3]->compare((*iter1)[iter3]);
	  if(!(matches)) break;
	}
	if(matches)
	for(unsigned iter3=0;iter3<second_columns.size();iter3++){
	  matches=second_columns[iter3]->compare((*iter2)[iter3]);
	  if(!(matches)) break;
	}
	if(matches){
	  vector<Parameter> add_tuple;
	  for(vector<QueryParam>::iterator iter3=new_columns.begin(); iter3 !=new_columns.end(); iter3++)
	    add_tuple.push_back(Parameter(iter3->return_value()));
	  output.tuples.insert(add_tuple);
	}
      }
    for(vector<QueryParam>::iterator iter1=new_columns.begin(); iter1 !=new_columns.end(); iter1++){
      output.columns.push_back(Parameter(QueryParam(iter1->return_natural())));
      delete (*iter1);
    }
    return output;
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
