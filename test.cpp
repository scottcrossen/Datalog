#include <iostream>
#include "debugger.h"
#include "scanner.h"

int main(){
  Debugger debug=Debugger("Main");
  debug.output("Debugger class seems to be working.");
  debug.flag(1);
  debug.flag(2);
  debug.flags_display();
  if(!(debug.encountered(1))) debug.flag(1);
  debug.flags_clear();
  Scanner scanner=Scanner();
}
