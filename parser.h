#ifndef PARSER_H
#define PARSER_H
#include <string>

using std::string;

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

// #include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      std::cout << "/* message var*/" << '\n';
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      std::cout << "/* messageA */" << '\n';
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }
    return nullptr;
  }

  Term * structure() {
    _inStruct = true;
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    _isStruct = true;
    createTerms();
    if(_currentToken == ')')
    {
      _inStruct = false;
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _nodeTerms.erase(_nodeTerms.begin() + startIndexOfStructArgs, _nodeTerms.end());
      checkVarInArgs(args);
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    _inList = true;
    int startIndexOfListArgs = _terms.size();
    _isList = true;
    createTerms();
    if(_currentToken == ']')
    {
      _inList = false;
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      _nodeTerms.erase(_nodeTerms.begin() + startIndexOfListArgs, _nodeTerms.end());
      checkVarInArgs(args);
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void getNodes(){
    for (int i = 0; i < _terms.size(); i++){
      std::cout << _terms[i] << '\n';
    }
  }

  void matchings() {
    createTerms();
    int commaCount = 0;
    int commaPosition;
    int semicolonCount = 0;
    int semicolonPosition;
    if (_nodeTerms[_nodeTerms.size() - 1] -> term -> symbol() == "." && _nodeTerms.size() != 1){
      if (_nodeTerms[_nodeTerms.size() - 2] -> term -> symbol() != "."){
        _isDeletePeriod = true;
        _nodeTerms.pop_back();
      }
    }
    for (int i = 0; i < _nodeTreeOperator.size(); i++){
      if (_nodeTreeOperator[i] -> payload == EQUALITY){
        _nodeTreeOperator[i] -> left = _nodeTerms[i];
        _nodeTreeOperator[i] -> right = _nodeTerms[i + 1];
      }
      else if (_nodeTreeOperator[i] -> payload == COMMA){
        commaCount++;
        if (commaCount == 1){
          if (semicolonCount == 0){
            _root = _nodeTreeOperator[i];
          }
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          commaPosition = i;
        }
        else if (commaCount >= 2){
          _nodeTreeOperator[commaPosition] -> right = _nodeTreeOperator[i];
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          commaPosition = i;
        }
      }
      else if (_nodeTreeOperator[i] -> payload == SEMICOLON){
        semicolonCount++;
        if (semicolonCount == 1){
          _root = _nodeTreeOperator[i];
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          semicolonPosition = i;
        }
        else if (semicolonCount >= 2){
          _nodeTreeOperator[semicolonPosition] -> right = _nodeTreeOperator[i];
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          semicolonPosition = i;
        }
      }
    }
    if (commaCount > 0 && _nodeTreeOperator.size() > commaPosition + 1){
      _nodeTreeOperator[commaPosition] -> right = _nodeTreeOperator[commaPosition + 1];
    }
    if (semicolonCount > 0 && _nodeTreeOperator.size() > semicolonPosition + 1){
      if (commaCount == 0){
        _nodeTreeOperator[semicolonPosition] -> right = _nodeTreeOperator[semicolonPosition + 1];
      }
      else{
        _nodeTreeOperator[semicolonPosition] -> right = _nodeTreeOperator[semicolonPosition + 2];
      }
    }
  }

  Node * expressionTree(){
    if (_nodeTreeOperator.size() == 1){
      _root = _nodeTreeOperator[0];
    }
    else if (_nodeTreeOperator.size() == 0){
      _root = _nodeTerms[0];
    }
    return _root;
  }

  Operators getEnums(int op){
    switch (op){
      case ';':
        return SEMICOLON;
        break;
      case ',':
        return COMMA;
        break;
      case '=':
        return EQUALITY;
        break;
      default:
        return TERM;
    }
  }

  void buildExpression(){
    matchings();
    Node * et = expressionTree();
    std::cout << "/* message */"<<  _isDeletePeriod << '\n';
    if ((et -> left != 0 && et -> right != 0) && _isDeletePeriod){
      generateResult(et -> evaluate());
    }
    else{
      if (et -> left == 0 && et -> right == 0)
        throw string(_nodeTerms[0] -> term -> symbol() + " does never get assignment");
      else if (!_isDeletePeriod)
        throw string("Missing token '.'");
      else if (et -> left == 0 || et -> right == 0){
        throw string("Unexpected '" + _root -> convertEnumToString(_root -> payload) + "' before '.'");
      }
    }
  }

  void generateResult(bool evaluate){
    std::cout << "/* message in gen*/" << evaluate << '\n';
    if (!evaluate){
      _result = "false.";
    }
    else{
      std::cout << "/* message in else*/" << '\n';
      string leftOperand = _root -> left -> term -> symbol();
      string rightOperand = _root -> right -> term -> symbol();
      if (leftOperand == rightOperand){
        _result = "true.";
      }
      else{
        _result = leftOperand + " " + _root -> convertEnumToString(_root -> payload) + " " + rightOperand + ".";
      }
    }
  }

  string getResult(){
    return _result;
  }
private:
  // FRIEND_TEST(ParserTest, createArgs);
  // FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  // FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  // FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _nodeTerms.push_back(new Node(getEnums(_currentToken), term, 0, 0));
      _terms.push_back(term);
      if (_isStruct){
        _structPosition.push_back(_terms.size() - 1);
        _isStruct = false;
      }
      if (_isList){
        _listPosition.push_back(_terms.size() - 1);
        _isList = false;
      }
      if (isExist(term, _terms)){
        _nodeTerms[_nodeTerms.size() - 1] = _nodeTerms[_existSymbolPosition];
        _terms[_terms.size() - 1] = _terms[_existSymbolPosition];
      }
      while((_currentToken = _scanner.nextToken()) == ',' || _currentToken == '=' || _currentToken == ';') {
        _nodeTreeOperator.push_back(new Node(getEnums(_currentToken)));
        Term * _termInWhile = createTerm();
        _nodeTerms.push_back(new Node(getEnums(_currentToken), _termInWhile, 0, 0));
        _terms.push_back(_termInWhile);
        if (_nodeTreeOperator[_nodeTreeOperator.size() - 1] -> payload != SEMICOLON){
          if (isExist(_termInWhile, _terms)){
            _nodeTerms[_nodeTerms.size() - 1] = _nodeTerms[_existSymbolPosition];
            _terms[_terms.size() - 1] = _terms[_existSymbolPosition];
          }
        }
        if (_scanner.currentChar() == '.'){
          _isDeletePeriod = true;
        }
      }
    }
  }

  bool isExist(Term * term, vector<Term*> terms){
    for (int i = terms.size() - 2; i >= 0; i--){
      if (_currentToken == VAR && (terms[i] -> symbol() == term -> symbol())){
          _existSymbolPosition = i;
          return true;
      }
      else if (_currentToken == VAR && _structPosition.size() != 0 && !_inStruct){
        for (int j = 0; j < _structPosition.size(); j++){
          for (int k = 0; k < dynamic_cast<Struct *>(terms[_structPosition[j]]) -> _args.size(); k++){
            if (term -> symbol() == dynamic_cast<Struct *>(terms[_structPosition[j]]) -> _args[k] -> symbol()){
              dynamic_cast<Struct *>(terms[_structPosition[j]]) -> _args[k] = term;
            }
          }
        }
      }
      else if (_currentToken == VAR && _listPosition.size() != 0 && !_inList){
        for (int j = 0; j < _listPosition.size(); j++){
          for (int k = 0; k < dynamic_cast<List *>(terms[_listPosition[j]]) -> getElements().size(); k++){
            if (term -> symbol() == dynamic_cast<List *>(terms[_listPosition[j]]) -> getElements()[k] -> symbol()){
              dynamic_cast<List *>(terms[_listPosition[j]]) -> getElements()[k] = term;
            }
          }
        }
      }
    }
    return false;
  }

  void checkVarInArgs(vector<Term *> args){
    for (int i = 0; i < _terms.size(); i++){
      for (int j = 0; j < args.size(); j++){
        if ((args[j] -> symbol()) == (_terms[i] -> symbol())){
          args[j] = _terms[i];
        }
      }
    }
  }

  Node * _root = nullptr;
  vector<Term *> _terms;
  vector<Node *> _nodeTerms;
  vector<Node *> _nodeTreeOperator;
  Scanner _scanner;
  int _currentToken;
  int _existSymbolPosition;
  bool _inStruct = false;
  bool _isStruct = false;
  bool _inList = false;
  bool _isList = false;
  vector<int> _structPosition;
  vector<int> _listPosition;
  bool _isDeletePeriod = false;
  string _result;
};
#endif
