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
    virtual T currentItem() const = 0;
    virtual bool isDone() const = 0;
    bool firstTime = true;
};

template<class T>
class NullIterator : public Iterator<T> {
public:
    friend class Term;
    NullIterator(T t) {}
    void first() {}
    void next() {}
    T currentItem() const { return nullptr; }
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
    T currentItem() const { return _s->args(_index); }
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
    T currentItem() const { return _l->args(_index); }
    bool isDone() const { return _index >= _l->arity(); }
};
template<class T>
class DFSIterator : public Iterator<T> {
private:
    DFSIterator(T t) : _t(t), _index(0) {}
    T _t;
    Iterator<T> *_it = nullptr;
    int _index;
    bool structure = false;
    void process() {
        if(!isDone()) {
            Term *ptr = _t->args(_index)->getStruct();
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
    T currentItem() const {
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
    BFSIterator(T t) : _t(t), _index(0) {}
    T _t;
    Iterator<T> *_it = nullptr;
    int _index;
    std :: queue<T>_queue;
    std :: vector<T>_result;
public:
    friend class Struct;
    friend class List;
    void first() { 
        _index = 0;
        T term;
        _queue.push(_t);
        while(!_queue.empty()) {
            term = _queue.front();
            _queue.pop();
            if(_t != term)
                _result.push_back(term);
            _it = term->createIterator();
            for(_it->first(); !_it->isDone(); _it->next())
                _queue.push(_it->currentItem());
        }
    }
    void next() {
        _index++;
    }
    T currentItem() const {
        return _result[_index];
    }
    
    bool isDone() const { 
        return _index >= _result.size();
    }
};
#endif