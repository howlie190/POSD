#ifndef utTest_h
#define utTest_h
#include "atom.h"
#include "variable.h"
#include "struct.h"
#include "number.h"
TEST(Atom, match) {
    Atom tom("tom"), jerry("jerry");
    Variable X("X"), Y("Y"), Z("Z");
    X.match(Y);
    X.match(Z);
    Y.match(tom);
    EXPECT_EQ("tom", Z.value());
}
TEST(Atom, match2) {
    Atom tom("tom"), jerry("jerry");
    Variable X("X"), Y("Y"), Z("Z");
    Y.match(tom);
    X.match(Y);
    EXPECT_EQ("tom", X.value());
}
TEST(Struct, match) {
    Variable X("X"), Y("Y");
    X.match(Y);
    Atom kent_beck("kent_beck");
    std :: vector<Term *> v2 = {&Y};
    Struct s2(Atom("s2"), v2);
    std :: vector<Term *> v1 = {&s2, &X};
    Struct s1(Atom("s1"), v1);
    X.match(Y);
    X.match(kent_beck);
    EXPECT_EQ("s1(s2(Y), X)", s1.symbol());
    EXPECT_EQ("s1(s2(kent_beck), kent_beck)", s1.value());
}
// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST(Struct, match2) {
    Variable X("X"), Y("Y");
    Atom teddy("teddy");
    vector<Term *>v = {&X};
    Struct s(Atom("s"), v);
    Y.match(s);
    X.match(teddy);
    EXPECT_EQ("Y", Y.symbol());
    EXPECT_EQ("s(teddy)", Y.value());
}
#endif