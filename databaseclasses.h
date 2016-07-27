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
string vec_to_string(vector<Parameter> vec){
  //debug.flag(23);
  stringstream output;
  output <<"(";
  for(unsigned iter=0; iter<vec.size()-1;iter++)
    output << vec[iter].return_ID()<<",";
  output << vec[vec.size()-1].return_ID() << ")";
  //debug.flag(24);
  return output.str();
}
string vec_to_string(vector<QueryParam*> vec){
  //debug.flag(23);
  stringstream output;
  output <<"(";
  for(unsigned iter=0; iter<vec.size()-1;iter++)
    output << vec[iter]->return_natural()<<",";
  output << vec[vec.size()-1]->return_natural() << ")";
  //debug.flag(24);
  return output.str();
}
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
    this->node=Parameter(second.node.return_ID());
    this->columns=second.columns;
    this->tuples=second.tuples;
  }
  /*
  RelationNode operatorU (const RelationNode& second) const{
    //debug.abort(3, this->columns != second.columns);
    RelationNode output=(*this);
    RelationNode second_relation=second.project((*this).columns);
    for(set<vector<Parameter>>::iterator iter1=second_relation.tuples.begin(); iter1 !=second_relation.tuples.end(); iter1++)
      output.tuples.insert(*iter1);
    return output;
    }
  */
  void u(const RelationNode& second) const{
    //debug.abort(3, this->columns != second.columns);
    RelationNode second_relation=second.project((*this).columns);
    for(set<vector<Parameter>>::iterator iter1=second_relation.tuples.begin(); iter1 !=second_relation.tuples.end(); iter1++)
      (*this).tuples.insert(*iter1);
  }
  bool uni(vector<Parameter> this_columns, const RelationNode& second) const{
    //debug.abort(3, this->columns != second.columns);
    unsigned tuple_size_start=(*this).tuples.size();
    RelationNode second_relation=second.project(this_columns);
    for(set<vector<Parameter>>::iterator iter1=second_relation.tuples.begin(); iter1 !=second_relation.tuples.end(); iter1++)
      (*this).tuples.insert(*iter1);
    if((*this).tuples.size() !=tuple_size_start) return true;
    else return false;
  }
  RelationNode project(vector<Parameter> columns) const {
    RelationNode output=(*this);
    set<vector<Parameter>> new_tuples;
    for(set<vector<Parameter>>::iterator iter1=output.tuples.begin(); iter1 !=output.tuples.end(); iter1++){
      vector<Parameter> this_line;
      for(unsigned iter2=0; iter2 < columns.size(); iter2++){
	for(unsigned iter3=0; iter3 < (*this).columns.size(); iter3++)
	  if(columns[iter2].return_ID()==(*this).columns[iter3].return_ID())
	    this_line.push_back((*iter1)[iter3]);
      }
      new_tuples.insert(this_line);
    }
    output.columns=columns;
    output.tuples=new_tuples;
    return output;
  }
  /*
  RelationNode operatorX (const RelationNode& second){
  */
  RelationNode x(const RelationNode& second){
    RelationNode output;
    output.node=Parameter("new");
    vector<QueryParam*> new_columns;
    vector<QueryParam*> first_columns;
    vector<QueryParam*> second_columns;
    // First create the vectors that should match to make a new tuple
    create_match_vec_col_1(new_columns, first_columns, second_columns);
    create_match_vec_col_2(new_columns, first_columns, second_columns, second);
    debug.output("Templates Created. Unique Columns: "+vec_to_string(new_columns)+" First Columns: "+vec_to_string(first_columns)+" Second Columns: "+vec_to_string(second_columns));
    // Iterate through set and add matching tuples.
    for(set<vector<Parameter>>::iterator iter1=this->tuples.begin();iter1 !=this->tuples.end();iter1++)
      for(set<vector<Parameter>>::iterator iter2=second.tuples.begin();iter2 !=second.tuples.end();iter2++){
	for(vector<QueryParam*>::iterator iter3=new_columns.begin(); iter3 !=new_columns.end(); iter3++)
	  (*iter3)->reset();
	test_for_match(new_columns, first_columns, second_columns, second,iter1, iter2, output);
      }
    for(vector<QueryParam*>::iterator iter1=new_columns.begin(); iter1 !=new_columns.end(); iter1++){
      //(*this).columns.push_back(Parameter((*iter1)->return_natural()));
      output.columns.push_back(Parameter((*iter1)->return_natural()));
      delete (*iter1);
    }
    return output;
  }
  void rename(vector<Parameter> columns){
    this->columns=columns;
  }
  RelationNode rho(vector<Parameter> columns) const{
    RelationNode output;
    output=(*this);
    output.rename(columns);
    return output;
  }
  RelationNode sigma(vector<Parameter> current_query) const{
    RelationNode output;
    output.node=(*this).node;
    //output=(*this);
    output.columns=current_query;
    vector<QueryParam*> current_query_param;
    vector<QueryParam*> delete_list;
    build_QueryParam_object(current_query, current_query_param, delete_list);
    for(set<vector<Parameter>>::iterator iter1=(*this).tuples.begin(); iter1 !=(*this).tuples.end(); iter1++){
      for(unsigned iter2=0; iter2< current_query_param.size(); iter2++) current_query_param[iter2]->reset();
      bool does_tuple_match=true;
      for(unsigned iter2=0; iter2 <current_query_param.size(); iter2++){
	does_tuple_match=current_query_param[iter2]->compare((*iter1)[iter2]);
	if(!(does_tuple_match)) break;
      }
      if(does_tuple_match){
	output.tuples.insert(*iter1);
      }
    }
    while (delete_list.size()>0){
      delete delete_list[delete_list.size()-1];
      delete_list.pop_back();
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
 private:
  void test_for_match(vector<QueryParam*> &new_columns, vector<QueryParam*> &first_columns, vector<QueryParam*> &second_columns, const RelationNode& second,set<vector<Parameter>>::iterator &iter1, set<vector<Parameter>>::iterator &iter2, RelationNode &output){
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
      debug.output("Joined tuples: "+vec_to_string((*iter1))+" and "+vec_to_string((*iter2)));
      vector<Parameter> add_tuple;
      for(vector<QueryParam*>::iterator iter3=new_columns.begin(); iter3 !=new_columns.end(); iter3++)
	add_tuple.push_back(Parameter((*iter3)->return_value()));
      //(*this).tuples.insert(add_tuple);
      output.tuples.insert(add_tuple);
    }
    else{
      debug.output("Failed joining tuples: "+vec_to_string((*iter1))+" and "+vec_to_string((*iter2)));
    }
  }
  void create_match_vec_col_1(vector<QueryParam*> &new_columns, vector<QueryParam*> &first_columns, vector<QueryParam*> &second_columns){
    for(vector<Parameter>::iterator iter1=this->columns.begin(); iter1 !=this->columns.end(); iter1++){
      bool found_match=false;
      for(vector<QueryParam*>::iterator iter2=new_columns.begin(); iter2 != new_columns.end();iter2++)
	if ((*iter1).return_ID() == (*iter2)->return_natural()){
	  found_match=true;
	  first_columns.push_back(*iter2);
	  break;
	}
      if (!(found_match)){
	QueryParam* new_queryparam=new QueryParam((*iter1).return_ID());
	if(new_queryparam->return_assigned()) cout <<"New QueryParam created: "<< (*iter1).return_ID();
	new_columns.push_back(new_queryparam);
	first_columns.push_back(new_queryparam);
      }
    }
  }
  void create_match_vec_col_2(vector<QueryParam*> &new_columns, vector<QueryParam*> &first_columns, vector<QueryParam*> &second_columns, const RelationNode& second){
    for(vector<Parameter>::const_iterator iter1=second.columns.begin(); iter1 !=second.columns.end(); iter1++){
      bool found_match=false;
      for(vector<QueryParam*>::iterator iter2=new_columns.begin(); iter2 != new_columns.end();iter2++)
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
  }
  void build_new_QueryParam(vector<Parameter> &current_query, vector<QueryParam*> &current_query_param, vector<QueryParam*> &delete_list, vector<Parameter>::iterator &iter2) const{
    bool found_param=false;
    vector<QueryParam*>::iterator iter3;
    for(iter3=current_query_param.begin(); iter3 !=current_query_param.end();iter3++)
      if ((*iter3)->return_natural() == iter2->return_ID()){
	found_param=true;
	break;
      }
    if(found_param) current_query_param.push_back(*iter3);
    else{
      delete_list.push_back(new QueryParam(iter2->return_ID()));
      current_query_param.push_back(delete_list[delete_list.size()-1]);
    }
  }
  void build_QueryParam_object(vector<Parameter> &current_query, vector<QueryParam*> &current_query_param, vector<QueryParam*> &delete_list) const{
    for(vector<Parameter>::iterator iter2=current_query.begin(); iter2 !=current_query.end(); iter2++){
      if(iter2->return_ID().substr(0,1)!="'"){
	build_new_QueryParam(current_query, current_query_param, delete_list, iter2);
      }
      else{
	delete_list.push_back(new QueryParam(iter2->return_ID()));
	current_query_param.push_back(delete_list[delete_list.size()-1]);
      }
    }
  }
};
