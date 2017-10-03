#include <iostream>
#include "variable.h"
#include "number.h"
#include "atom.h"

bool Variable::match( Atom &atom ){
  if(_count == 0){
    _value = atom._symbol ;
    _count++;
    return true;
  }
  else if (_count > 0 && (atom._symbol != _value)) {
    return false;
  }
  else{
    return true;
  }
}

bool Variable::match( Number &num ){
  if(_count == 0){
    _value = num.value();
    _count++;
    return true;
  }
  else if (_count > 0 && (num.value() != _value)) {
    return false;
  }
  else{
    return true;
  }
}
