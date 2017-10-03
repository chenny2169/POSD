#ifndef NUMBER_H
#define NUMBER_H
#include <string>

class Atom;
class Variable;
class Number{
  public:
    Number(int num):_symbol(std::to_string(num)), _value(std::to_string(num)){}
    std::string symbol();
    std::string value();
    bool match(Number num);
    bool match(Atom &atom);
    bool match(Variable &var);
  private:
    std::string _symbol;
    std::string _value;
};

#endif
