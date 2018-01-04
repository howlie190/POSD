#ifndef EXP_H
#define EXP_H

#include "atom.h"

class Exp {
public:
  virtual char getOperator() = 0;
  virtual bool evaluate() = 0;
  virtual Exp * getLeftExp() { return nullptr; }
  virtual Exp * getRightExp() { return nullptr; }
  virtual Term * getLeftTerm() { return nullptr; }
  virtual Term * getRightTerm() { return nullptr; }
  virtual string getStr() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }
  char getOperator() { return '='; }
  bool evaluate(){
    return _left->match(*_right);
  }
  Term * getLeftTerm() { return _left; }
  Term * getRightTerm() { return _right; }
  string getStr() {
    return _left->symbol() + " = " + _right->value();
  }
private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }
  char getOperator() { return ','; }
  Exp * getLeftExp() { return _left; }
  Exp * getRightExp() { return _right; }
  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }
  string getStr() {
    return _left->getStr() + ", " + _right->getStr();
  }
private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }
  Exp * getLeftExp() { return _left; }
  Exp * getRightExp() { return _right; }
  char getOperator() { return ';'; }
  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }
  string getStr() {
    return _left->getStr() + "; " + _right->getStr();
  }
private:
  Exp * _left;
  Exp * _right;
};
#endif
