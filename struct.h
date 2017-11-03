#ifndef struct_h
#define struct_h

#include "term.h"
#include <vector>
class Struct : public Term {
private:
    std :: vector<Term *>_args;
    Atom _name;
public:
    Struct(Atom name, std :: vector<Term *>args) : _name(name), _args(args) {}
    Struct(Atom name) : _name(name), _args() {}
    Term & args(int index) { return *_args[index]; }
    Atom & name() { return _name; }
    string symbol() const {
        if(_args.empty())
            return _name.symbol() + "()";
        string _result = _name.symbol() + "(";
        for(int i = 0; i < _args.size() - 1; i++)
            _result += (_args[i]->symbol() + ", ");
        return _result += (_args[_args.size() - 1]->symbol() + ")");
    }
    string value() const {
        if(_args.empty())
            return _name.symbol() + "()";
        string _result = _name.symbol() + "(";
        for(int i = 0; i < _args.size() - 1; i++)
            _result += (_args[i]->value() + ", ");
        return _result += (_args[_args.size() - 1]->value() + ")");
    }
    int arity() { return _args.size(); }
    Struct * getStruct() { return this; }
};
#endif