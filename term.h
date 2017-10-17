#ifndef term_h
#define term_h
#include <string>
using std :: string;
class Term {
public:
    virtual string symbol() const = 0;
    virtual string value() const { return symbol(); }
    virtual bool match(Term &term) { return symbol() == term.symbol(); }
};
#endif