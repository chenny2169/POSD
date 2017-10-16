#include <iostream>
#include <string>
#include "term.h"
#include "variable.h"

bool Term::match(Term & term){
  Variable * pv = dynamic_cast<Variable *>(&term);
  if (pv){
    if (pv -> _count == 0){
      *(pv -> _value) = value();
      pv -> _count++;
      return true;
    }
    else if (value() == *(pv -> _value)){
      return true;
    }
    else{
      return false;
    }
  }
  else
    return value() == term.value();
}
