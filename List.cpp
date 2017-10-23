#include <vector>
#include <string>
#include "list.h"
#include "variable.h"
#include "term.h"

bool List::match(Term & term){
  List * pl = dynamic_cast<List *>(&term);
  Variable * pv = dynamic_cast<Variable *>(&term);
  std::vector<Term *> temp = getElements();
  if (pl){
    std::vector<Term *> pl_temp = pl -> getElements();
    if (temp.size() != pl -> getElements().size())
      return false;
    for (int i = 0; i < temp.size(); i++){
      temp[i] -> match(*pl_temp[i]);
    }
    return true;
  }
  else if (pv){
    if(pv -> _count == 0){
      for (int i = 0; i < getElements().size() - 1; i++){
        if (getElements()[i] == pv && getElements()[i] -> symbol() == pv -> _symbol)
          return false;
      }
      pv -> l = this;
      *(pv -> _matchVarList) = true;
      *(pv -> _value) = value();
      pv -> _count++;
      return true;
    }
    else if (pv -> _count > 0 && value() != *(pv -> _value)) {
      return false;
    }
    else{
      return true;
    }
  }
  else{
    return false;
  }
}
