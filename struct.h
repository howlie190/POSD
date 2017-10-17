#ifndef struct_h
#define struct_h
#include "term.h"
#include "atom.h"
#include <vector>
using std :: vector;
class Struct : public Term {
private:
    atom _name;
    vector<Term *>_args;
public:
    Struct(atom name, std :: vector<Term *> args) : _name(name), _args(args) {}
    string symbol() const;
    string value() const;
    bool match(Term &term);
    atom name();
    Term * args(int);
};
#endif