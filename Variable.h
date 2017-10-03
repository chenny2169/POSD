#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class Atom;
class Number;
class Variable{
public:
  Variable(std::string s):_symbol(s){}
  std::string const _symbol;
  std::string _value;
  int _count = 0;
  bool match( Atom &atom );
  bool match( Number &num );
};

#endif
