#ifndef term_h
#define term_h

#include <string>
#include <sstream>
#include <typeinfo>

using std :: string;
class List;
class Term {
protected:
    string _symbol;
    Term() : _symbol("") {}
    Term(string symbol) : _symbol(symbol) {}
    Term(double value) {
        std :: stringstream ss;
        ss << value;
        _symbol = ss.str();
    }
public:
    virtual string symbol() const { return _symbol; }
    virtual string value() const { return symbol(); }
    virtual bool match(Term &term);
    virtual List * getList() { return 0; }
};
class Atom : public Term {
public:
    Atom(string symbol) : Term(symbol) {}
};
class Number : public Term {
public:
    Number(double value) : Term(value) {}
};
#endif