#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;
#include <iostream>
#include <vector>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "utParser.h"
class Parser{
private:
  std :: vector<Node *>nodeArray, postfix;
  std :: vector<Term *>termTable;
  bool semicolon = false;
  int priority(Operators op) {
    switch(op) {
      case EQUALITY:
        return 2;
      case COMMA:
        return 1;
      case SEMICOLON:
        return 1;
      default:
        return 0;
    }
  }
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
  void infisToPostfix() {
    std :: vector<Node *>stack;
    for(int i = 0; i < nodeArray.size(); i++) {
      if(priority(nodeArray[i]->payload) == 0) {
        postfix.push_back(nodeArray[i]);
      } else if(stack.empty() && priority(nodeArray[i]->payload) != 0) {
        stack.push_back(nodeArray[i]);
      } else if(priority(nodeArray[i]->payload) < priority(stack.back()->payload)) {
        postfix.push_back(stack.back());
        stack.pop_back();
        stack.push_back(nodeArray[i]);
      } else if(priority(nodeArray[i]->payload) > priority(stack.back()->payload)) {
        stack.push_back(nodeArray[i]);
      }
    }
    while(!stack.empty()) {
      postfix.push_back(stack.back());
      stack.pop_back();
    }
  }
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}
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
      } else
        return atom;
    } else if(token == '['){
      return list();
    } else if(token == '=') {
      nodeArray.push_back(new Node(EQUALITY));
    } else if(token == ',') {
      nodeArray.push_back(new Node(COMMA));
    } else if(token == ';') {
      termTable.clear();
      nodeArray.push_back(new Node(SEMICOLON));
    }
    return nullptr;
  }
  void matchings() {
    Term *term;
    while(_scanner.currentChar() != EOS) {
      if(_scanner.currentChar() == '.')
        break;
      if(term = createTerm()) {
        _terms.push_back(term);
        nodeArray.push_back(new Node(TERM, term, 0, 0));
      }
    }
    infisToPostfix();
  }
  Node * expressionTree() {
    std :: vector<Node *>stack;
    for(int i = 0; i < postfix.size(); i++) {
      if(priority(postfix[i]->payload) == 0) {
        stack.push_back(postfix[i]);
      } else {
        postfix[i]->right = stack.back();
        stack.pop_back();
        postfix[i]->left = stack.back();
        stack.pop_back();
        stack.push_back(postfix[i]);
      }
    }
    return stack[0];
  }
  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')'){
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else
      throw string("unexpected token");
  }
  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']'){
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else
      throw string("unexpected token");
  }
  vector<Term *> & getTerms() { return _terms; }
private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr){
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',')
        _terms.push_back(createTerm());
    }
  }
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken, pos;
};
#endif
