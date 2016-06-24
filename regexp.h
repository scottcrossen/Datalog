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
    debug.output("Regular expression object created.");
    debug.flag(1);
    for(unsigned iter1=0; iter1 < expression.size(); iter1++){
      debug.flag(3);
      if(expression.substr(iter1,1)=="["){
	debug.flag(5);
	unsigned iter2;
	for(iter2=1; iter2 < expression.size()-iter1; iter2++){
	  debug.flag(4);
	  if(expression.substr(iter1+iter2,1)=="]"){debug.flag(8); break;}
	}
	debug.flag(6);
	debug.output("found compact rule: "+expression.substr(iter1,iter2+1));
	sequence.push_back(expression.substr(iter1,iter2+1));
	iter1+=iter2;
      }
      else sequence.push_back(expression.substr(iter1,1));
      debug.output("Added char:"+sequence.back());
      debug.flags_display();
      debug.flags_clear();
      debug.flag(7);
    }
    sequence.push_back(" ");
    debug.output("Expression correctly formatted.");
  }
  ~RegExp(){
    debug.output("Reg. expression object deconstructed.");
    debug.flag(2);
  }
  void debug_on(bool turn_on){
    debug.turned_on=turn_on;
  }
  // Returns 0 (fail), 1 (still going), 2 (may have reached finish)
  int check(string current_word){
    debug.flags_clear();
    debug.flag(9);
    debug.flags_display();
    debug.flags_clear();
    unsigned string_spot=0;
    for (list<string>::iterator it=sequence.begin(); it !=sequence.end(); ++it){
      debug.output("comparing "+*it+" with "+current_word.substr(string_spot,1)+".");
      bool fail=false;
      if(*it=="*"){
	*it--;
	debug.flag(18);
      debug.output("Changing. Comparing "+*it+" with "+current_word.substr(string_spot,1)+".");
      }
      if(*it == " "){
	debug.flag(16);
	if (string_spot >= current_word.size()) return 2;
      }
      if(*it == "[A-Z]"){
	debug.flag(20);
	if(string_spot < current_word.size()){
	  debug.flag(19);
	  if(current_word.at(string_spot) < 65 || (current_word.at(string_spot) >90)){fail=true; debug.flag(10);}
	  } else fail=true;
      }
      else if(*it == "[A-Za-z]" || *it == "[a-zA-Z]" ){
	debug.flag(20);
	if(string_spot < current_word.size()){
	  debug.flag(19);
	  if((current_word.at(string_spot) < 65 || current_word.at(string_spot) >90) && (current_word.at(string_spot) < 97 || current_word.at(string_spot) >122)){fail=true; debug.flag(10);}
	  } else fail=true;
      }
      else if(*it == "[A-Za-z0-9]" || *it == "[a-zA-Z0-9]" || *it == "[0-9A-Za-z]" || *it == "[0-9a-zA-Z]" ){
	debug.flag(20);
	if(string_spot < current_word.size()){
	  debug.flag(19);
	  if((current_word.at(string_spot) < 65 || current_word.at(string_spot) >90) && (current_word.at(string_spot) < 97 || current_word.at(string_spot) >122) && (current_word.at(string_spot) < 48 || current_word.at(string_spot) >57)){fail=true; debug.flag(10);}
	  } else fail=true;
      }
      else if(*it != current_word.substr(string_spot,1)){fail=true; debug.flag(11);}
      debug.flag(13);
      if(fail==true){
	debug.flag(14);
	if(*(++it)=="*"){
	  if(string_spot >= current_word.size()){
	    debug.flag(21);
	    return 2;
	  }
	  debug.flag(17);
	  string_spot--;
	}
	else if(string_spot >= current_word.size()){
	  debug.flag(15);
	  return 1;
	}
	else{debug.flag(18); return 0;}
      }
      string_spot++;
    }
    return 2;
    debug.output("Check method accessed.");
  }
};
