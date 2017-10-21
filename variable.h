#ifndef variable_h
#define variable_h
#include "term.h"
#include "struct.h"
#include "list.h"
#include <vector>
using std :: vector;
class Variable : public Term {
private:
    const string _symbol;
    string _value;
    bool _assignable = true;
    vector<Variable *>_v;
    Struct *_struct;
    List * _list;
    bool _structMatch = false;
    bool _listMatch = false;
public:
    Variable(string);
    string symbol() const;
    string value() const;
    bool match(Term &term);
    void copy(Variable *);
    void chain();
    void memberCopy(Variable *);
    Variable * getVariable();
    bool checkList(List *);
};
#endif