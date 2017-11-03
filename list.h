#ifndef list_h
#define list_h
#include "term.h"
#include <vector>
class List : public Term {
private:
    std :: vector<Term *>_elements;
public:
    List() : _elements() {}
    List(std :: vector<Term *>elements) : _elements(elements) {}
    List * getList() { return this; }
    string symbol() const {
        if(_elements.empty())
            return "[]";
        string _result = "[";
        for(int i = 0; i < _elements.size() - 1; i++)
            _result += (_elements[i]->symbol() + ", ");
        return _result += (_elements[_elements.size() - 1]->symbol() + "]");
    }
    string value() const {
        if(_elements.empty())
            return "[]";
        string _result = "[";
        for(int i = 0; i < _elements.size() - 1; i++)
            _result += (_elements[i]->value() + ", ");
        return _result += (_elements[_elements.size() - 1]->value() + "]");
    }
    Term * head() {
        if(_elements.empty())
            throw string("Accessing head in an empty list");
        return _elements[0];
    }
    List * tail() {
        if(_elements.empty())
            throw string("Accessing tail in an empty list");
        std :: vector<Term *>v(_elements.begin() + 1, _elements.end());
        List *temp = new List(v);
        return temp;
    }
    bool match(Term &term) {
        List *pl = term.getList();
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
        if(typeid(term) == typeid(Variable))
            return term.match(*this);
        return false;
    }
};
#endif