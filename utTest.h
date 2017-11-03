#ifndef utTest_h
#define utTest_h

#include "term.h"
#include "variable.h"
#include "structure.h"

TEST (Atom, match) {
    Atom tom("tom");
    ASSERT_EQ("tom", tom.symbol());
    ASSERT_EQ("tom", tom.value());
    ASSERT_TRUE(tom.match(tom));
}
TEST (Number, match) {
    Number num1(3.14), num2(1);
    ASSERT_EQ("3.14", num1.symbol());
    ASSERT_EQ("3.14", num1.value());
    ASSERT_FALSE(num1.match(num2));
}
TEST (Variable, match) {
    Variable X("X"), Y("Y"), W("W"), Z("Z"), A("A");
    Atom tom("tom");
    X.match(Y);
    X.match(tom);
    ASSERT_EQ("tom", X.value());
    X.match(Y);
    W.match(Z);
    W.match(X);
    Z.match(tom);
    ASSERT_EQ("tom", X.value());
    ASSERT_EQ("tom", Y.value());
    ASSERT_EQ("tom", W.value());
    ASSERT_EQ("tom", Z.value());
}
TEST (Struct, symbol) {
    Variable X("X");
    Atom tom("tom");
    Number num(3.14);
    std :: vector<Term *>v = {&X, &tom, &num};
    Struct s(Atom("s"), v);
    ASSERT_EQ("s(X, tom, 3.14)", s.symbol());
}
TEST (Struct, match) {
    Variable X("X"), Y("Y");
    Atom tom("tom"), jerry("jerry");
    Number num(3.14);
    std :: vector<Term *>v = {&X, &tom, &num};
    Struct s(Atom("s"), v);
    X.match(jerry);
    ASSERT_EQ("s(X, tom, 3.14)", s.symbol());
    s.match(Y);
    ASSERT_EQ("s(jerry, tom, 3.14)", Y.value());
}
#endif