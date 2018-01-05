#include <iostream>
#include <string>

#include "scanner.h"
#include "parser.h"

int main(){
  std::string input;
  std::cout << "?- ";
  while (input != "halt."){
    std::getline(std::cin, input, '\n');

    Scanner s(input);
    Parser p(s);
    try {
      p.buildExpression();
      string result = p.getResult();
      std::cout << result << '\n';
    } catch (std::string &msg) {
        std::cout << msg << '\n';
    }
    if (input == ""){
      std::cout << "?- ";
    }
    else if (input != "halt."){
      std::cout << "|   " << '\n';
    }
  }
}
