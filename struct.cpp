#include "struct.h"
#include "variable.h"
string Struct :: symbol() const {
    string ret = _name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1; i++)
        ret += (_args[i]->symbol() + ", ");
    return ret += (_args[_args.size() - 1]->symbol() + ")");
}
string Struct :: value() const {
    string ret = _name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1; i++)
        ret += (_args[i]->value() + ", ");
    return ret += (_args[_args.size() - 1]->value() + ")");
}
bool Struct :: match(Term &term) {
    Struct *ps = dynamic_cast<Struct *>(&term);
    Variable *pt = dynamic_cast<Variable *>(&term);
    if(ps) {
        if(!_name.match(ps->_name))
            return false;
        if(_args.size() != ps->_args.size())
            return false;
        for(int i = 0; i < _args.size(); i++) 
            if(_args[i]->symbol() != ps->_args[i]->symbol())
                return false;
        return true;
    }
    if(pt)
        return pt->match(*this);
    return false;
}
atom Struct :: name() { return _name; }
Term * Struct :: args(int index) { return _args[index]; }