#include "list.h"
#include "variable.h"
#include <iostream>
string List :: symbol() const {
    if(!_elements.size())
        return "[]";
    string ret = "[";
    for(int i = 0; i < _elements.size() - 1; i++)
        ret += (_elements[i]->symbol() + ", ");
    return ret += (_elements[_elements.size() - 1]->symbol() + "]");
}
string List :: value() const {
    if(!_elements.size())
    return "[]";
    string ret = "[";
    for(int i = 0; i < _elements.size() - 1; i++)
        ret += (_elements[i]->value() + ", ");
    return ret += (_elements[_elements.size() - 1]->value() + "]");
}
bool List :: match(Term &term) {
    List *pl = term.getList();
    Variable *pv = term.getVariable();
    if(pl) {
        if(_elements.size() != pl->_elements.size())
            return false;
        bool ret = true;
        for(int i = 0; i < _elements.size(); i++)
            if(!(_elements[i]->match(*(pl->_elements[i])))) {
                ret = false;
                break;
            }
        return ret;
    }
    if(pv)
        return pv->match(*this);
    return false;
}