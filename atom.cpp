#include "atom.h"
#include "variable.h"
Atom :: Atom(string symbol) : _symbol(symbol) {}
string Atom :: symbol() const { return _symbol; }
bool Atom :: match(Term &term) {
    Variable *ps = term.getVariable();
    if(ps)
        return ps->match(*this);
    return _symbol == term.symbol();
}
