#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  List():_elements(){}
  List (vector<Term *> const & elements):_elements(elements){}
  std::string symbol() const{
    std::string ret = "[";
    if (_elements.size() == 0)
      ret += "]";
    else {
      for(int i = 0; i < _elements.size() - 1 ; i++){
        ret += _elements[i] -> symbol() + ", ";
      }
      ret += _elements[_elements.size()-1] -> symbol() + "]";
    }
    return ret;
  }
  std::string value() const{
    std::string ret = "[";
    if (_elements.size() == 0)
      ret += "]";
    else {
      for(int i = 0; i < _elements.size() - 1; i++){
        if (_elements[i] -> value() == "")
          ret += _elements[i] -> symbol() + ", ";
        else
          ret += _elements[i] -> value() + ", ";
      }
      if (_elements[_elements.size()-1] -> value() == "")
        ret += _elements[_elements.size()-1] -> symbol() + "]";
      else
        ret += _elements[_elements.size()-1] -> value() + "]";
      return ret;
    }
  }
  bool match(Term & term){
    List * pl = dynamic_cast<List *>(&term);
    if (pl){
      if (_elements.size() != pl -> _elements.size())
        return false;
      for (int i = 0; i < _elements.size(); i++){
        _elements[i] -> match(*(pl -> _elements[i]));
      }
      return true;
    }
    else
      return false;
  }

  Term * head() const{
      Term * ret = NULL;
      if (_elements.size() <= 0)
        throw std::string("Accessing head in an empty list");
      else{
        ret = _elements[0];
        return ret;
      }
  }

  List * tail() const{

      std::vector<Term *> temp = {};
      temp = _elements;
      if (temp.size() == 0)
        throw std::string("Accessing tail in an empty list");
      else{
        temp.erase(temp.begin());
        return new List(temp);
      }
  }

  vector<Term *> getElements(){
    return _elements;
  }

private:
  vector<Term *> _elements;
};

#endif
