#ifndef TERM_H
#define TERM_H

class Term{
public:
  virtual std::string symbol() const = 0;

  virtual std::string value() {
    return symbol();
  }

  virtual bool match(Term & term);
};


#endif
