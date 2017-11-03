#include "term.h"
#include "variable.h"
#include <iostream>
#include <typeinfo>

bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this);
  else{
    return symbol() == a.symbol();
  }
}
