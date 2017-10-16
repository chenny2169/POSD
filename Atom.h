#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"


class Atom : public Term{
public:
  Atom (std::string s):_symbol(s) {}
  std::string _symbol;
  std::string symbol() const{
    return _symbol;
  }
};


#endif
