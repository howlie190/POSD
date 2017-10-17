#include "atom.h"
#include "variable.h"
atom :: atom(string symbol) : _symbol(symbol) {}
string atom :: symbol() const { return _symbol; }
bool atom :: match(Term &term) {
    Variable *ps = dynamic_cast<Variable *>(&term);
    if(ps)
        return ps->match(*this);
    return _symbol == term.symbol();
}
