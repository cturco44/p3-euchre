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
    ASSERT_EQUAL(d.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_SPADES);
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
TEST(remaining_operators) {
    Card jack(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card queen(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    
    Card ace(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two(Card::RANK_TWO, Card::SUIT_CLUBS);
    
    ASSERT_EQUAL(jack < queen, true);
    ASSERT_EQUAL(jack > queen, false);
    
    ASSERT_EQUAL(ace < two, false);
    ASSERT_EQUAL(ace > two, true);
    
    ASSERT_EQUAL(jack == jack2, true);
    ASSERT_EQUAL(jack != jack2, false);
    
    ASSERT_EQUAL(ace == two, false);
    ASSERT_EQUAL(ace != two, true);
    
}
TEST(card_less) {
    Card jackhearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jackdiamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card tenspades(Card::RANK_TEN, Card::SUIT_SPADES);
    Card nineclubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card eightclubs(Card::RANK_EIGHT, Card::RANK_EIGHT);
    
    ASSERT_EQUAL(Card_less(jackhearts, jackdiamonds, Card::SUIT_DIAMONDS), true);
    ASSERT_EQUAL(Card_less(jackhearts, jackdiamonds, Card::SUIT_HEARTS), false);
    
    ASSERT_EQUAL(Card_less(jackhearts, tenspades, Card::SUIT_HEARTS), false);
    ASSERT_EQUAL(Card_less(tenspades, jackhearts, Card::SUIT_HEARTS), true);
    
    ASSERT_EQUAL(Card_less(tenspades, jackhearts, Card::SUIT_SPADES), true);
    
    ASSERT_EQUAL(Card_less(tenspades, jackhearts, Card::SUIT_SPADES), true);
    
    //tests that led card affects algorithm
    ASSERT_EQUAL(Card_less(nineclubs, tenspades, eightclubs, Card::SUIT_DIAMONDS), false);
    ASSERT_EQUAL(Card_less(tenspades, nineclubs, eightclubs, Card::SUIT_DIAMONDS), true);
    
    ASSERT_EQUAL(Card_less(nineclubs, jackdiamonds, eightclubs, Card::SUIT_DIAMONDS), true);
    ASSERT_EQUAL(Card_less(jackdiamonds, nineclubs, eightclubs, Card::SUIT_DIAMONDS), false);
    
}

// Add more test cases here

TEST_MAIN()
