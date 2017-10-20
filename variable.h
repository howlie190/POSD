#ifndef variable_h
#define variable_h
#include "term.h"
#include <vector>
#include "struct.h"
using std :: vector;
class Variable : public Term {
private:
    const string _symbol;
    string _value;
    bool _assignable = true;
    vector<Variable *>_v;
    Struct *_struct;
    bool _structMatch = false;
public:
    Variable(string);
    string symbol() const;
    string value() const;
    bool match(Term &term);
    void copy(Variable *);
    void chain();
    void memberCopy(Variable *);
    Variable * getVariable();
};
#endif