#include <iostream>
#include "debugger.h"
#include "scanner.h"

int main(){
  Debugger debug=Debugger("Main");
  debug.flag(1);
  Scanner scanner=Scanner();
  scanner.initialize();
  RegExp newexp=RegExp("ABC*D");
  debug.output("checking condition 1");
  cout << newexp.check("A") << endl;
  debug.output("checking condition 2");
  cout << newexp.check("AB") << endl;
  debug.output("checking condition 3");
  cout << newexp.check("ABC") << endl;
  debug.output("checking condition 4");
  cout << newexp.check("ABCD") << endl;
  debug.output("checking condition 5");
  cout << newexp.check("ABCDE") << endl;
  debug.output("checking condition 6");
  cout << newexp.check("BC") << endl;
  debug.output("End of main reached.");
  return 0;
}
