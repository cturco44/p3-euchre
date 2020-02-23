// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <sstream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}
TEST(get_suit_2) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);
    
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(d.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);
    
    Card e(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(e.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_SPADES);
}
TEST(is_face) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.is_face(), true);
    
    Card d(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(d.is_face(), false);
    
    Card e(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(e.is_face(), true);
    
}
TEST(is_right_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.is_right_bower(Card::SUIT_HEARTS), true);
    
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(d.is_right_bower(Card::SUIT_DIAMONDS), false);
    
    Card e(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(e.is_right_bower(Card::SUIT_HEARTS), false);
}

TEST(is_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.is_left_bower(Card::SUIT_DIAMONDS), true);
    
    Card d(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(d.is_left_bower(Card::SUIT_CLUBS), false);
    
    Card e(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(e.is_left_bower(Card::SUIT_SPADES), false);
    
}
TEST(is_trump) {
    
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.is_trump(Card::SUIT_DIAMONDS), true);
    
    Card d(Card::RANK_EIGHT, Card::SUIT_SPADES);
    ASSERT_EQUAL(d.is_trump(Card::SUIT_DIAMONDS), false);
    
    Card e(Card::RANK_EIGHT, Card::SUIT_SPADES);
    ASSERT_EQUAL(e.is_trump(Card::SUIT_SPADES), true);
}
TEST(suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
}
TEST(output_overload) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.is_trump(Card::SUIT_DIAMONDS), true);
    
    ostringstream test;
    test << c;
    
    ostringstream correct;
    correct << "Jack of Hearts";
    
    ASSERT_EQUAL(test.str(), correct.str());
}

TEST(less_than1){
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
}
TEST(less_than2){
   //Same suit
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   ASSERT_EQUAL( jack < queen, true);
   ASSERT_EQUAL( queen < jack, false);
}
TEST(less_than3){
   //Same rank different suit
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   ASSERT_EQUAL(jack2 < jack, false);
   ASSERT_EQUAL(jack < jack2, true);
}
TEST(less_than4){
   //Same Rank same suit
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   ASSERT_EQUAL(ten1 < ten2, false); 
}
TEST(less_than5){
      Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Different suit
   ASSERT_EQUAL(jack2 < ace, true);
   ASSERT_EQUAL(ace < jack2, false);
   //Face card non face card same suit
   ASSERT_EQUAL(jack < ten2, false);
   ASSERT_EQUAL(ten2 < jack, true);
}

TEST(less_than6){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Face card non face card different suit
   ASSERT_EQUAL(two < jack, true);
   ASSERT_EQUAL(jack < two, false);
   //Two non face cards
   ASSERT_EQUAL(two < ten1, true);
   ASSERT_EQUAL(ten1 < two, false);
}

TEST(less_than7){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Two face cards
   ASSERT_EQUAL(jack < queen, true);
   ASSERT_EQUAL(queen < ace, true);
   ASSERT_EQUAL(ace < jack, false);
}

TEST(greater_than1){
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);

   //Same suit
   ASSERT_EQUAL( jack > queen, false);
   ASSERT_EQUAL( queen > jack, true);
   //Same rank different suit
   ASSERT_EQUAL(jack2 > jack, true);
   ASSERT_EQUAL(jack > jack2, false);
}
TEST(greater_than2){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Same Rank same suit
   ASSERT_EQUAL(ten1 > ten2, false); 
   //Different suit
   ASSERT_EQUAL(jack2 > ace, false);
   ASSERT_EQUAL(ace > jack2, true);
}

TEST(greater_than3){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Face card non face card same suit
   ASSERT_EQUAL(jack > ten2, true);
   ASSERT_EQUAL(ten2 > jack, false);
   //Face card non face card different suit
   ASSERT_EQUAL(two > jack, false);
   ASSERT_EQUAL(jack > two, true);
}

TEST(greater_than4){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Two non face cards
   ASSERT_EQUAL(two > ten1, false);
   ASSERT_EQUAL(ten1 > two, true);
   //Two face cards
   ASSERT_EQUAL(jack > queen, false);
   ASSERT_EQUAL(queen > ace, false);
   ASSERT_EQUAL(ace > jack, true);
}

TEST(not_equal1){
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   
   //Same suit
   ASSERT_EQUAL( jack != queen, true);
   ASSERT_EQUAL( queen != jack, true);
   //Same rank different suit
   ASSERT_EQUAL(jack2 != jack, true);
   ASSERT_EQUAL(jack != jack2, true);
}

TEST(not_equal2){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Same Rank same suit
   ASSERT_EQUAL(ten1 != ten2, false); 
   //Different suit
   ASSERT_EQUAL(jack2 != ace, true);
   ASSERT_EQUAL(ace != jack2, true);
}

TEST(not_equal3){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Face card non face card same suit
   ASSERT_EQUAL(jack != ten2, true);
   ASSERT_EQUAL(ten2 != jack, true);
   //Face card non face card different suit
   ASSERT_EQUAL(two != jack, true);
   ASSERT_EQUAL(jack != two, true);
}

TEST(not_equal4){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Two non face cards
   ASSERT_EQUAL(two != ten1, true);
   ASSERT_EQUAL(ten1 != two, true);
   //Two face cards
   ASSERT_EQUAL(jack != queen, true);
   ASSERT_EQUAL(queen != ace, true);
   ASSERT_EQUAL(ace != jack, true);
}

TEST(equality1){
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   
   //Same suit
   ASSERT_EQUAL( jack == queen, false);
   ASSERT_EQUAL( queen == jack, false);
   //Same rank different suit
   ASSERT_EQUAL(jack2 == jack, false);
   ASSERT_EQUAL(jack == jack2, false);
}

TEST(equality4){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Same Rank same suit
   ASSERT_EQUAL(ten1 == ten2, true); 
   //Different suit
   ASSERT_EQUAL(jack2 == ace, false);
   ASSERT_EQUAL(ace == jack2, false);
}

TEST(equality2){
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Face card non face card same suit
   ASSERT_EQUAL(jack == ten2, false);
   ASSERT_EQUAL(ten2 == jack, false);
   //Face card non face card different suit
   ASSERT_EQUAL(two == jack, false);
   ASSERT_EQUAL(jack == two, false);
}

TEST(equality3){
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Two non face cards
   ASSERT_EQUAL(two == ten1, false);
   ASSERT_EQUAL(ten1 == two, false);
   //Two face cards
   ASSERT_EQUAL(jack == queen, false);
   ASSERT_EQUAL(queen == ace, false);
   ASSERT_EQUAL(ace == jack, false);
}

TEST(card_less_1) {
    Card jackhearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jackdiamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card tenspades(Card::RANK_TEN, Card::SUIT_SPADES);
    Card nineclubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card eightclubs(Card::RANK_EIGHT, Card::RANK_EIGHT);
    
    ASSERT_EQUAL(Card_less(jackhearts, jackdiamonds, Card::SUIT_DIAMONDS), true);
    ASSERT_EQUAL(Card_less(jackhearts, jackdiamonds, Card::SUIT_HEARTS), false);
    
    ASSERT_EQUAL(Card_less(jackhearts, tenspades, Card::SUIT_HEARTS), false);
    ASSERT_EQUAL(Card_less(tenspades, jackhearts, Card::SUIT_HEARTS), true);
    
    ASSERT_EQUAL(Card_less(tenspades, jackhearts, Card::SUIT_SPADES), false);
    ASSERT_EQUAL(Card_less(tenspades, jackhearts, Card::SUIT_SPADES), false);
}

TEST(card_less_3) {
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   
   //Same suit
   ASSERT_EQUAL( Card_less(jack, queen, Card::SUIT_HEARTS), false);
   ASSERT_EQUAL( Card_less(queen, jack, Card::SUIT_DIAMONDS), true);
   //Same rank different suit
   ASSERT_EQUAL(Card_less(jack2, jack, Card::SUIT_DIAMONDS), true);
   ASSERT_EQUAL(Card_less(jack, jack2, Card::SUIT_CLUBS), true);
}

TEST(card_less_4) {
  Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Same Rank same suit
   ASSERT_EQUAL(Card_less(ten1, ten2, Card::SUIT_HEARTS), false); 
   //Different suit
   ASSERT_EQUAL(Card_less(jack2, ace, Card::SUIT_SPADES), false);
   ASSERT_EQUAL(Card_less(ace, jack2, Card::SUIT_SPADES), true);
}

TEST(card_less_5) {
Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Face card non face card same suit
   ASSERT_EQUAL(Card_less(jack2, ace, Card::SUIT_SPADES), false);
   ASSERT_EQUAL(Card_less(ten2, jack2, Card::SUIT_SPADES), true);
   //Face card non face card different suit
   ASSERT_EQUAL(Card_less(two, jack, Card::SUIT_CLUBS), false);
   ASSERT_EQUAL(Card_less(jack, two, Card::SUIT_CLUBS), true);
}

TEST(card_less_6) {
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Two non face cards
   ASSERT_EQUAL(Card_less(two, ten1, Card::SUIT_SPADES), true);
   ASSERT_EQUAL(Card_less(ten1, two, Card::SUIT_CLUBS), true);
   //Two face cards
   ASSERT_EQUAL(Card_less(jack, queen, Card::SUIT_HEARTS), false);
   ASSERT_EQUAL(Card_less(queen, ace, Card::SUIT_HEARTS), false);
   ASSERT_EQUAL(Card_less(ace, jack, Card::SUIT_DIAMONDS), true);
}

TEST(card_less_2){
    Card jackhearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jackdiamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card tenspades(Card::RANK_TEN, Card::SUIT_SPADES);
    Card nineclubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card eightclubs(Card::RANK_EIGHT, Card::RANK_EIGHT);

    //tests that led card affects algorithm
    ASSERT_EQUAL(Card_less(nineclubs, tenspades, eightclubs, Card::SUIT_DIAMONDS), true);
    ASSERT_EQUAL(Card_less(tenspades, nineclubs, eightclubs, Card::SUIT_DIAMONDS), false);
    
    ASSERT_EQUAL(Card_less(nineclubs, jackdiamonds, eightclubs, Card::SUIT_DIAMONDS), true);
    ASSERT_EQUAL(Card_less(jackdiamonds, nineclubs, eightclubs, Card::SUIT_DIAMONDS), false);
}

TEST(card_less_7){
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   
   //Same suit
   ASSERT_EQUAL( Card_less(jack, queen, ten1, Card::SUIT_HEARTS), false);
   ASSERT_EQUAL( Card_less(queen, jack, ten1, Card::SUIT_DIAMONDS), true);
   //Same rank different suit
   ASSERT_EQUAL(Card_less(jack2, jack, ten2, Card::SUIT_DIAMONDS), true);
   ASSERT_EQUAL(Card_less(jack, jack2, ten2, Card::SUIT_CLUBS), true);
}

TEST(card_less_8){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Same Rank same suit
   ASSERT_EQUAL(Card_less(ten1, ten2, ten1, Card::SUIT_HEARTS), false); 
   //Different suit
   ASSERT_EQUAL(Card_less(jack2, ace, ten1, Card::SUIT_SPADES), false);
   ASSERT_EQUAL(Card_less(ace, jack2, ace, Card::SUIT_DIAMONDS), false);
}

TEST(card_less_9){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Face card non face card same suit
   ASSERT_EQUAL(Card_less(jack2, ace, ace, Card::SUIT_SPADES), false);
   ASSERT_EQUAL(Card_less(ten2, jack2, ten2, Card::SUIT_SPADES), true);
   //Face card non face card different suit
   ASSERT_EQUAL(Card_less(two, jack, jack, Card::SUIT_CLUBS), false);
   ASSERT_EQUAL(Card_less(jack, two, two, Card::SUIT_SPADES), true);
}

TEST(card_less_10){
   Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
   //Two non face cards
   ASSERT_EQUAL(Card_less(two, ten1, two, Card::SUIT_SPADES), false);
   ASSERT_EQUAL(Card_less(ten1, two, ten1, Card::SUIT_SPADES), false);
   //Two face cards
   ASSERT_EQUAL(Card_less(jack, two, two, Card::SUIT_CLUBS), true);
   ASSERT_EQUAL(Card_less(queen, ace, jack2, Card::SUIT_CLUBS), true);
   ASSERT_EQUAL(Card_less(ace, jack, ace, Card::SUIT_DIAMONDS), true);
}


TEST_MAIN()
