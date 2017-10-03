#ifndef ATOM_H
#define ATOM_H

#include <string>

class Number;
class Variable;
class Atom {
public:
  Atom (std::string s):_symbol(s) {}
  std::string _symbol;
  bool match(Atom a);
  bool match(Number &num);
  bool match(Variable &var);
};

#endif
