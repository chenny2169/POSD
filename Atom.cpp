#include <iostream>
#include "atom.h"
#include "number.h"
#include "variable.h"

bool Atom::match(Atom a){
  if (_symbol == a._symbol){
    return true;
  }
  else{
    return false;
  }
}

bool Atom::match(Number &num){
  if (_symbol == num.value()){
    return true;
  }
  else{
    return false;
  }
}

bool Atom::match(Variable &var){
  if(var._count == 0){
    var._value = _symbol;
    var._count++;
    return true;
  }
  else if (_symbol == var._value){
    return true;
  }
  else{
    return false;
  }
}
