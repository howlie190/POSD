#ifndef variable_h
#define variable_h
#include "term.h"
#include <vector>
#include "struct.h"
using std :: vector;
class variavle : public Term {
private:
    const string _symbol;
    string _value;
    bool _assignable = true;
    vector<variavle *>_v;
    Struct *_struct;
    bool _structMatch = false;
public:
    variavle(string);
    string symbol() const;
    string value() const;
    bool match(Term &term);
    void copy(variavle *);
    void chain();
    void memberCopy(variavle *);
};
#endif