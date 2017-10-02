#ifndef UTTERM_H
#define UTTERM_H
#include "atom.h"
#include "number.h"
#include "variable.h"
//test Number.value()
TEST (Number,ctor) {
	Number number("number", 25);
	ASSERT_EQ("25", number.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number number("number", 25);
	ASSERT_EQ("number", number.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number numberX("numberX", 25), numberY("numberY", 25);
	ASSERT_TRUE(numberX.match(numberY));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number numberX("numberX", 25), numberY("numberY", 0);
	ASSERT_FALSE(numberX.match(numberY));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Number number("number", 25);
	Atom tom("tom");
	ASSERT_FALSE(number.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
	Number number("number", 25);
	Var X("X");
	ASSERT_TRUE(number.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	Number number("number", 25);
	Atom tom("tom");
	ASSERT_FALSE(tom.match(number));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Var X("X");
	ASSERT_TRUE(tom.match(X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Var X("X");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(tom.match(X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Atom tom("tom"), jerry("jerry");
	Var X("X");
	ASSERT_TRUE(X.match(jerry));
	ASSERT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
	Var X("X");
	Number number("number", 5);
	ASSERT_TRUE(X.match(number));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
	Var X("X");
	Number numberX("numberX", 25), numberY("numberY", 100);
	ASSERT_TRUE(X.match(numberX));
	ASSERT_FALSE(X.match(numberY));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
	Var X("X");
	Atom tom("tom");
	Number number("number", 25);
	ASSERT_TRUE(X.match(tom));
	ASSERT_FALSE(X.match(number));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
	Var X("X");
	Atom tom("tom");
	Number number("number", 25);
	ASSERT_TRUE(tom.match(X));
	ASSERT_FALSE(number.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
	Var X("X");
	Atom tom("tom");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(X.match(tom));
}
#endif
