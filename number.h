#ifndef number_h
#define number_h
#include "term.h"
class Number : public Term {
private:
    string _symbol;
    double _value;
public:
    Number(double);
    string symbol() const;
    string value() const;
    bool match(Term &term);
};
#endif