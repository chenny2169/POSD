#ifndef NUMBER_H
#define NUMBER_H
#include <string>

class Atom;
class Variable;
class Number{
  public:
    Number(std::string num):_symbol(num), _value(num){}
    std::string symbol();
    std::string value();
    bool match(Number num);
    bool match(Atom* atom);
    bool match(Variable* var);
  private:
    std::string _symbol;
    std::string _value;
};

#endif
