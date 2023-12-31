// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

//Adds cards
static void add_cards(Player *player) {
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  for (int i = 0; i < 4; ++i) {
    player->add_card(two_spades);
  }
}

//Tests get name
TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
    
    Player * bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL("Bob", bob->get_name());

    delete bob;
}
TEST(sort_with_trump) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    Card jackofspades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card nineofdiamonds(Card::RANK_NINE, Card:: SUIT_DIAMONDS);
    Card queenofhearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(aceofspades);
    billie->add_card(jackofclubs);
    billie->add_card(nineofdiamonds);
    billie->add_card(jackofspades);
    billie->add_card(queenofhearts);
    
    billie->lead_card(Card::SUIT_SPADES);
    delete billie;
}
//Tests picking non-trump card with trump present
TEST(simple_lead_card) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    Card tenofhearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card nineofdiamonds(Card::RANK_NINE, Card:: SUIT_DIAMONDS);
    Card queenofspades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(aceofspades);
    billie->add_card(jackofclubs);
    billie->add_card(tenofhearts);
    billie->add_card(nineofdiamonds);
    billie->add_card(queenofspades);
    
    ASSERT_TRUE(billie->lead_card(Card::SUIT_SPADES)==tenofhearts);

    delete billie;
}

//Tests leading when only have trump
TEST(simple_lead_card_trump) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    
    Player * billie = Player_factory("Billie", "Simple");
    add_cards(billie);
    billie->add_card(aceofspades);
    
    ASSERT_TRUE(billie->lead_card(Card::SUIT_SPADES)==aceofspades);
    
    delete billie;
}

//Tests for left bower detected as highest trump
TEST(simple_lead_card_trump_left) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);

    Player * billie = Player_factory("Billie", "Simple");
    add_cards(billie);
    billie->add_card(jackofclubs);

    ASSERT_TRUE(billie->lead_card(Card::SUIT_SPADES)==jackofclubs);
    
    delete billie;
}

//Tests for right bower detected as highest trump
TEST(simple_lead_card_trump_right) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);

    Player * billie = Player_factory("Billie", "Simple");
    add_cards(billie);
    billie->add_card(jackofspades);

    ASSERT_TRUE(billie->lead_card(Card::SUIT_SPADES)==jackofspades);
    
    delete billie;
}

//Tests for lead card with unfull deck
TEST(simple_lead_card_unfull) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    
    Player * billie = Player_factory("Billie", "Simple");
    
    billie->add_card(aceofspades);
    
    ASSERT_TRUE(billie->lead_card(Card::SUIT_SPADES)==aceofspades);
    
    delete billie;
}

//If player can follow suit
TEST(simple_play_card) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);

    Player * billie = Player_factory("Billie", "Simple");
    add_cards(billie);
    billie->add_card(jackofspades);

    ASSERT_TRUE(billie->play_card(two_spades,Card::SUIT_HEARTS)==jackofspades);
    
    delete billie;
}

//Tests for if player can't follow suit
TEST(simple_play_card_no_suit) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card nineofdiamonds(Card::RANK_NINE, Card:: SUIT_DIAMONDS);

    Player * billie = Player_factory("Billie", "Simple");
    add_cards(billie);
    billie->add_card(jackofspades);

    ASSERT_TRUE(billie->play_card(nineofdiamonds,Card::SUIT_HEARTS)==two_spades);
    
    delete billie;
}

//Tests for if trump is lead and player has right
TEST(simple_play_card_right) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card tenofhearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card nineofdiamonds(Card::RANK_NINE, Card:: SUIT_DIAMONDS);
    Card queenofspades(Card::RANK_QUEEN, Card::SUIT_SPADES);

    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(aceofspades);
    billie->add_card(jackofspades);
    billie->add_card(tenofhearts);
    billie->add_card(nineofdiamonds);
    billie->add_card(queenofspades);

    ASSERT_TRUE(billie->play_card(queenofspades,Card::SUIT_SPADES)==jackofspades);
    
    delete billie;
}

//Tests for if trump is led and player has left
TEST(simple_play_card_left) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    Card tenofhearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card nineofdiamonds(Card::RANK_NINE, Card:: SUIT_DIAMONDS);
    Card queenofspades(Card::RANK_QUEEN, Card::SUIT_SPADES);

    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(aceofspades);
    billie->add_card(jackofclubs);
    billie->add_card(tenofhearts);
    billie->add_card(nineofdiamonds);
    billie->add_card(queenofspades);

    ASSERT_TRUE(billie->play_card(queenofspades,Card::SUIT_SPADES)==jackofclubs);
    
    delete billie;
}

//Tests play card if player has not full hand
TEST(simple_play_card_unfull) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);

    Player * billie = Player_factory("Billie", "Simple");
    add_cards(billie);

    ASSERT_TRUE(billie->play_card(two_spades,Card::SUIT_SPADES)==two_spades);
    
    delete billie;
}

//Tests for if player only has trump
TEST(simple_play_card_trump) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);

    Player * billie = Player_factory("Billie", "Simple");
    add_cards(billie);
    billie->add_card(jackofspades);

    ASSERT_TRUE(billie->play_card(two_spades,Card::SUIT_SPADES)==jackofspades);
    
    delete billie;
}

//Basic add and discard
TEST(add_and_discard) {
    Card aceofclubs(Card::RANK_ACE, Card:: SUIT_CLUBS);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    Card jackofspades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card nineofdiamonds(Card::RANK_NINE, Card:: SUIT_DIAMONDS);
    Card queenofhearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card nineofhearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(aceofclubs);
    billie->add_card(nineofhearts);
    billie->add_card(nineofdiamonds);
    billie->add_card(jackofclubs);
    billie->add_card(queenofhearts);
    
    billie->add_and_discard(jackofspades);
    
    ASSERT_TRUE(billie->play_card(jackofspades, Card::SUIT_HEARTS)==jackofspades);
    delete billie;
    
    
}

//Tests if dealer has all greater than upcard and not complete hand
TEST(simple_add_and_discard_nice_hand) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);

    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);
    billie->add_card(jackofclubs);
    billie->add_and_discard(aceofspades);

    ASSERT_TRUE(billie->play_card(two_spades,Card::SUIT_HEARTS)==jackofspades);
    
    delete billie;
}

//Tests making trump not dealer round 1
TEST(simple_make_trump_dealer_round1) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);
    billie->add_card(jackofclubs);

    string order_up_suit = Card::SUIT_SPADES;
    ASSERT_TRUE(billie->make_trump(aceofspades,false,1, order_up_suit));
    
    delete billie;
}

//Tests making trump dealer round 1
TEST(simple_make_trump_round1) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);
    billie->add_card(jackofclubs);

    string order_up_suit = Card::SUIT_SPADES;
    ASSERT_TRUE(billie->make_trump(aceofspades,true,1, order_up_suit));
    
    delete billie;
}

//Tests making trump not dealer round 2
TEST(simple_make_trump_round2) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);
    billie->add_card(jackofclubs);

    string order_up_suit = Card::SUIT_SPADES;
    ASSERT_TRUE(billie->make_trump(aceofspades,false,2, order_up_suit));

    
    delete billie;
}

//Tests making trump dealer round 2
TEST(simple_make_trump_dealer_round2) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);
    billie->add_card(jackofclubs);

    string order_up_suit = Card::SUIT_SPADES;
    ASSERT_TRUE(billie->make_trump(aceofspades,true,2, order_up_suit));
    ASSERT_TRUE(order_up_suit==Card::SUIT_CLUBS);
    
    delete billie;
}

//Tests making trump call same color one card in hand dealer
TEST(simple_same_make_trump_dealer_round2) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);

    string order_up_suit = Card::SUIT_SPADES;
    ASSERT_TRUE(billie->make_trump(aceofspades,true,2, order_up_suit));
    ASSERT_TRUE(order_up_suit==Card::SUIT_CLUBS);
    
    
    delete billie;
}

//Tests making trump call same color one card in hand not dealer
TEST(simple_make_trump_not_dealer_round2) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    
    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);

    string order_up_suit = Card::SUIT_SPADES;
    ASSERT_TRUE(billie->make_trump(aceofspades,false,2, order_up_suit));
    ASSERT_TRUE(order_up_suit==Card::SUIT_CLUBS);
    
    delete billie;
}

//Tests making trump pass due to possession of opposite color
TEST(simple_make_trump_pass) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    Card queenofhearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);

    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(jackofspades);

    string order_up_suit = Card::SUIT_HEARTS;
    ASSERT_FALSE(billie->make_trump(queenofhearts,false,2, order_up_suit));
    ASSERT_TRUE(order_up_suit==Card::SUIT_HEARTS);
    
    delete billie;
}

//Tests Screw the dealer
TEST(screw_the_dealer) {
    Card aceofspades(Card::RANK_ACE, Card:: SUIT_SPADES);
    Card jackofspades(Card::RANK_JACK, Card:: SUIT_SPADES);
    Card jackofclubs(Card::RANK_JACK, Card:: SUIT_CLUBS);
    Card queenofhearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);

    Player * billie = Player_factory("Billie", "Simple");
    billie->add_card(queenofhearts);

    string order_up_suit = Card::SUIT_SPADES;
    ASSERT_TRUE(billie->make_trump(aceofspades,true,2, order_up_suit));
    ASSERT_TRUE(order_up_suit==Card::SUIT_CLUBS);
    
    delete billie;
}

TEST_MAIN()
