#include "number.h"
#include "variable.h"
#include "sstream"
Number :: Number(double i) : _value(i) {
    std :: stringstream ss;
    ss << i;
    _symbol = ss.str();
}
string Number :: symbol() const { return _symbol; }    
string Number :: value() const { return _symbol; }
bool Number :: match(Term &term) {
    Variable *ps = term.getVariable();
    if(ps) {
        return ps->match(*this);
    }
    return _symbol == term.symbol();
}