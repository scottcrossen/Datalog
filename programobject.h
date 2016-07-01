#include <vector>
#include <set>
#pragma once
class ProgramObject{
 public:
  ProgramObject(){
    this->child_size=0;
    is_full=true;
  }
  ProgramObject(string type, int child_size){
    this->type=type;
    this->child_size=child_size;
    if (child_size !=0)
      is_full=false;
    else
      is_full=true;
  }
  virtual ~ProgramObject(){
    for(unsigned iter2=0; iter2< children.size(); iter2++)
    delete children[iter2];
  }
  bool add(ProgramObject* new_obj){
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
      return true;
    }
    return false;
  } 
  void extend(){
    if(children.size() >=1){
      if (!(children[children.size()-1]->full()))
	children[children.size()-1]->extend();
      else child_size++;
    }
    else child_size++;
  }
  virtual string obj_print(int tabs){
    stringstream output;
    for(int iter=0; iter<tabs; iter++ ) output<<" ";
    output << type << endl;
    for(unsigned iter2=0; iter2< children.size(); iter2++)
      output << children[iter2]->obj_print(tabs+1);
    return output.str();
  }
  string print(){
    stringstream output;
    output << type << endl;
    for(unsigned iter2=0; iter2< children.size(); iter2++)
      output << children[iter2]->obj_print(1);
    return output.str();
  }
  virtual string display(){
    return type;
  }
  virtual string to_string(){
    stringstream output;
    for(unsigned iter=0;iter<children.size();iter++)
      output << children[iter]->to_string();
    return output.str();
  }
  void clear(){
    while(children.size() !=0){
      delete children[children.size()-1];
      children.pop_back();
    }
  }
  void find_print(string find, set<string> &output){
    if(this->type == find) output.insert(to_string());
    else
      for(unsigned iter=0; iter<children.size(); iter++)
	children[iter]->find_print(find,output);
  }
  void find_print(string find, vector<string> &output){
    if(this->type == find) output.push_back(to_string());
    else
      for(unsigned iter=0; iter<children.size(); iter++)
	children[iter]->find_print(find,output);
  }
  void find_error(string find, set<string> &output){
    if(this->type == find)
      for(unsigned iter=0; iter<children.size(); iter++)
	output.insert(children[iter]->display());
    else
      for(unsigned iter=0; iter<children.size(); iter++)
	children[iter]->find_error(find,output);
  }
  bool full(){return is_full;}
  string type;
 private:
  bool is_full;
  vector<ProgramObject*> children;
  unsigned child_size;
};
