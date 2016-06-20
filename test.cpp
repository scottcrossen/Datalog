#include <iostream>
#include "debugger.h"
using namespace std;
int main(){
  Debugger debug=Debugger(true);
  debug.output("Flag 1 Reached");
  debug.flag(1);
  debug.flags_display();
}
