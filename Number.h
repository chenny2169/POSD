#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include "term.h"

class Number : public Term{
  public:
    Number(double num):_symbol(std::to_string(num)), _value(std::to_string(num)){}
    std::string symbol() const{
      int count = 0;
      std::string ret;
      for (int i = 0; i < _symbol.size(); i++){
        if (_symbol[i] == '0')
          count++;
        else
          count = 0;
      }
      ret = _symbol.substr(0, _symbol.size() - count);
      if (ret[ret.size() - 1] == '.'){
        ret = _symbol.substr(0, _symbol.size() - count - 1);
      }
      return ret;
    }
    std::string value() const{
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
