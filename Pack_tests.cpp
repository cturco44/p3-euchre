// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

TEST(basic_shuffle){
    Pack pack;
    pack.shuffle();
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_KING, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, first.get_suit());
}

TEST_MAIN()
