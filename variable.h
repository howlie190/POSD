#ifndef variable_h
#define variable_h

#include "term.h"

class Variable : public Term {
private:
    Term *_ptr;
public:
    Variable(string symbol) : Term(symbol), _ptr(0) {}
    string value() const {
        if(_ptr)
            return _ptr->value();
        return Term :: value();
    }
    bool match(Term &term) {
        if(this == &term)
            return true;
        if(!_ptr) {
            _ptr = &term;
            return true;
        }
        return _ptr->match(term);
    }
};
#endif