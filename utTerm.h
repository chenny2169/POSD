#ifndef UTTERM_H
#define UTTERM_H

#include "Number.h"
#include "Atom.h"
#include "Variable.h"


// test Number.value()
TEST (Number,ctor) {
  Number one("1");
  ASSERT_EQ("1", one.value());
}
//test Number.symbol()
TEST (Number, symbol) {
  Number one("1");
  ASSERT_EQ("1", one.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number firstTwentyFive("25");
  Number secondTwentyFive("25");
  ASSERT_TRUE(firstTwentyFive.match(secondTwentyFive));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number twentyFive("25");
  Number zero("0");
  ASSERT_FALSE(twentyFive.match(zero));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number twentyFive("25");
  Atom tom("tom");
  ASSERT_FALSE(twentyFive.match(&tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number twentyFive("25");
  Variable X("X");
  ASSERT_TRUE(twentyFive.match(&X));
}

// ?- tom=25.
// false.
TEST (Atom, matchFailureDiffConstant) {
  Atom tom("tom");
  Number twentyFive("25");
  ASSERT_FALSE(tom.match(&twentyFive));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Variable X("X");
  ASSERT_TRUE(tom.match(&X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
  Variable X("X");
  Atom tom("tom");
  ASSERT_TRUE(X.match(&tom));
  ASSERT_TRUE(tom.match(&X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Variable X("X");
  Atom jerry("jerry");
  Atom tom("tom");
  ASSERT_TRUE(X.match(&jerry));
  ASSERT_FALSE(tom.match(&X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
  Variable X("X");
  Number five("5");
  ASSERT_TRUE(X.match(&five));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
  Variable X("X");
  Number twentyFive("25");
  Number hundred("100");
  ASSERT_TRUE(X.match(&twentyFive));
  ASSERT_FALSE(X.match(&hundred));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Variable X("X");
  Atom tom("tom");
  Number twentyFive("25");
  ASSERT_TRUE(X.match(&tom));
  ASSERT_FALSE(X.match(&twentyFive));
}

//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Atom tom("tom");
  Variable X("X");
  Number twentyFive("25");
  ASSERT_TRUE(tom.match(&X));
  ASSERT_FALSE(twentyFive.match(&X));
}

//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
  Variable X("X");
  Atom tom("tom");
  EXPECT_TRUE(X.match(&tom));
  EXPECT_TRUE(X.match(&tom));
}
#endif
