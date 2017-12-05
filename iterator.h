#ifndef iterator_h
#define iterator_h

#include "atom.h"
#include "struct.h"
#include "list.h"
#include <queue>

template<class T>
class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual T * currentItem() const = 0;
    virtual bool isDone() const = 0;
    bool firstTime = true;
    virtual int index() { return 0; }
};

template<class T>
class NullIterator : public Iterator<T> {
public:
    friend class Term;
    NullIterator(Term *term) {}
    void first() {}
    void next() {}
    T * currentItem() const { return nullptr; }
    bool isDone() const { return true; }
};

template<class T>
class StructIterator : public Iterator<T> {
private:
    StructIterator(Struct *s) : _index(0), _s(s) {}
    int _index;
    Struct *_s;
public:
    friend class Struct;
    void first() { _index = 0; }
    void next() { _index++; }
    T * currentItem() const { return _s->args(_index); }
    bool isDone() const { return _index >= _s->arity(); }
};
template<class T>
class ListIterator : public Iterator<T> {
private:
    ListIterator(List *l) : _index(0), _l(l) {}
    int _index;
    List *_l;
public:
    friend class List;
    void first() { _index = 0; }
    void next() { _index++; }
    T * currentItem() const { return _l->args(_index); }
    bool isDone() const { return _index >= _l->arity(); }
};
template<class T>
class DFSIterator : public Iterator<T> {
private:
    DFSIterator(Term *t) : _t(t), _index(0) {}
    Term *_t;
    Iterator<T> *_it = nullptr;
    int _index;
    bool structure = false;
    void process() {
        Term *ptr;
        if(!isDone()) {
            ptr = _t->args(_index)->getStruct();
            if(ptr == nullptr)
                ptr = _t->args(_index)->getList();
            if(ptr) {
                _it = ptr->createDFSIterator();
                _it->first();
                structure = true;
            }
        }
    }
public:
    friend class Struct;
    friend class List;
    void first() { 
        _index = 0;
        process();
    }
    void next() {
        structure = false;
        if(_it) {
            if(_it->firstTime)
                _it->firstTime = false;
            else {
                _it->next();
                if(_it->isDone()) {
                    _it = nullptr;
                    goto label;
                }
            }
        } else {
            label:
            _index++;
            process();
        }
    }
    T * currentItem() const {
        if(structure)
            return _t->args(_index);
        if(_it)
            return _it->currentItem();
        return _t->args(_index);
    }
    bool isDone() const { return _index >= _t->arity(); }
};
template<class T>
class BFSIterator : public Iterator<T> {
private:
    BFSIterator(Term *t) : _t(t), _index(0) {}
    Term *_t;
    Iterator<T> *_it = nullptr;
    int _index;
    std :: queue<Iterator<Term> *>_queue;
    void process() {
        Term *ptr;
        if(!isDone()) {
            ptr = _t->args(_index)->getStruct();
            if(ptr == nullptr)
                ptr = _t->args(_index)->getList();
            if(ptr) {
                _it = ptr->createBFSIterator();
                _it->first();
                _queue.push(_it);
                _it = nullptr;
            }
        }
    }
public:
    friend class Struct;
    friend class List;
    void first() { 
        _index = 0;
        process();
    }
    void next() {
        
    }
    T * currentItem() const {
        if(_it)
            return _it->currentItem();
        return _t->args(_index);
    }
    bool isDone() const { 
        if(_queue.empty() && _index >= _t->arity())
            return true;
        return false;
    }
};
#endif