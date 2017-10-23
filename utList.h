#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  std::vector<Term *> args = {};
  List empty(args);
  EXPECT_EQ("[]", empty.symbol());
}

// Given there are two perfect numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128, 496]"
TEST(List, Numbers) {
  Number perfect_num(8128);
  Number four_nine_six(496);
  std::vector<Term *> args = {&perfect_num, &four_nine_six};
  List list_with_perfect_num(args);
  EXPECT_EQ("[8128, 496]", list_with_perfect_num.symbol());

}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term *> args = {&terence_tao, &alan_mathison_turing};
  List list_with_two_atoms(args);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", list_with_two_atoms.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> args = {&X, &Y};
  List list_with_two_vars(args);
  EXPECT_EQ("[X, Y]", list_with_two_vars.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number four_nine_six(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args = {&four_nine_six, &X, &terence_tao};
  List match_to_atom(args);
  EXPECT_FALSE(tom.match(match_to_atom));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number perfect_num(8128);
  Number four_nine_six(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args = {&four_nine_six, &X, &terence_tao};
  List match_to_num(args);
  EXPECT_FALSE(perfect_num.match(match_to_num));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Number four_nine_six(496);
  Variable X1("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args = {&four_nine_six, &X1, &terence_tao};
  List match_to_struct(args);
  EXPECT_FALSE(s.match(match_to_struct));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Number four_nine_six(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args = {&four_nine_six, &X, &terence_tao};
  List match_to_var(args);
  Y.match(match_to_var);
  EXPECT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Variable X("X");
  Number four_nine_six(496);
  Variable X1("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args = {&four_nine_six, &X, &terence_tao};
  List match_to_var(args);
  EXPECT_FALSE(X.match(match_to_var));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number four_nine_six(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args = {&four_nine_six, &X, &terence_tao};
  List list1(args);
  List list2(args);
  EXPECT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number four_nine_six(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args1 = {&four_nine_six, &X, &terence_tao};
  Variable Y("Y");
  std::vector<Term *> args2 = {&four_nine_six, &Y, &terence_tao};
  List list1(args1);
  List list2(args2);
  EXPECT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number four_nine_six(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> args1 = {&four_nine_six, &X, &terence_tao};
  Number perfect_num(8128);
  std::vector<Term *> args2 = {&four_nine_six, &perfect_num, &terence_tao};
  List list1(args1);
  List list2(args2);
  list1.match(list2);
  EXPECT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable Y("Y");
  Number four_nine_six(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term *> args = {&four_nine_six, &X, &terence_tao};
  List list(args);
  Y.match(list);
  X.match(alan_mathison_turing);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
  EXPECT_EQ("alan_mathison_turing", X.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  std::vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  std::vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  std::vector<Term *> first = {&f};
  List list_first(first);
  std::vector<Term *> args = {&list_first, &s, &t};
  List list(args);
  EXPECT_EQ("[first]", list.head() -> symbol());
  EXPECT_EQ("[second, third]", list.tail() -> value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  std::vector<Term *> args = {&f, &s, &t};
  List list(args);
  EXPECT_EQ("third", list.tail() -> tail() -> head() -> symbol());
  EXPECT_EQ("[]", list.tail() -> tail() -> tail() -> value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  std::vector<Term *> args = {};
  List empty(args);
  try{
    empty.head();
  }
  catch(...){}
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  std::vector<Term *> args = {};
  List empty(args);
  try{
    empty.tail();
  }catch(...){}
}

#endif
