#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "atom.h"
#include "number.h"
#include "struct.h"
#include "list.h"

class Variable : public Term{
public:
  Variable(std::string s):_symbol(s), _value(new std::string(s)){}
  std::string const _symbol;
  std::string * _value;
  int _count = 0;
  bool * _bothValuesAreEmpty = new bool(false);
  bool * _matchVarStruct = new bool(false);
  bool * _matchVarList = new bool(false);
  std::vector<Variable*> matchVector = {};
  Struct * s = NULL;
  List * l = NULL;
  std::string symbol() const{
    return _symbol;
  }
  std::string value() const{
    if (*_matchVarStruct)
      return s -> value();
    else if (*_matchVarList)
      return l -> value();
    else
      return *_value;
  }
  bool match (Term & term){
    Variable * pv = dynamic_cast<Variable *>(&term);
    Atom * pa = dynamic_cast<Atom *>(&term);
    Number * pn = dynamic_cast<Number *>(&term);
    Struct * ps = dynamic_cast<Struct *>(&term);
    List * pl = dynamic_cast<List *>(&term);
    // Variable matches variable
    if (pv){
      if (_count == 0 && pv -> _count == 0){
        if (*_bothValuesAreEmpty && !(*(pv -> _bothValuesAreEmpty))){
          pv -> _value = _value;
          *(pv -> _bothValuesAreEmpty) = true;
          pv -> matchVector.push_back(this);
          matchVector.push_back(pv);
        }
        else if (*(pv -> _bothValuesAreEmpty) && !(*_bothValuesAreEmpty)){
          _value = pv -> _value;
          *(_bothValuesAreEmpty) = true;
          matchVector.push_back(pv);
          (pv -> matchVector).push_back(this);
        }
        else if (*_bothValuesAreEmpty && *(pv -> _bothValuesAreEmpty)){
          _value = pv -> _value;
          matchVector[0] -> _value = pv -> matchVector[0] -> _value;
          matchVector.push_back(pv);
          (pv -> matchVector).push_back(this);
        }
        else{
          _value = pv -> _value;
          matchVector.push_back(pv);
          (pv -> matchVector).push_back(this);
          *(_bothValuesAreEmpty) = true;
          *(pv -> _bothValuesAreEmpty) = true;
        }
      }
      else if (_count == 0 && (pv -> _count) > 0){
        *_value = *(pv -> _value) ;
        _count++;
        return true;
      }
      else if (_count > 0 && pv -> _count == 0){
        *(pv -> _value) = *_value;
        pv -> _count++;
        return true;
      }
      else if (_count > 0 && pv -> _count > 0 && (pv -> value() != *_value)) {
        return false;
      }
      else{
        return true;
      }
    }
    //Variable matches atom
    else if (pa){
      if(_count == 0){
        *_value = pa -> symbol();
        _count++;
        return true;
      }
      else if (_count > 0 && (pa -> symbol() != *_value)) {
        return false;
      }
      else{
        return true;
      }
    }
    //Variable matches number
    else if (pn){
      if(_count == 0){
        *_value = pn -> symbol();
        _count++;
        return true;
      }
      else if (_count > 0 && (pn -> symbol() != *_value)) {
        return false;
      }
      else{
        return true;
      }
    }
    //Variale matches structure
    else if (ps){
      if(_count == 0){
        s = ps;
        *_matchVarStruct = true;
        *_value = ps -> value();
        _count++;
        return true;
      }
      else if (_count > 0 && (ps -> value() != *_value)) {
        return false;
      }
      else{
        return true;
      }
    }
    //Variable matches list
    else if (pl){
      if(_count == 0){
        for (int i = 0; i < pl -> getElements().size() - 1; i++){
          if (pl -> getElements()[i] == this && pl -> getElements()[i] -> symbol() == _symbol)
            return false;
        }

        // s = &str;
        // *_matchVarStruct = true;
        l = pl;
        *_matchVarList = true;
        *_value = pl -> value();
        _count++;
        return true;
      }
      else if (_count > 0 && (pl -> value() != *_value)) {
        return false;
      }
      else{
        return true;
      }
    }
  }
};

#endif
