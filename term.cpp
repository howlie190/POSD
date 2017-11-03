#include "term.h"
#include "variable.h"

bool Term :: match(Term &term) {
    if(typeid(term) == typeid(Variable))
        return term.match(*this);
    return symbol() == term.symbol();
}