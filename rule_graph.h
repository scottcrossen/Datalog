#include "parserclasses.h"
#pragma once
class GraphNode{
  public:
    GraphNode(){};
    ~GraphNode(){};
    GraphNode(Parameter relation_name){
      this->relation_name=relation_name;
      this->visited=false;
    };
    Rule rule;
    Parameter relation_name;
    unsigned postfix;
    bool visited;
    int rule_num;
    set<GraphNode*> children;
    string return_ID(){
      stringstream output;
      output <<"R"<<rule_num;
      return output.str();
    }
    string print(){
      stringstream output;
      output<<"  "<<this->return_ID()<<":";
      for(set<GraphNode*>::iterator iter1=children.begin(); iter1 !=children.end();iter1++)
	output<<" "<< (*iter1)->return_ID();
      return output.str();
    }
    string print_order(){
      stringstream output;
      output <<"  "<<this->return_ID()<<": "<<postfix;
      return output.str();
    }
  };
class RuleGraph{
 private:
  vector<Rule> rules;
  vector<GraphNode*> rule_graph;
  vector<GraphNode*> reverse_rule_graph;
 public:
  RuleGraph(){}
  ~RuleGraph(){
    for(unsigned iter1=0;iter1<rule_graph.size();iter1++)
      delete rule_graph[iter1];
    for(unsigned iter1=0;iter1<reverse_rule_graph.size();iter1++)
      delete reverse_rule_graph[iter1];
    while(rule_graph.size()>0) rule_graph.pop_back();
    while(reverse_rule_graph.size()>0) reverse_rule_graph.pop_back();
  }
  RuleGraph(vector<Rule> rules){
    this->rules=rules;
    for(unsigned iter1=0; iter1 < rules.size(); iter1++){
      rule_graph.push_back(new GraphNode(rules[iter1].return_rule().return_parameter()));
      rule_graph[rule_graph.size()-1]->rule_num=iter1;
      rule_graph[rule_graph.size()-1]->rule=rules[iter1];
    }
    for(unsigned iter1=0; iter1 <rules.size(); iter1++){
vector<Predicate> current_predicates=rules[iter1].return_predicates();
      for(vector<Predicate>::iterator iter2=current_predicates.begin(); iter2 != current_predicates.end(); iter2++){
	for(unsigned iter3=0; iter3<rules.size(); iter3++)
	  if((*iter2).return_parameter()==rule_graph[iter3]->relation_name)
	    rule_graph[iter1]->children.insert(rule_graph[iter3]);
      }
    }
    /*
    this->rules=rules;
    for(unsigned iter1=0; iter1 <rules.size(); iter1++){
      unsigned iter2;
      for(iter2=0; iter2 <rule_graph.size(); iter2++)
	if(rule_graph[iter2]->relation_name==rules[iter1].return_rule().return_parameter()) break;
      if(iter2 == rule_graph.size()){
	cout << "Added"<<int(iter1)<<" "<<rules[iter1].return_rule().return_parameter().return_ID() <<endl;
	rule_graph.push_back(new GraphNode(rules[iter1].return_rule().return_parameter()));
	rule_graph[rule_graph.size()-1]->rule_num=int(iter1);
      }
      vector<Predicate> current_predicates=rules[iter1].return_predicates();
      for(vector<Predicate>::iterator iter3=current_predicates.begin(); iter3 != current_predicates.end(); iter3++){
	GraphNode* temporary=add_node((*iter3).return_parameter());
	cout << "child "<<temporary->relation_name.return_ID()<<" has num "<< temporary->rule_num<<endl;
	rule_graph[iter2]->children.insert(temporary);
      }
      rule_graph[iter2]->rule_num=int(iter1);
    }*/
    reverse_links();
  }
  GraphNode* add_node(Parameter new_name){
    for(unsigned iter1=0; iter1 <rule_graph.size(); iter1++){
      //cout << "comparing "<<rule_graph[iter1]->relation_name.return_ID()<<" and " << new_name.return_ID()<<"+"<<endl;
      if(rule_graph[iter1]->relation_name.return_ID()==new_name.return_ID()){
	cout << "found with num "<<rule_graph[iter1]->rule_num <<endl;
	return rule_graph[iter1];
      }
    }
    rule_graph.push_back(new GraphNode(new_name));
    cout << "Added-1 "<<new_name.return_ID()<<endl;
    rule_graph[rule_graph.size()-1]->rule_num=-1;
    return rule_graph[rule_graph.size()-1];
  }
  void clear_tree(){
    for(vector<GraphNode*>::iterator iter1=rule_graph.begin(); iter1 != rule_graph.end(); iter1++)
      (*iter1)->visited=false;
    for(vector<GraphNode*>::iterator iter1=reverse_rule_graph.begin(); iter1 != reverse_rule_graph.end(); iter1++)
      (*iter1)->visited=false;
  }
  void build_tree(GraphNode* root,unsigned &current_count){
    if(!(root->visited)){
      root->visited=true;
      set<GraphNode*> current_set=(*root).children;
      for(set<GraphNode*>::iterator iter1=current_set.begin(); iter1 !=current_set.end(); iter1++)
	build_tree((*iter1), current_count);
      root->postfix=current_count++;
    }
  };
  GraphNode* add_reverse_node(Parameter new_name){
    for(unsigned iter1=0; iter1 <reverse_rule_graph.size(); iter1++)
      if(reverse_rule_graph[iter1]->relation_name==new_name)
	return reverse_rule_graph[iter1];
    reverse_rule_graph.push_back(new GraphNode(new_name));
    return reverse_rule_graph[reverse_rule_graph.size()-1];
  }
  void reverse_links(){
    for(unsigned iter1=0; iter1< rule_graph.size(); iter1++){
      reverse_rule_graph.push_back(new GraphNode(rule_graph[iter1]->relation_name));
      reverse_rule_graph[reverse_rule_graph.size()-1]->rule_num=iter1;
      reverse_rule_graph[reverse_rule_graph.size()-1]->rule=rules[iter1];
    }
    for(unsigned iter1=0; iter1< rule_graph.size(); iter1++){
      set<GraphNode*> current_set=rule_graph[iter1]->children;
      for(set<GraphNode*>::iterator iter2=current_set.begin(); iter2 != current_set.end(); iter2++)
	for(unsigned iter3=0; iter3< reverse_rule_graph.size(); iter3++)
	  if(reverse_rule_graph[iter3]->relation_name==(*iter2)->relation_name)
	    reverse_rule_graph[iter3]->children.insert(reverse_rule_graph[iter1]);
    }
    /*
    for(vector<GraphNode*>::iterator iter1=rule_graph.begin(); iter1 !=rule_graph.end(); iter1++){
      GraphNode* current_parent=add_reverse_node((*iter1)->relation_name);
      set<GraphNode*> current_set=(*iter1)->children;
      for(set<GraphNode*>::iterator iter2=current_set.begin(); iter2 != current_set.end(); iter2++){
	GraphNode* current_child=add_reverse_node((*iter2)->relation_name);
	current_child->children.insert(current_parent);
      }
    }
    */	
  }
  string dependency_graph(){
    string output="Dependency Graph\n";
    for(unsigned iter1=0; iter1<rule_graph.size(); iter1++){
      output+=rule_graph[iter1]->print();
      output+="\n";
    }
    return output;
  }
  string reverse_dependency_graph(){
    string output="Reverse Graph\n";
    for(unsigned iter1=0; iter1<reverse_rule_graph.size(); iter1++){
      output+=reverse_rule_graph[iter1]->print();
      output+="\n";
    }
    return output;
  }
  string display_reverse_postfix(){
    string output="Postorder Numbers\n";
    for(unsigned iter1=0; iter1 <reverse_rule_graph.size(); iter1++){
      output+=reverse_rule_graph[iter1]->print_order();
      output+="\n";
    }
    return output;
  }
  vector<GraphNode> return_reverse_list(){
    vector<GraphNode> output;
    for(unsigned iter1=0; iter1< reverse_rule_graph.size(); iter1++){
      output.push_back(GraphNode(reverse_rule_graph[iter1]->relation_name));
      output[iter1].rule_num=reverse_rule_graph[iter1]->rule_num;
      output[iter1].rule=reverse_rule_graph[iter1]->rule;
      output[iter1].postfix=reverse_rule_graph[iter1]->postfix;
    }
    return output;
  }
  void sort_reverse_post_order(){
    vector<GraphNode*> output;
    for(unsigned iter1=reverse_rule_graph.size(); iter1>0; iter1--)
      for(unsigned iter2=0; iter2<reverse_rule_graph.size(); iter2++)
	if(reverse_rule_graph[iter2]->postfix==iter1)
	  output.push_back(reverse_rule_graph[iter2]);
    if(output.size() == reverse_rule_graph.size())
      reverse_rule_graph=output;
  }
  string display_reverse_order(){
    stringstream output;
    output <<"SCC Search Order"<<endl;
    for(unsigned iter1=0; iter1 <reverse_rule_graph.size(); iter1++){
      output<<"  R"<<reverse_rule_graph[iter1]->rule_num;
      output<<"\n";
    }
    return output.str();
  }
  string build(){
    stringstream output;
    output << dependency_graph()<<endl;
    output << reverse_dependency_graph()<<endl;
    unsigned postfix=1;
    for(unsigned iter1=0; iter1 <reverse_rule_graph.size(); iter1++)
      build_tree(reverse_rule_graph[iter1],postfix);
    output <<display_reverse_postfix()<<endl;
    sort_reverse_post_order();
    output << display_reverse_order();
    return output.str();
  }
};
