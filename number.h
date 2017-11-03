#ifndef number_h
#define number_h
#include "term.h"
class Number : public Term {
public:
    Number(double value) : Term(value) {}
};
#endif