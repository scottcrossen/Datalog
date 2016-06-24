#include <iostream>
#include "debugger.h"
#include "scanner.h"

int main(){
  Debugger debug=Debugger("Main");
  debug.flag(1);
  /*
  RegExp newexp=RegExp("AAA*");
  debug.flags_clear();
  debug.output("checking condition 1");
  debug.flag(newexp.check("A"));
  debug.output("checking condition 2");
  debug.flag(newexp.check("AA"));
  debug.output("checking condition 3");
  debug.flag(newexp.check("AAA"));
  debug.output("checking condition 4");
  debug.flag(newexp.check("AAAA"));
  debug.output("checking condition 5");
  debug.flag(newexp.check("AAAB"));
  debug.output("checking condition 6");
  debug.flag(newexp.check("AABB"));
  debug.flags_display();
  debug.flags_clear();*/
  

  Scanner scanner=Scanner();
  scanner.initialize();
  scanner.read_in();
  debug.output("End of main reached.");
  return 0;
}
