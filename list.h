#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
using std::vector;

class Variable ;
template<class T>
class Iterator;
class List : public Term {
public:
  string symbol() const ;
  string value() const ;
  bool match(Term & term) ;
  List * getList() { return this; }
public:
  List (): _elements(0) {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const;
  List * tail() const;
  Iterator<Term *> * createIterator();
  Iterator<Term *> * createDFSIterator();
  Iterator<Term *> * createBFSIterator();
  Term * args(int index) { return _elements[index]; }
  int arity() const { return _elements.size(); }
private:
  vector<Term *> _elements;
};

#endif
