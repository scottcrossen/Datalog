#include "parserclasses.h"
#include "databaseclasses.h"
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
    debug.flag(10);
    vector<Predicate> schemes=program.return_schemes();
    for(unsigned iter1=0; iter1 < schemes.size(); iter1++)
      relations.insert(RelationNode(schemes[iter1]));
    //debug_on(true);
    add_schemes();
    add_facts();
    debug.output(11,"Database created from object.");
  }
  void add_schemes(){
    debug.flag(12);
    current_output+="Scheme Evaluation\n\n";
    debug.output(13,"Schemes added");
  }
  void add_facts(){
    debug.flag(14);
    current_output+="Fact Evaluation\n\n";
    stringstream output;
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
      if(!(found_relation)) debug.abort(18);
    }
    debug.flag(15);
    for(set<RelationNode>::iterator iter=relations.begin(); iter!=relations.end(); iter++){
      output<< (*iter).node.return_ID() <<endl;
      for(set<vector<Parameter>>::iterator iter2=(*iter).tuples.begin(); iter2 != (*iter).tuples.end(); iter2++){
	output << " ";
	for(unsigned iter3=0; iter3 < (*iter).columns.size(); iter3++)
	  output <<" "<< (*iter).columns[iter3].return_ID()<<"="<<(*iter2)[iter3].return_ID();
	output << endl;
      }
      output<<endl;
    }
    current_output+=output.str();
    debug.output(16,"Facts Added");
  }
  void apply_queries(){
    debug.flag(17);
    current_output+="Query Evaluation\n\n";
    stringstream output;
    vector<Predicate> queries=program.return_queries();
    for(vector<Predicate>::iterator iter1=queries.begin(); iter1 !=queries.end(); iter1++){
      vector<string> select;
      vector<string> project;
      vector<string> rename;
      vector<Parameter> current_query=iter1->return_parameter_list();
      vector<QueryParam*> current_query_param;
      vector<QueryParam*> delete_list;
      build_QueryParam_object(current_query, current_query_param, delete_list);
      find_query(iter1, current_query, current_query_param, delete_list,select,project,rename);
      while (delete_list.size()>0){
	delete delete_list[delete_list.size()-1];
	delete_list.pop_back();
      }
      write_query_out(select,project,rename,iter1, output);
    }
    current_output+=output.str();
    debug.output(18,"Queries applied.");
  }
  void output_file(string file){
    debug.flag(19);
    out_file=file;
    debug.output(20,"Output file changed to "+file);
  }
  void write_out(){
    debug.flag(21);
    ofstream file_out;
    file_out.open(out_file.c_str());
    file_out << current_output;
    file_out.close();
    debug.output(22,"Output file written.");
  }
 private:
  string vec_to_string(vector<Parameter> vec){
    debug.flag(23);
    stringstream output;
    output <<"(";
    for(unsigned iter=0; iter<vec.size()-1;iter++)
      output << vec[iter].return_ID()<<",";
    output << vec[vec.size()-1].return_ID() << ")";
    debug.flag(24);
    return output.str();
  }
  string vec_to_string(vector<QueryParam*> vec){
    debug.flag(23);
    stringstream output;
    output <<"(";
    for(unsigned iter=0; iter<vec.size()-1;iter++)
      output << vec[iter]->return_natural()<<",";
    output << vec[vec.size()-1]->return_natural() << ")";
    debug.flag(24);
    return output.str();
  }
  void write_query_out(vector<string> &select, vector<string> &project, vector<string> &rename, vector<Predicate>::iterator &iter1, stringstream &output){
    debug.flag(25);
    output<<(*iter1).toString()<<"? ";
    if(select.size()==0) output << "No"<<endl;
    else{
      output << "Yes("<< select.size()<<")"<<endl;
      output <<"select" <<endl;
      for(unsigned iter2=0; iter2<select.size(); iter2++){
	output << select[iter2] <<endl;
      }
      output <<"project" <<endl;
      for(unsigned iter2=0; iter2<project.size(); iter2++){
	output << project[iter2]<<endl;
      }
      output <<"rename" <<endl;
      for(unsigned iter2=0; iter2<rename.size(); iter2++){
	output << rename[iter2]<<endl;
      }
    }
    output <<endl;
    debug.flag(26);
  }
  void tuple_matches(vector<Parameter> &current_query, vector<QueryParam*> &current_query_param, vector<QueryParam*> &delete_list, vector<string> &select, vector<string> &project, vector<string> &rename, set<RelationNode>::iterator &iter2, set<vector<Parameter>>::iterator &iter3){
    debug.flag(27);
    stringstream for_debug;
    for_debug<< "found match for relation "<<(*iter2).node.return_ID()<<": " << "Query: "<< vec_to_string(current_query_param) <<" Tuple: "<<vec_to_string((*iter3));
    debug.output(for_debug.str());
    stringstream output_string1;
    stringstream output_string2;
    stringstream output_string3;
    for(unsigned iter4=0; iter4< current_query_param.size(); iter4++) current_query_param[iter4]->reset();
    output_string1 <<" ";
    for(unsigned iter4=0; iter4<current_query_param.size();iter4++){
      if(!(current_query_param[iter4]->return_assigned())){
	current_query_param[iter4]->compare((*iter3)[iter4]);
	output_string2 << " "<<(*iter2).columns[iter4].return_ID()<<"="<< current_query_param[iter4]->return_value();
	output_string3 <<" "<<current_query_param[iter4]->return_natural() <<"=" <<current_query_param[iter4]->return_value();
      }
      output_string1 << " "<<(*iter2).columns[iter4].return_ID()<<"="<< current_query_param[iter4]->return_value();
    }
    select.push_back(output_string1.str());
    if(output_string2.str().size()!=0)
      project.push_back(" "+output_string2.str());
    if(output_string3.str().size()!=0)
      rename.push_back(" "+output_string3.str());
    debug.flag(28);
  }
  void does_tuple_match(vector<Parameter> &current_query, vector<QueryParam*> &current_query_param, vector<QueryParam*> &delete_list, vector<string> &select, vector<string> &project, vector<string> &rename, set<RelationNode>::iterator &iter2, set<vector<Parameter>>::iterator &iter3){
    debug.flag(29);
    bool does_tuple_match=true;
    for(unsigned iter4=0; iter4 <current_query_param.size(); iter4++){
      does_tuple_match=current_query_param[iter4]->compare((*iter3)[iter4]);
      if(!(does_tuple_match)) break;
    }
    if(does_tuple_match){
      tuple_matches(current_query, current_query_param, delete_list,select,project,rename,iter2,iter3);
    }
    debug.flag(30);
  }
  void find_query(vector<Predicate>::iterator &iter1, vector<Parameter> &current_query, vector<QueryParam*> &current_query_param, vector<QueryParam*> &delete_list, vector<string> &select, vector<string> &project, vector<string> &rename){
    debug.flag(31);
    for(set<RelationNode>::iterator iter2=relations.begin(); iter2 !=relations.end(); iter2++){
      if(iter2->node.return_ID()==iter1->return_ID()){
	for(set<vector<Parameter>>::iterator iter3=(*iter2).tuples.begin(); iter3 !=(*iter2).tuples.end(); iter3++){
	  for(unsigned iter4=0; iter4< current_query_param.size(); iter4++) current_query_param[iter4]->reset();
	  does_tuple_match(current_query, current_query_param, delete_list,select,project,rename,iter2,iter3);
	}
      }
    }
    debug.flag(32);
  }
  void build_new_QueryParam(vector<Parameter> &current_query, vector<QueryParam*> &current_query_param, vector<QueryParam*> &delete_list, vector<Parameter>::iterator &iter2){
    debug.flag(33);
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
    debug.flag(34);
  }
  void build_QueryParam_object(vector<Parameter> &current_query, vector<QueryParam*> &current_query_param, vector<QueryParam*> &delete_list){
    debug.flag(35);
    for(vector<Parameter>::iterator iter2=current_query.begin(); iter2 !=current_query.end(); iter2++){
      if(iter2->return_ID().substr(0,1)!="'"){
	build_new_QueryParam(current_query, current_query_param, delete_list, iter2);
      }
      else{
	delete_list.push_back(new QueryParam(iter2->return_ID()));
	current_query_param.push_back(delete_list[delete_list.size()-1]);
      }
    }
    debug.flag(36);
  }
  Debugger debug;
  set<RelationNode> relations;
  string out_file;
  string current_output;
  DatalogProgram program;
};
