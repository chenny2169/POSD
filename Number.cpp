#include <iostream>
#include "atom.h"
#include "variable.h"
#include "number.h"
#include <string>


std::string Number::symbol(){
    return _symbol;
}

std::string Number::value(){
    return _value;
}

bool Number::match(Number num){
    if (_value == num.value()){
      return true;
    }
    else{
      return false;
    }
}

bool Number::match(Atom &atom){
    if (_value == atom._symbol){
      return true;
    }
    else{
      return false;
    }
}

bool Number::match(Variable &var){
  if(var._count == 0){
    var._value = _value;
    var._count++;
  }
  else if (_symbol == var._value){
    return true;
  }
  else{
    return false;
  }
}
