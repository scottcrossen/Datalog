#include <iostream>
#include "debugger.h"

int main(){
  Debugger debug=Debugger(true, true);
  debug.output("Debugger class seems to be working.");
  debug.flag(1);
  debug.flag(2);
  debug.flags_display();
  if(!(debug.encountered(1))) debug.flag(1);
  debug.flags_clear();
  debug.abort();
}
