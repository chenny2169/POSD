#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "atom.h"
#include <list>
#include <iostream>

template<class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term * currentItem() const {
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template<class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<class T>
class ListIterator :public Iterator<T> {
public:
  friend class List;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};

template<class T>
class DFSIterator : public Iterator<T> {
public:
  friend class Struct;
  friend class List;
  void first() {
    _makeIterator = _t -> createIterator();
    _makeIterator -> first();
    _list.push_back(_makeIterator -> currentItem());
  }

  Term* currentItem() const {
    return _list.front();
  }

  bool isDone() const {
    return _list.size() == 0;
  }

  void next() {
    _list.pop_front();
    if (!_makeIterator -> isDone()){
      _nowIterator = _makeIterator -> currentItem() -> createIterator();
      _nowIterator -> first();
      while(!(_nowIterator -> isDone())){
        _list.push_back(_nowIterator -> currentItem());
        _nowIterator -> next();
      }
      _makeIterator -> next();
      if (!_makeIterator -> isDone()){
        _list.push_back(_makeIterator -> currentItem());
      }
    }
  }

private:
  DFSIterator(T t): _index(0), _t(t) {}
  int _index;
  T _t;
  std::list<Term *> _list;
  Iterator<Term *> * _makeIterator = nullptr;
  Iterator<Term *> * _nowIterator = nullptr;
};

template<class T>
class BFSIterator : public Iterator<T> {
public:
  friend class Struct;
  friend class List;
  void first() {
    _makeIterator = _t -> createIterator();
    while (!(_makeIterator -> isDone())){
      _list.push_back(_makeIterator -> currentItem());
      _makeIterator -> next();
    }
    _makeIterator -> first();
  }

  Term* currentItem() const {
    return _list.front();
  }

  bool isDone() const {
    return _list.size() == 0;
  }

  void next() {
    _nowIterator = _list.front() -> createIterator();
    _nowIterator -> first();
    while(!(_nowIterator -> isDone())){
      _list.push_back(_nowIterator -> currentItem());
      _nowIterator -> next();
    }
    _list.pop_front();
  }
private:
  BFSIterator(T t): _index(0), _t(t) {}
  int _index;
  T _t;
  std::list<Term *> _list;
  Iterator<Term *> * _makeIterator = nullptr;
  Iterator<Term *> * _nowIterator = nullptr;
};

#endif
