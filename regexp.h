#include "debugger.h"
#include <string>
#include <list>
#pragma once
using namespace std;
class RegExp{
 private:
  Debugger debug;
  list<string> sequence;
  string expression;
 public:
  RegExp(string expression){
    this->expression=expression;
    debug=Debugger("Exp");
    debug.output(1,"Regular expression object created.");
    for(unsigned iter1=0; iter1 < expression.size(); iter1++){
      debug.flag(2);
      if(expression.substr(iter1,1)=="["){
	unsigned iter2;
	for(iter2=1; iter2 < expression.size()-iter1; iter2++){
	  if(expression.substr(iter1+iter2,1)=="]") break;
	}
	//debug.output(3,"found compact rule: "+expression.substr(iter1,iter2+1));
	sequence.push_back(expression.substr(iter1,iter2+1));
	iter1+=iter2;
      }
      else sequence.push_back(expression.substr(iter1,1));
    }
    sequence.push_back(" ");
    debug.output(4,"Expression correctly formatted.");
  }
  ~RegExp(){
    debug.output(5,"Reg. expression object deconstructed.");
  }
  void debug_on(bool turn_on){
    debug.flag(6);
    debug.turned_on=turn_on;
    debug.output(7,"Debug turned on.");
  }
  // Returns 0 (fail), 1 (still going), 2 (may have reached finish)
  int check(string current_word){
    debug.flag(8);
    unsigned string_spot=0;
    for (list<string>::iterator it=sequence.begin(); it !=sequence.end(); ++it){
      debug.flag(9);
      //debug.output(10,"comparing "+*it+" with "+current_word.substr(string_spot,1)+".");
      bool fail=false;
      if(*it=="*"){
	*it--;
	//debug.output(11,"comparing "+*it+" with "+current_word.substr(string_spot,1)+".");
      }
      if(*it == " "){
	if (string_spot >= current_word.size()) return 2;
      }
      if(*it == "[A-Z]"){
	if(string_spot < current_word.size()){
	  if(current_word.at(string_spot) < 65 || (current_word.at(string_spot) >90)) fail=true;
	  } else fail=true;
      }
      else if(*it == "[A-Za-z]" || *it == "[a-zA-Z]" ){
	if(string_spot < current_word.size()){
	  if((current_word.at(string_spot) < 65 || current_word.at(string_spot) >90) && (current_word.at(string_spot) < 97 || current_word.at(string_spot) >122)) fail=true;
	  } else fail=true;
      }
      else if(*it == "[A-Za-z0-9]" || *it == "[a-zA-Z0-9]" || *it == "[0-9A-Za-z]" || *it == "[0-9a-zA-Z]" ){
	if(string_spot < current_word.size()){
	  if((current_word.at(string_spot) < 65 || current_word.at(string_spot) >90) && (current_word.at(string_spot) < 97 || current_word.at(string_spot) >122) && (current_word.at(string_spot) < 48 || current_word.at(string_spot) >57)) fail=true;
	  } else fail=true;
      }
      else if(*it != current_word.substr(string_spot,1)) fail=true; 
      debug.flag(12);
      if(fail==true){
	if(*(++it)=="*"){
	  if(string_spot >= current_word.size())
	    return 2;
	  string_spot--;
	}
	else if(string_spot >= current_word.size())
	  return 1;
	else return 0;
      }
      string_spot++;
    }
    debug.flag(13);
    return 2;
  }
};
