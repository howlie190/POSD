#ifndef utStruct_h
#define utStruct_h
#include <vector>
#include "atom.h"
#include "struct.h"
#include "number.h"
#include "variable.h"
TEST(Struct, hobby)
{
    atom tom("tom");
    atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(atom("hobby"), v);
    ASSERT_EQ("hobby", hobby.name().symbol());
    ASSERT_EQ("tom", hobby.args(0)->symbol());
    ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());
    
}

TEST(Struct, symbol)
{
    atom tom("tom");
    atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(atom("hobby"), v);
    ASSERT_EQ("hobby(tom, chaseMouse)",hobby.symbol());
}

TEST(Struct, match1)
{
    atom tom("tom");
    atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(atom("hobby"), v);
    Struct hobby2(atom("hobby2"), v);
    EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match2){
    atom tom("tom");
    atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(atom("hobby"), v);
    std::vector<Term *> v1 = {&tom};
    Struct hobby2(atom("hobby"), v1);
    EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match3){
    atom tom("tom");
    atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(atom("hobby"), v);
    std::vector<Term *> v1 = { &chaseMouse,&tom};
    Struct hobby2(atom("hobby"), v1);
    EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match4)
{
    atom tom("tom");
    atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(atom("hobby"), v);
    Struct hobby2(atom("hobby"), v);
    EXPECT_TRUE(hobby.match(hobby2));
}

TEST(Struct, match5)
{
    atom tom("tom");
    atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(atom("hobby"), v);
    EXPECT_FALSE(hobby.match(tom));
}

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
    Variable X("X");
    std :: vector<Term *> v = {&X};
    Struct s(atom("s"), v);
    EXPECT_EQ("s(X)", s.symbol());
    EXPECT_EQ("s(X)", s.value());
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
    atom tom("tom");
    Variable X("X");
    std :: vector<Term *> v = {&X};
    Struct s(atom("s"), v);
    X.match(tom);
    EXPECT_EQ("s(X)", s.symbol());
    EXPECT_EQ("s(tom)", s.value());
}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
    Variable X("X");
    std :: vector<Term *> v2 = {&X};
    Struct s2(atom("s2"), v2);
    std :: vector<Term *> v1 = {&s2};
    Struct s1(atom("s1"), v1);
    EXPECT_EQ("s1(s2(X))", s1.symbol());
    EXPECT_EQ("s1(s2(X))", s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
    atom tom("tom");
    Variable X("X");
    std :: vector<Term *> v2 = {&X};
    Struct s2(atom("s2"), v2);
    X.match(tom);
    std :: vector<Term *> v1 = {&s2};
    Struct s1(atom("s1"), v1);
    EXPECT_EQ("s1(s2(X))", s1.symbol());
    EXPECT_EQ("s1(s2(tom))", s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
    number pi(3.14);
    Variable X("X");
    std :: vector<Term *> v2 = {&X};
    Struct s2(atom("s2"), v2);
    X.match(pi);
    std :: vector<Term *> v1 = {&s2};
    Struct s1(atom("s1"), v1);
    EXPECT_EQ("s1(s2(X))", s1.symbol());
    EXPECT_EQ("s1(s2(3.14))", s1.value());
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
    Variable X("X"), Y("Y");
    X.match(Y);
    atom kent_beck("kent_beck");
    std :: vector<Term *> v2 = {&Y};
    Struct s2(atom("s2"), v2);
    std :: vector<Term *> v1 = {&s2, &X};
    Struct s1(atom("s1"), v1);
    X.match(Y);
    X.match(kent_beck);
    EXPECT_EQ("s1(s2(Y), X)", s1.symbol());
    EXPECT_EQ("s1(s2(kent_beck), kent_beck)", s1.value());
}
#endif