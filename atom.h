#ifndef atom_h
#define atom_h
#include "term.h"
class atom : public Term {
private:
    const string _symbol;
public:
    atom(string);
    string symbol() const;
    bool match(Term &term);
};
#endif