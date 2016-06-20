#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Debugger{
 private:
  vector<int> flags;
 public:
  bool turned_on;
  Debugger(bool turned_on){
    this->turned_on=turned_on;
    if(turned_on) cout << "Debug: initialized" <<endl;
  }
  ~Debugger(){
    if(turned_on) cout << "Debug: terminated" <<endl;
  }
  void flag(int add_flag){
    flags.push_back(add_flag);
  }
  void flags_display(){
    if(turned_on){
      cout << "Debug: flags encountered:\t";
      for(unsigned i=0; i < flags.size(); i++)
	cout << flags[i] << " ";
      cout << endl;
    }
  }
  void output(string current_output){
    if(turned_on) cout << "Debug: status line:\t\t" << current_output << endl;
  }
  void flags_clear(){
    for (unsigned i=0; i < flags.size(); i++) flags.pop_back();
  }
  bool encountered(int current_flag){
    for (unsigned i=0; i < flags.size(); i++)
      if (flags[i]==current_flag) return true;
    return false;
  }
};
