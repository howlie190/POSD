#include "number.h"
#include "variable.h"
#include "sstream"
number :: number(double i) : _symbol(std :: to_string(i)), _value(i) {}
string number :: symbol() const { return _symbol; }
string number :: value() const {
    std :: stringstream ss;
    ss << _value;
    return ss.str();
}
bool number :: match(Term &term) {
    Variable *ps = dynamic_cast<Variable *>(&term);
    if(ps) {
        return ps->match(*this);
    }
    return _symbol == term.symbol();
}