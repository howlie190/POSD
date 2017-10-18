#ifndef atom_h
#define atom_h
#include "term.h"
class Atom : public Term {
private:
    const string _symbol;
public:
    Atom(string);
    string symbol() const;
    bool match(Term &term);
};
#endif