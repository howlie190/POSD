#ifndef UTTERM_H
#define UTTERM_H
#include "Atom.h"
#include "Number.h"
#include "Variable.h"
//test Number.value()
TEST (Number,ctor) {
	Number number_25("number_25", "25");
	ASSERT_EQ("25", number_25.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number number_25("number_25", "25");
	ASSERT_EQ("number_25", number_25.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number numberX("numberX", "25"), numberY("numberY", "25");
	ASSERT_TRUE(numberX.match(numberY));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number numberX("numberX", "25"), numberY("numberY", "0");
	ASSERT_FALSE(numberX.match(numberY));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Atom tom("tom");
	Number number("number_25", "25");
	ASSERT_FALSE(number.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
	Number number_25("number_25", "25");
	Number number_50("number_50", "50");
	Variable X("X");
	ASSERT_TRUE(number_25.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number number("number_25", "25");
	ASSERT_FALSE(tom.match(number));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable X("X");
	ASSERT_TRUE(tom.match(X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Variable X("X");
	Atom tom("tom");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(tom.match(X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Variable X("X");
	Atom tom("tom"), jerry("jerry");
	ASSERT_TRUE(X.match(jerry));
	ASSERT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
	Number number_5("number_5", "5");
	Variable X("X");
	ASSERT_TRUE(X.match(number_5));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
	Variable X("X");
	Number number_25("number_25", "25"), number_100("number_100", "100");
	ASSERT_TRUE(X.match(number_25));
	ASSERT_FALSE(X.match(number_100));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
	Variable X("X");
	Atom tom("tom");
	Number number_25("number_25", "25");
	ASSERT_TRUE(X.match(tom));
	ASSERT_FALSE(X.match(number_25));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
	Variable X("X");
	Atom tom("tom");
	Number number_25("number_25", "25");
	ASSERT_TRUE(tom.match(X));
	ASSERT_FALSE(number_25.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
	Variable X("X");
	Atom tom("tom");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(X.match(tom));
}
#endif
