#include "number.h"
#include "variable.h"
#include "sstream"
Number :: Number(double i) : _symbol(std :: to_string(i)), _value(i) {}
string Number :: symbol() const { return _symbol; }
string Number :: value() const {
    std :: stringstream ss;
    ss << _value;
    return ss.str();
}
bool Number :: match(Term &term) {
    Variable *ps = term.getVariable();
    if(ps) {
        return ps->match(*this);
    }
    return _symbol == term.symbol();
}