#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Debugger{
 private:
  vector<int> flags;
 public:
  bool turned_on;
  bool flags_on;
  Debugger(bool turned_on){
    this->turned_on=turned_on;
    flags_on=false;
    if(turned_on) cout << "Debug: Initialized" <<endl;
  }
  ~Debugger(){
    if(turned_on) cout << "Debug: Terminated" <<endl;
  }
  void flag(int add_flag){
    flags.push_back(add_flag);
    if(turned_on && flags_on) cout << "Debug: Flag "<< add_flag << " reached" <<endl;
  }
  void flags_display(){
    if(turned_on){
      cout << "Debug: Flags encountered:\t";
      for(unsigned i=0; i < flags.size(); i++)
	cout << flags[i] << " ";
      cout << endl;
    }
  }
  void output(string current_output){
    if(turned_on) cout << "Debug: Status line:\t\t" << current_output << endl;
  }
  void flags_clear(){
    for (unsigned i=0; i < flags.size(); i++) flags.pop_back();
    if(turned_on) cout << "Debug: Flags cleared." << endl;
  }
  bool encountered(int current_flag){
    for (unsigned i=0; i < flags.size(); i++)
      if(flags[i]==current_flag){
	if(turned_on) cout << "Debug: Flag 1 conditional met:\tTrue"<< endl;
	return true;
      }
    if(turned_on) cout << "Debug: Flag 1 conditional met:\tFalse"<< endl;
    return false;
  }
};
