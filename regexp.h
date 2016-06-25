#include "debugger.h"
#include <string>
#include <list>
#pragma once
using namespace std;
class RegExp{
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
      if(*it=="*") *it--;
      if(*it == " " && string_spot >= current_word.size()) return 2;
      compare_current(it,string_spot, current_word, fail);
      debug.flag(12);
      int ret_int=check_failed(fail,it,string_spot,current_word);
      if (ret_int !=-1) return ret_int; // remove this line when pasting above function in.
      string_spot++;
    }
    debug.flag(13);
    return 2;
  }
 private:
  Debugger debug;
  list<string> sequence;
  string expression;
  void compare_current(list<string>::iterator &it, unsigned &string_spot, string &current_word, bool &fail){
    if(*it == "[A-Z]") is_az(string_spot, current_word, fail);
    else if(*it == "[A-Za-z]" || *it == "[a-zA-Z]" ) is_azaz(string_spot, current_word, fail);
    else if(*it == "[A-Za-z0-9]" || *it == "[a-zA-Z0-9]")
      is_azaz09(string_spot, current_word, fail);
    else if(*it != current_word.substr(string_spot,1)) fail=true; 
}
  void is_az(unsigned &string_spot, string &current_word, bool &fail){
    if(string_spot < current_word.size()){
      if(current_word.at(string_spot) < 65 || (current_word.at(string_spot) >90)) fail=true;
    } else fail=true;
  }
  void is_azaz(unsigned &string_spot, string &current_word, bool &fail){
    if(string_spot < current_word.size()){
      if((current_word.at(string_spot) < 65 || current_word.at(string_spot) >90) && (current_word.at(string_spot) < 97 || current_word.at(string_spot) >122)) fail=true;
    } else fail=true;
  }
  void is_azaz09(unsigned &string_spot, string &current_word, bool &fail){
    if(string_spot < current_word.size()){
      if((current_word.at(string_spot) < 65 || current_word.at(string_spot) >90) && (current_word.at(string_spot) < 97 || current_word.at(string_spot) >122) && (current_word.at(string_spot) < 48 || current_word.at(string_spot) >57)) fail=true;
    } else fail=true;
}
  int check_failed(bool &fail, list<string>::iterator &it, unsigned &string_spot, string &current_word){
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
    return -1; //remove this when pasting back in.
  }
};
