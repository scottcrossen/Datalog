#include "programobject.h"
#pragma once

class DatalogProgram {
 public:
  DatalogProgram(){}
  DatalogProgram(ProgramObject object){
    this->object=object;
  }
  ~DatalogProgram(){}
  string toString(){
    return object.to_string();
  }
 private:
  ProgramObject object;
};

class Rule {
 public:
  Rule(){}
  Rule(ProgramObject object){
    this->object=object;
  }
  ~Rule(){}
  string toString(){
    return object.to_string();
  }
 private:
  ProgramObject object;
};

class Predicate {
 public:
  Predicate(){}
  Predicate(ProgramObject object){
    this->object=object;
  }
  ~Predicate(){}
  string toString(){
    return object.to_string();
  }
 private:
  ProgramObject object;
};

class Parameter {
 public:
  Parameter(){}
  Parameter(ProgramObject object){
    this->object=object;
  }
  ~Parameter(){}
  string toString(){
    return object.to_string();
  }
 private:
  ProgramObject object;
};
