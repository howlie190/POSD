#ifndef number_h
#define number_h
#include "term.h"
class number : public Term {
private:
    const string _symbol;
    const double _value;
public:
    number(double);
    string symbol() const;
    string value() const;
    bool match(Term &term);
};
#endif