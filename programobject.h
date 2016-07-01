#include <vector>
#include <set>
#include "debugger.h"
#pragma once
class ProgramObject{
 public:
  ProgramObject(){
    this->child_size=0;
    is_full=true;
  }
  ProgramObject(string type, int child_size){
    debug=Debugger("Prog O");
    this->type=type;
    this->child_size=child_size;
    if (child_size !=0)
      is_full=false;
    else
      is_full=true;
    debug.flag(1);
  }
  virtual ~ProgramObject(){
    debug.flag(2);
    for(unsigned iter2=0; iter2< children.size(); iter2++)
    delete children[iter2];
    debug.flag(3);
  }
  virtual void debug_on(bool turn_on){
    debug.flag(4);
    debug.turned_on=turn_on;
    for(unsigned iter2=0; iter2< children.size(); iter2++)
      children[iter2]->debug_on(turn_on);
    debug.flag(5);
    //debug.output(5,"Debug turned on.");
  }
  bool add(ProgramObject* new_obj){
    debug.flag(6);
    if (!(is_full)){
      if(children.size() >=1){
	if (!(children[children.size()-1]->full()))
	  children[children.size()-1]->add(new_obj);
      else
	children.push_back(new_obj);
      }
      else children.push_back(new_obj);
      if(children.size() == child_size && children[children.size()-1]->full())
	is_full=true;
      debug.flag(7);
      return true;
    }
    debug.flag(7);
    return false;
  } 
  void extend(){
    debug.flag(8);
    if(children.size() >=1){
      if (!(children[children.size()-1]->full()))
	children[children.size()-1]->extend();
      else child_size++;
    }
    else child_size++;
    debug.flag(9);
  }
  virtual string obj_print(int tabs){
    debug.flag(10);
    stringstream output;
    for(int iter=0; iter<tabs; iter++ ) output<<" ";
    output << type << endl;
    for(unsigned iter2=0; iter2< children.size(); iter2++)
      output << children[iter2]->obj_print(tabs+1);
    debug.flag(11);
    return output.str();
  }
  string print(){
    debug.flag(12);
    stringstream output;
    output << type << endl;
    for(unsigned iter2=0; iter2< children.size(); iter2++)
      output << children[iter2]->obj_print(1);
    debug.flag(13);
    return output.str();
  }
  virtual string display(){
    debug.flag(14);
    return type;
  }
  virtual string to_string(){
    debug.flag(15);
    stringstream output;
    for(unsigned iter=0;iter<children.size();iter++)
      output << children[iter]->to_string();
    debug.flag(16);
    return output.str();
  }
  void clear(){
    debug.flag(17);
    while(children.size() !=0){
      delete children[children.size()-1];
      children.pop_back();
    }
    debug.flag(18);
  }
  void find_print(string find, set<string> &output){
    debug.flag(19);
    if(this->type == find) output.insert(to_string());
    else
      for(unsigned iter=0; iter<children.size(); iter++)
	children[iter]->find_print(find,output);
    debug.flag(20);
  }
  void find_print(string find, vector<string> &output){
    debug.flag(21);
    if(this->type == find) output.push_back(to_string());
    else
      for(unsigned iter=0; iter<children.size(); iter++)
	children[iter]->find_print(find,output);
    debug.flag(21);
  }
  void find_error(string find, set<string> &output){
    debug.flag(22);
    if(this->type == find)
      for(unsigned iter=0; iter<children.size(); iter++)
	output.insert(children[iter]->display());
    else
      for(unsigned iter=0; iter<children.size(); iter++)
	children[iter]->find_error(find,output);
    debug.flag(23);
  }
  bool full(){
    debug.flag(24);
    return is_full;
  }
  string type;
 private:
  bool is_full;
  vector<ProgramObject*> children;
  unsigned child_size;
  Debugger debug;
};
