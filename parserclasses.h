#pragma once

class AbstractObject {
 public:
  AbstractObject(){}
  ~AbstractObject(){}
  virtual string toString()=0;
};

class Parameter : public AbstractObject{
 public:
  Parameter(){}
  Parameter(string ID){
    this->ID=ID;
  }
  ~Parameter(){}
  string toString(){
    return ID;
  }
  string return_ID(){
    return toString();
  }
 private:
  string ID;
};

class Predicate : public AbstractObject{
 public:
  Predicate(){}
  Predicate(Parameter ID, vector<Parameter> parameter_list){
    this->ID=ID;
    this->parameter_list=parameter_list;
  }
  Predicate(Parameter ID){
    this->ID=ID;
  }
  void add_parameter(Parameter parameter){
    parameter_list.push_back(parameter);
  }
  ~Predicate(){}
  string toString(){
    stringstream output;
    output << ID.toString() << "(";
    for(unsigned iter=0; iter < parameter_list.size()-1; iter++)
      output << parameter_list[iter].toString() << ",";
    output << parameter_list[parameter_list.size()-1].toString() << ")";
    return output.str();
  }
  string return_ID(){
    return ID.return_ID();
  }
  vector<Parameter> return_parameter_list(){
    return parameter_list;
  }
 private:
  Parameter ID;
  vector<Parameter> parameter_list;
};

class Rule : public AbstractObject{
 public:
  Rule(){};
  Rule(Predicate rule, vector<Predicate> predicates){
    this->rule=rule;
    this->predicates=predicates;
  }
  Rule(Predicate rule){
    this->rule=rule;
  }
  void add_predicate(Parameter predicate){
    predicates.push_back(predicate);
  }
  ~Rule(){}
  string toString(){
    stringstream output;
    output << rule.toString() << " :- ";
    for(unsigned iter=0; iter <predicates.size()-1; iter++)
      output << predicates[iter].toString() <<",";
    output << predicates[predicates.size()-1].toString();
    return output.str();
  }
 private:
  Predicate rule;
  vector<Predicate> predicates;
};

class DatalogProgram : public AbstractObject {
 public:
  DatalogProgram(){}
  DatalogProgram(vector<Predicate> schemes, vector<Predicate> facts, vector<Rule> rules, vector<Predicate> queries, set<string> domain){
  this->schemes=schemes;
  this->facts=facts;
  this->rules=rules;
  this->queries=queries;
  this->domain=domain;
  }
  ~DatalogProgram(){}
  string toString(){
    stringstream output;
    output << "Schemes(" << schemes.size() <<"):"<<endl;
    for(unsigned iter=0; iter < schemes.size(); iter++)
      output <<"  "<< schemes[iter].toString()<<endl;
    output << "Facts(" << facts.size() <<"):"<<endl;
    for(unsigned iter=0; iter < facts.size(); iter++)
      output <<"  "<< facts[iter].toString()<<endl;
    output << "Rules(" << rules.size() <<"):"<<endl;
    for(unsigned iter=0; iter < rules.size(); iter++)
      output <<"  "<< rules[iter].toString()<<endl;
    output << "Queries(" << queries.size() <<"):"<<endl;
    for(unsigned iter=0; iter < queries.size(); iter++)
      output <<"  "<< queries[iter].toString()<<endl;
    output << "Domain(" << domain.size() <<"):" << endl;
    for(set<string>::iterator iter=domain.begin(); iter !=domain.end(); iter++)
      output << "  " << *iter<<endl;
    return output.str();
  }
  void add_scheme(Predicate scheme){
    schemes.push_back(scheme);
  }
  void add_fact(Predicate fact){
    facts.push_back(fact);
  }
  void add_rule(Rule rule){
    rules.push_back(rule);
  }
  void add_query(Predicate query){
    queries.push_back(query);
  }
  void add_domain(string add){
    domain.insert(add);
  }
  void set_domain(set<string> domain){
    this->domain=domain;
  }
  vector<Predicate> return_schemes(){
    return schemes;
  }
  vector<Predicate> return_facts(){
    return facts;
  }
  vector<Rule> return_rules(){
    return rules;
  }
  vector<Predicate> return_queries(){
    return queries;
  }
  set<string> return_domain(){
    return domain;
  }
 private:
  vector<Predicate> schemes;
  vector<Predicate> facts;
  vector<Rule> rules;
  vector<Predicate> queries;
  set<string> domain;
};
