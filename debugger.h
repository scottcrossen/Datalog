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
    if(turned_on) cout << "\033[1;34mDebug:\033[0m Initialized" <<endl;
  }
  ~Debugger(){
    if(turned_on) cout << "\033[1;34mDebug:\033[0m Terminated" <<endl;
  }
  void flag(int add_flag){
    if(turned_on){
      flags.push_back(add_flag);
      if(!(last_flag)) cout << "\033[1;34mDebug:\033[0m Flags encountered:\t"<< add_flag;
      else cout << " " << add_flag;
      last_flag=true;
    }
  }
  void flags_display(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      cout << "\033[1;34mDebug:\033[0m Displaying flags found:\t";
      for(unsigned i=0; i < flags.size(); i++)
	cout << flags[i] << " ";
      cout << endl;
    }
  }
  void output(string current_output){
    if(turned_on){
      if(last_flag){cout << endl; last_flag=false;}
      cout << "\033[1;34mDebug:\033[0m Status line:\t\t" << current_output << endl;
    }
  }
  void flags_clear(){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      for (unsigned i=0; i < flags.size(); i++) flags.pop_back();
      cout << "\033[1;34mDebug:\033[0m Flags cleared." << endl;
    }
  }
  bool encountered(int current_flag){
    if(turned_on){
      if(last_flag){ cout << endl; last_flag=false;}
      for (unsigned i=0; i < flags.size(); i++)
	if(flags[i]==current_flag){
	  cout << "\033[1;34mDebug:\033[0m Flag 1 conditional met:\tTrue"<< endl;
	  return true;
	}
      cout << "\033[1;34mDebug:\033[0m Flag 1 conditional met:\tFalse"<< endl;
      return false;
    } else return false;
  }
  void abort(bool conditional_met){
    if(turned_on){
      if(conditional_met){
	cout << "\033[1;34mDebug:\033[0m Aborting. Unknown flag." << endl;
	flags_display();
	if(turned_on) cout << "\033[1;34mDebug:\033[0m Terminated" <<endl;
	exit(0);
      }
    }
  }
  void abort(bool conditional_met, int current_flag){
    if(turned_on){
      if(conditional_met){
	cout << "\033[1;34mDebug:\033[0m Aborting with flag:\t" << current_flag << endl;
	flags_display();
	if(turned_on) cout << "\033[1;34mDebug:\033[0m Terminated" <<endl;
	exit(0);
      }
    }
  }
  void abort(){
    if(turned_on){
	cout << "\033[1;34mDebug:\033[0m Aborting. Absolute." << endl;
	flags_display();
	if(turned_on) cout << "\033[1;34mDebug:\033[0m Terminated" <<endl;
	exit(0);
    }
  }
  void pause(){
    if(turned_on){
      cout << "\033[1;34mDebug:\033[0m Paused. Press Enter.";
      cin.get();
    }
  }
};
