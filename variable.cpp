#include "variable.h"
Variable :: Variable(string symbol) : _symbol(symbol), _value(symbol) {}
string Variable :: symbol() const { return _symbol; }
string Variable :: value() const {
    if(_structMatch)
        return _struct->value();
    if(_listMatch)
        return _list->value();
    return _value;
}
bool Variable :: match(Term &term) {
    Variable *ps = term.getVariable();
    Struct *pt = term.getStruct();
    List *pl = term.getList();
    if(ps) {
        if(_value == ps->value())
            return true;
        if(_assignable || ps->_assignable) {
            _value = ps->symbol();
            copy(ps);
            memberCopy(ps);
            if(!_assignable)
                chain();
            else if(!(ps->_assignable))
                ps->chain();
            return true;
        }
        return false;
    }
    if(pt) {
        if(!_structMatch || _assignable || _struct->value() == pt->value()) {
            _struct = pt;
            _structMatch = true;
            _assignable = false;
            return true;
        }
        return false;
    }
    if(pl) {
        if(!_listMatch || _assignable || _list->value() == pl->value()) {
            if(!checkList(pl))
                return false;
            _list = pl;
            _listMatch = true;
            _assignable = false;
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
    _v.push_back(ps);
    ps->_v.push_back(this);
}
Variable * Variable :: getVariable() { return this; }
bool Variable :: checkList(List *list) {
    for(int i = 0; i < list->elementSize(); i++) {
        if(_symbol == list->getElement(i)->symbol())
            return false;
    }
    return true;
}