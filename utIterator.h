#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include <iostream>

 TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
  }

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term> *it = s.createIterator();
  it->first();
  it->next();
  Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

  Iterator<Term> *it2 = s2->createIterator();
  it2->first();
  ASSERT_EQ("X", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_EQ("2", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");                                        
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  Iterator<Term> *it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, Struct_DFS1) {  // s1(1, s2(tom, X, s3(1)), jerry, tom)
  Number one(1);
  Atom tom("tom"), jerry("jerry");
  Variable X("X");
  Struct s3(Atom("s3"), {&one});
  Struct s2(Atom("s2"), {&tom, &X, &s3});
  Struct s1(Atom("s1"), {&one, &s2, &jerry, &tom});
  Iterator<Term> *it = s1.createDFSIterator();
  it->first();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s2(tom, X, s3(1))", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s3(1)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("jerry", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, Struct_DFS2) {  // s([tom, X], 1, jerry)
  Number one(1);
  Atom tom("tom"), jerry("jerry");
  Variable X("X");
  List list1({&tom, &X});
  Struct s(Atom("s"), {&list1, &one, &jerry});
  Iterator<Term> *it = s.createDFSIterator();
  it->first();
  EXPECT_EQ("[tom, X]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("jerry", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, List_DFS1) { //  [1, [tom, X, [1]], jerry, tom]
  Number one(1);
  Atom tom("tom"), jerry("jerry");
  Variable X("X");
  List list3({&one});
  List list2({&tom, &X, &list3});
  List list1({&one, &list2, &jerry, &tom});
  Iterator<Term> *it = list1.createDFSIterator();
  it->first();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[tom, X, [1]]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[1]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("jerry", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, List_DFS2) { //  [s1([tom, X], s2(1)), jerry, 1]
  Number one(1);
  Atom tom("tom"), jerry("jerry");
  Variable X("X");
  Struct s2(Atom("s2"), {&one});
  List list2({&tom, &X});
  Struct s1(Atom("s1"), {&list2, &s2});
  List list1({&s1, &jerry, &one});
  Iterator<Term> *it = list1.createDFSIterator();
  it->first();
  EXPECT_EQ("s1([tom, X], s2(1))", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[tom, X]", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s2(1)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("jerry", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, Struct_BFS1) { //  s1(s2(1, tom), X, s3(jerry, tom))
  Number one(1);
  Atom tom("tom"), jerry("jerry");
  Variable X("X");
  Struct s3(Atom("s3"), {&jerry, &tom});
  Struct s2(Atom("s2"), {&one, &tom});
  Struct s1(Atom("s1"), {&s2, &X, &s3});
  Iterator<Term> *it = s1.createBFSIterator();
  it->first();
  EXPECT_EQ("s2(1, tom)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("s3(jerry, tom)", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("tom", it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
}
#endif
