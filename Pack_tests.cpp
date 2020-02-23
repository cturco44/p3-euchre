// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>
#include <fstream>

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

TEST(shuffle_2){
    Pack pack;
    pack.shuffle();
    ASSERT_EQUAL(Card::RANK_KING, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_JACK, pack.deal_one().get_rank());    
    ASSERT_EQUAL(Card::RANK_NINE, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_ACE, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_QUEEN, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_TEN, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_NINE, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_KING, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_JACK, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_TEN, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_ACE, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_QUEEN, pack.deal_one().get_rank());
    ASSERT_EQUAL(Card::RANK_JACK, pack.deal_one().get_rank());
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, pack.deal_one().get_rank());
}

TEST(shuffle_3){
    Pack pack;
    pack.shuffle();
    ASSERT_EQUAL(Card::SUIT_CLUBS, pack.deal_one().get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, pack.deal_one().get_suit());    
    ASSERT_EQUAL(Card::SUIT_SPADES, pack.deal_one().get_suit());
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    ASSERT_EQUAL(Card::SUIT_HEARTS, pack.deal_one().get_suit());
}

TEST(test_pack_empty) {
  Pack pack;
  pack.shuffle();
  for (int i = 0; i < 23; ++i) {
    Card temp = pack.deal_one();
    ASSERT_FALSE(pack.empty());
  }
  pack.deal_one();
  ASSERT_TRUE(pack.empty());
}

TEST(reset_shuffle){
    Pack pack;
    pack.shuffle();
    ASSERT_EQUAL(Card::SUIT_CLUBS, pack.deal_one().get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, pack.deal_one().get_suit());    
    ASSERT_EQUAL(Card::SUIT_SPADES, pack.deal_one().get_suit());
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.reset();
    ASSERT_EQUAL(Card::SUIT_CLUBS, pack.deal_one().get_suit());
}

TEST(reset_basic){
    Pack pack;
    ASSERT_EQUAL(Card::SUIT_SPADES, pack.deal_one().get_suit());
    ASSERT_EQUAL(Card::RANK_TEN, pack.deal_one().get_rank());    
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.reset();
    ASSERT_EQUAL(Card::SUIT_SPADES, pack.deal_one().get_suit());
    pack.reset();
    ASSERT_EQUAL(Card::RANK_NINE, pack.deal_one().get_rank());
}
  
TEST(pack_in)
{
  const string filename = "pack.in";
  ifstream ifs(filename);
  Pack pack(ifs);
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    pack.shuffle();
    ASSERT_EQUAL(Card::SUIT_CLUBS, pack.deal_one().get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, pack.deal_one().get_suit());    
    ASSERT_EQUAL(Card::SUIT_SPADES, pack.deal_one().get_suit());
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    ASSERT_EQUAL(Card::SUIT_HEARTS, pack.deal_one().get_suit());
}

TEST_MAIN()
