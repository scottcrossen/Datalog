#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Debugger{
 private:
  vector<int> flags;
 public:
  int on;
  Debugger(on){
    this->on=on;
    if(on) cout << "Debugger object created" <<endl;
  }
  ~Debugger(){
    if(on) cout << "Debugger object deleted" <<endl;
  }
  flag(int flag){
    flags.push_back(flag);
  }
  flags_display(){
    if(on){
      cout << "flags encountered: ";
      for(int i=0; i < flags.length(); i++)
	cout << flags[i] << " ";
      cout << endl;
    }
  }
  output(string output){
    if(on) cout << "status line: " output << endl;
  }
  flags_clear(){
    for (int i=0; i < flags.length(); i++) flags.pop();
  }
}
