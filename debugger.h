#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#pragma once
using namespace std;
const bool debug_on=false;
const bool editor=false;
class Debugger{
 private:
  vector<int> flags;
  bool editor_interface;
  string object_name;
 public:
  bool turned_on;
  Debugger(){}
  Debugger(string object_name){
    this->turned_on=debug_on;
    this->editor_interface=editor;
    this->object_name=object_name;
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tInitialized." <<endl;
      else cout << "Debug: "+object_name+":\tInitialized." << endl;
    }
  }
  Debugger(bool editor_interface, bool turned_on, string object_name){
    this->turned_on=turned_on;
    this->editor_interface=editor_interface;
    this->object_name=object_name;
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tInitialized." <<endl;
      else cout << "Debug: "+object_name+":\tInitialized." << endl;
    }
  }
  ~Debugger(){
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tTerminated." <<endl;
      else cout << "Debug: "+object_name+":\tTerminated." << endl;
    }
  }
  void flag(int add_flag){
    if(turned_on){
      flags.push_back(add_flag);
      /*
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tFlag encountered:\t"<< add_flag << endl;
      else cout << "Debug: "+object_name+":\tFlag encountered:\t" << add_flag << endl;
      */
    }
  }
  void flags_display(){
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tDisplaying flags found:\t";
      else cout << "Debug: "+object_name+":\tDisplaying flags found:\t";
      for(unsigned i=0; i < flags.size(); i++)
	cout << flags[i] << " ";
      cout << endl;
      flags_clear();
    }
  }
  void flags_display(int add_flag){
    if(turned_on){
      flag(add_flag);
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tDisplaying flags found:\t";
      else cout << "Debug: "+object_name+":\tDisplaying flags found:\t";
      for(unsigned i=0; i < flags.size(); i++)
	cout << flags[i] << " ";
      cout << endl;
      flags_clear();
    }
  }
  void output(int add_flag, string current_output){
    if(turned_on){
      flag(add_flag);
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tStatus line:\t\t" << current_output << endl;
      else cout << "Debug: "+object_name+":\tStatus line:\t\t" << current_output << endl;
    }
  }
  void output(string current_output){
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tStatus line:\t\t" << current_output << endl;
      else cout << "Debug: "+object_name+":\tStatus line:\t\t" << current_output << endl;
    }
  }
  void flags_clear(){
    if(turned_on){
      for (unsigned i=0; flags.size() >0; i++) flags.pop_back();
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tFlags cleared." << endl;
      else cout << "Debug: "+object_name+":\tFlags cleared." << endl;
    }
  }
  bool encountered(int current_flag){
    if(turned_on){
      for (unsigned i=0; i < flags.size(); i++)
	if(flags[i]==current_flag){
	  if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tFlag "<< current_flag<<" conditional met:\tTrue"<< endl;
	  else cout << "Debug: "+object_name+":\tFlag "<< current_flag << " conditional met:\tTrue" << endl;
	  return true;
	}
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tFlag " << current_flag << " conditional met:\tFalse"<< endl;
      else cout << "Debug: "+object_name+":\tFlag " << current_flag << " conditional met:\tFalse" << endl;
      return false;
    } else return false;
  }
  void abort(bool conditional_met){
    if(turned_on){
      if(conditional_met){
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tAborting. Unknown flag." << endl;
	else cout << "Debug: "+object_name+":\tAborting. Unknown flag." << endl;
	flags_display();
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tTerminated." <<endl;
	else cout << "Debug: "+object_name+":\tTerminated." << endl;
	exit(0);
      }
      else {
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tAbort condition failed." << endl;
	else cout << "Debug: "+object_name+":\tAbort condition failed." << endl;
      }
    }
  }
  void abort(bool conditional_met, int current_flag){
    if(turned_on){
      if(conditional_met){
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tAborting with flag:\t" << current_flag << endl;
	else cout << "Debug: "+object_name+":\tAborting with flag:\t" << current_flag << endl;
	flags_display();
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tTerminated." <<endl;
	else cout << "Debug: "+object_name+":\tTerminated." << endl;
	exit(0);
      }
      else {
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tAbort condition failed." << endl;
	else cout << "Debug:\tAbort condition failed." << endl;
      }
    }
  }
  void abort(){
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tAborting. Absolute." << endl;
      else cout << "Debug: "+object_name+":\tAborting. Absolute." << endl;
      flags_display();
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tTerminated." <<endl;
      else cout << "Debug: "+object_name+":\tTerminated." << endl;
      exit(0);
    }
  }
  void pause(){
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m \033[1;31m"+object_name+":\033[0m\tPaused. Press Enter.";
      else cout << "Debug: "+object_name+":\tPaused. Press Enter." << endl;
      cin.get();
    }
  }
};
