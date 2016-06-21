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
 public:
  Debugger(bool turned_on){
    this->turned_on=turned_on;
    last_flag=false;
    if(turned_on) cout << "Debug: Initialized" <<endl;
  }
  ~Debugger(){
    if(turned_on) cout << "Debug: Terminated" <<endl;
  }
  void flag(int add_flag){
    if(turned_on){
      flags.push_back(add_flag);
      if(!(last_flag)) cout << "Debug: Flags encountered:\t"<< add_flag;
      else cout << " " << add_flag;
      last_flag=true;
    }
  }
  void flags_display(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      cout << "Debug: Displaying flags found:\t";
      for(unsigned i=0; i < flags.size(); i++)
	cout << flags[i] << " ";
      cout << endl;
    }
  }
  void output(string current_output){
    if(turned_on){
      if(last_flag){cout << endl; last_flag=false;}
      cout << "Debug: Status line:\t\t" << current_output << endl;
    }
  }
  void flags_clear(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      for (unsigned i=0; i < flags.size(); i++) flags.pop_back();
      cout << "Debug: Flags cleared." << endl;
    }
  }
  bool encountered(int current_flag){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      for (unsigned i=0; i < flags.size(); i++)
	if(flags[i]==current_flag){
	  cout << "Debug: Flag 1 conditional met:\tTrue"<< endl;
	  return true;
	}
      cout << "Debug: Flag 1 conditional met:\tFalse"<< endl;
      return false;
    } else return false;
  }
  void abort(bool conditional_met){
    if(turned_on){
      if(conditional_met){
	cout << "Debug: Aborting. Unknown flag." << endl;
	flags_display();
	if(turned_on) cout << "Debug: Terminated" <<endl;
	exit(0);
      }
    }
  }
  void abort(bool conditional_met, int current_flag){
    if(turned_on){
      if(conditional_met){
	cout << "Debug: Aborting with flag:\t" << current_flag << endl;
	flags_display();
	if(turned_on) cout << "Debug: Terminated" <<endl;
	exit(0);
      }
    }
  }
  void abort(){
    if(turned_on){
	cout << "Debug: Aborting. Absolute." << endl;
	flags_display();
	if(turned_on) cout << "Debug: Terminated" <<endl;
	exit(0);
    }
  }
  void pause(){
    if(turned_on){
      cout << "Debug: Paused. Press Enter.";
      cin.get();
    }
  }
};
