#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "atom.h"
#include "number.h"
#include "struct.h"

class Variable : public Term{
public:
  Variable(std::string s):_symbol(s), _value(new std::string(s)){}
  std::string const _symbol;
  std::string * _value;
  int _count = 0;
  bool * _bothValuesAreEmpty = new bool(false);
  bool * _matchVarStruct = new bool(false);
  std::vector<Variable*> matchVector = {};
  std::string symbol() const{
    return _symbol;
  }
  std::string value() {
    return *_value;
  }
  bool match (Variable & var){
    if (_count == 0 && var._count == 0){
      if (*_bothValuesAreEmpty && !(*(var._bothValuesAreEmpty))){
        var._value = _value;
        *(var._bothValuesAreEmpty) = true;
        var.matchVector.push_back(this);
        matchVector.push_back(&var);
      }
      else if (*(var._bothValuesAreEmpty) && !(*_bothValuesAreEmpty)){
        _value = var._value;
        *(_bothValuesAreEmpty) = true;
        matchVector.push_back(&var);
        var.matchVector.push_back(this);
      }
      else if (*_bothValuesAreEmpty && *(var._bothValuesAreEmpty)){
        _value = var._value;
        matchVector[0] -> _value = var.matchVector[0] -> _value;
        std::cout << "var.matchVector:" << var.value() << '\n';
        matchVector.push_back(&var);
        var.matchVector.push_back(this);
      }
      else{
        _value = var._value;
        matchVector.push_back(&var);
        var.matchVector.push_back(this);
        *(_bothValuesAreEmpty) = true;
        *(var._bothValuesAreEmpty) = true;
      }
    }
    else if (_count == 0 && var._count > 0){
      *_value = *(var._value) ;
      _count++;
      return true;
    }
    else if (_count > 0 && var._count == 0){
      *(var._value) = *_value;
      var._count++;
      return true;
    }
    else if (_count > 0 && var._count > 0 && (var.value() != *_value)) {
      return false;
    }
    else{
      return true;
    }
  }
  bool match( Atom & atom ){
    if(_count == 0){
      *_value = atom.symbol();
      _count++;
      return true;
    }
    else if (_count > 0 && (atom.symbol() != *_value)) {
      return false;
    }
    else{
      return true;
    }
  }

  bool match( Number & num ){
    if(_count == 0){
      *_value = num.value();
       _count++;
    }
    else if (_count > 0 && (num.value() != *_value)) {
      return false;
    }
    else{
      return true;
    }
  }
  bool match(Struct & str){
    if(_count == 0){
      std::string strValue = str.value();
      // *_matchVarStruct = true;
      // *(str._matchVarStruct) = true;
      _value = str._value;
      _count++;
      return true;
    }
    else if (_count > 0 && (str.value() != *_value)) {
      return false;
    }
    else{
      return true;
    }
  }
};

#endif
