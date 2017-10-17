#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include "term.h"

class Number : public Term{
  public:
    Number(double num):_symbol(std::to_string(num)), _value(std::to_string(num)){}
    std::string symbol() const{
      return _symbol;
    }
    std::string value() {
      int count = 0;
      std::string ret;
      for (int i = 0; i < _value.size(); i++){
        if (_value[i] == '0')
          count++;
        else
          count = 0;
      }
      ret = _value.substr(0, _value.size() - count);
      if (ret[ret.size() - 1] == '.'){
        ret = _value.substr(0, _value.size() - count - 1);
      }
      return ret;
    }
  private:
    std::string _symbol;
    std::string _value;
    double _num;
};

#endif
