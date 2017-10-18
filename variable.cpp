#include "variable.h"
Variable :: Variable(string symbol) : _symbol(symbol), _value(symbol) {}
string Variable :: symbol() const { return _symbol; }
string Variable :: value() const {
    if(_structMatch) {
        return _struct->value();
    }
    return _value;
}
bool Variable :: match(Term &term) {
    Variable *ps = dynamic_cast<Variable *>(&term);
    Struct *pt = dynamic_cast<Struct *>(&term);
    if(ps) {
        if(_assignable && ps->_assignable) {
            _value = ps->symbol();
            ps->_value = _symbol;
            copy(ps);
            memberCopy(ps);
            _v.push_back(ps);
            ps->_v.push_back(this);
            return true;
        }
        else if(ps->_assignable) {
            copy(ps);
            memberCopy(ps);
            _v.push_back(ps);
            ps->_v.push_back(this);
            chain();
            return true;
        }
        else if(_assignable) {
            return ps->match(*this);
        }
        return false;
    }
    if(pt) {
        if(!_structMatch || _value == pt->value()) {
            _struct = pt;
            _structMatch = true;
            return true;
        }
        return false;
    }
    bool ret = _assignable;
    if(_assignable || _value == term.value()) {
        _value = term.value();
        _assignable = false;
        chain();
        ret = true;
    }
    return ret;
}
void Variable :: copy(Variable *ps) {
    if(_v.size() != 0 || ps->_v.size() != 0) {
        vector<Variable *>temp = _v;
        for(int i = 0; i < ps->_v.size(); i++)
            _v.push_back(ps->_v[i]);
        for(int i = 0; i < temp.size(); i++) {
            ps->_v.push_back(_v[i]);
        }
    }
}
void Variable :: chain() {
    for(int i = 0; i < _v.size(); i++) {
        _v[i]->_value = _value;
        _v[i]->_assignable = false;
    }
}
void Variable :: memberCopy(Variable *ps) {
    for(int i = 0; i < _v.size(); i++)
        _v[i]->_v.push_back(ps);
}