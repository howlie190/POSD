#ifndef atom_h
#define atom_h
#include "term.h"
class Atom : public Term {
public:
    Atom(string symbol) : Term(symbol) {}
};
#endif