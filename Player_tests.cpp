// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
    
    Player * bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL("Bob", bob->get_name());

    delete bob;
}
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
    
    billie->lead_card(Card::SUIT_SPADES);
}

// Add more tests here

TEST_MAIN()
