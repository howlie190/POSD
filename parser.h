#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>
#include <iostream>

using std::stack;

class Parser{
private:
  std :: vector<Term *>termTable;
  bool termExist(int &pos, Term term) {
    pos = -1;
    for(int i = 0; i < termTable.size(); i++) {
      if(term.symbol() == termTable[i]->symbol()) {
        pos = i;
        return true;
      }
    }
    return false;
  }
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      Term *term = new Variable(symtable[_scanner.tokenValue()].first);
      if(termExist(pos, *term))
        term = termTable[pos];
      else
        termTable.push_back(term);
      termTable.push_back(term);
      return term;
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
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
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      if(_currentToken == ';')
        throw string("Unbalanced operator");
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
  }

  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';') {
      termTable.clear();
      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
      createTerm();
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    Term * left = createTerm();
    if(!left)
      throw string("Unexpected ',' before '.'");
    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      _expStack.push(new MatchExp(left, right));
    } else {
      if(_currentToken == ',')
        throw string("Unexpected ',' before '.'");
      if(_currentToken == ';')
        throw string("Unexpected ';' before '.'");
      if(left->symbol() == left->value()) {
        throw string(left->symbol() + " does never get assignment");
      }
    }
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }

private:
  // FRIEND_TEST(ParserTest, createArgs);
  // FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  // FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  // FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  // FRIEND_TEST(ParserTest, createTerms);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }
  stack<string>_err;
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken, pos;
  //MatchExp* _root;
  stack<Exp*> _expStack;
};
#endif
