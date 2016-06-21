#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Debugger{
 private:
  vector<int> flags;
  bool turned_on;
  bool last_flag;
  bool editor_interface;
 public:
  Debugger(bool editor_interface, bool turned_on){
    this->turned_on=turned_on;
    this->editor_interface=editor_interface;
    last_flag=false;
    if(turned_on){
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Initialized." <<endl;
      else cout << "Debug: Initialized." << endl;
    }
  }
  ~Debugger(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Terminated." <<endl;
      else cout << "Debug: Terminated." << endl;
    }
  }
  void flag(int add_flag){
    if(turned_on){
      flags.push_back(add_flag);
      if(!(last_flag)){
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Flags encountered:\t"<< add_flag;
	else cout << "Debug: Flags encountered:\t" << add_flag;
      }
      else cout << " " << add_flag;
      last_flag=true;
    }
  }
  void flags_display(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Displaying flags found:\t";
      else cout << "Debug: Displaying flags found:\t";
      for(unsigned i=0; i < flags.size(); i++)
	cout << flags[i] << " ";
      cout << endl;
    }
  }
  void output(string current_output){
    if(turned_on){
      if(last_flag){cout << endl; last_flag=false;}
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Status line:\t\t" << current_output << endl;
      else cout << "Debug: Status line:\t\t" << current_output << endl;
    }
  }
  void flags_clear(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      for (unsigned i=0; i < flags.size(); i++) flags.pop_back();
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Flags cleared." << endl;
      else cout << "Debug: Flags cleared." << endl;
    }
  }
  bool encountered(int current_flag){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      for (unsigned i=0; i < flags.size(); i++)
	if(flags[i]==current_flag){
	  if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Flag "<< current_flag<<" conditional met:\tTrue"<< endl;
	  else cout << "Debug: Flag "<< current_flag << " conditional met:\tTrue" << endl;
	  return true;
	}
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Flag " << current_flag << " conditional met:\tFalse"<< endl;
      else cout << "Debug: Flag " << current_flag << " conditional met:\tFalse" << endl;
      return false;
    } else return false;
  }
  void abort(bool conditional_met){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      if(conditional_met){
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Aborting. Unknown flag." << endl;
	else cout << "Debug: Aborting. Unknown flag." << endl;
	flags_display();
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Terminated." <<endl;
	else cout << "Debug: Terminated." << endl;
	exit(0);
      }
      else {
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Abort condition failed." << endl;
	else cout << "Debug: Abort condition failed." << endl;
      }
    }
  }
  void abort(bool conditional_met, int current_flag){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      if(conditional_met){
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Aborting with flag:\t" << current_flag << endl;
	else cout << "Debug: Aborting with flag:\t" << current_flag << endl;
	flags_display();
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Terminated." <<endl;
	else cout << "Debug: Terminated." << endl;
	exit(0);
      }
      else {
	if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Abort condition failed." << endl;
	else cout << "Debug: Abort condition failed." << endl;
      }
    }
  }
  void abort(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Aborting. Absolute." << endl;
      else cout << "Debug: Aborting. Absolute." << endl;
      flags_display();
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Terminated." <<endl;
      else cout << "Debug: Terminated." << endl;
      exit(0);
    }
  }
  void pause(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      if(!(editor_interface)) cout << "\033[1;34mDebug:\033[0m Paused. Press Enter.";
      else cout << "Debug: Paused. Press Enter." << endl;
      cin.get();
    }
  }
};
