#pragma once

class Parameter {
 public:
  Parameter(){}
  Parameter(string ID){
    this->ID=ID;
  }
  ~Parameter(){}
  string toString(){
    return ID;
  }
 private:
  string ID;
};

class Predicate {
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
 private:
  Parameter ID;
  vector<Parameter> parameter_list;
};

class Rule {
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

class DatalogProgram {
 public:
  DatalogProgram(){}
  ~DatalogProgram(){}
  string toString(){
    stringstream output;
    output << "Schemes(" << schemes.size() <<"):"<<endl;
    for(unsigned iter=0; iter < schemes.size(); iter++)
      output <<"  "<< schemes[iter].toString()<<endl;
    output << "Facts(" << schemes.size() <<"):"<<endl;
    for(unsigned iter=0; iter < schemes.size(); iter++)
      output <<"  "<< schemes[iter].toString()<<endl;
    output << "Rules(" << schemes.size() <<"):"<<endl;
    for(unsigned iter=0; iter < schemes.size(); iter++)
      output <<"  "<< schemes[iter].toString()<<endl;
    output << "Queries(" << schemes.size() <<"):"<<endl;
    for(unsigned iter=0; iter < schemes.size(); iter++)
      output <<"  "<< schemes[iter].toString()<<endl;
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
 private:
  vector<Predicate> schemes;
  vector<Predicate> facts;
  vector<Rule> rules;
  vector<Predicate> queries;
};
