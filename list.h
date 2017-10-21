#ifndef list_h
#define list_h
#include "term.h"
#include <vector>
#include <stdexcept>
class List : public Term {
private:
    std :: vector<Term *>_elements;
public:
    List() : _elements() {}
    List (std :: vector<Term *> const & elements) : _elements(elements) {}
    Term * head() const {
        if(!_elements.size())
            throw std :: runtime_error("Accessing head in an empty list");
        return _elements[0];
    }
    List * tail() const {
        if(!_elements.size())
            throw std :: runtime_error("Accessing tail in an empty list");
        std :: vector<Term *>v(_elements.begin() + 1, _elements.end());
        List *temp = new List(v);
        return temp;
    }
    string symbol() const;
    List * getList() { return this; }
    int elementSize() { return _elements.size(); }
    Term * getElement(int index) { return _elements[index]; }
    bool match(Term &term);
};
#endif