#ifndef term_h
#define term_h
#include <string>
using std :: string;
class Variable;
class Struct;
class Term {
public:
    virtual string symbol() const = 0;
    virtual string value() const { return symbol(); }
    virtual bool match(Term &term) { return symbol() == term.symbol(); }
    virtual Variable * getVariable() { return 0; }
    virtual Struct * getStruct() { return 0; }
};
#endif