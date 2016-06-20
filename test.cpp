#include <iostream>
#include "debugger.h"
using namespace std;
int main(){
  Debugger debug=Debugger(true);
  debug.flags_on=true;
  debug.output("Debugger class seems to be working.");
  debug.flag(1);
  debug.flags_display();
  if(!(debug.encountered(1))) debug.flag(1);
  debug.flags_clear();
}
