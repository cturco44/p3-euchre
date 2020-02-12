// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

//EFFECTS Initializes Card to the Two of Spades
Card::Card()
{
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs)
{
    //Find suit of lhs
    int ls = 0;
    for(; ls < NUM_SUITS; ++ls)
    {
        if(lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[ls])
            break;
    }

    //Find rank of rhs
    int rs = 0;
    for(; rs < NUM_RANKS; ++rs)
    {
        if(rhs.get_rank() == RANK_NAMES_BY_WEIGHT[rs])
            break;
    }
    
    //Check suit
    if(ls < rs)
        return true;
    else if(ls > rs)
        return false;
    
    //Find rank of lhs
    int lr = 0;
    for(; lr < NUM_RANKS; ++lr)
    {
        if(lhs.get_rank() == RANK_NAMES_BY_WEIGHT[lr])
            break;
    }

    //Find rank of rhs
    int rr = 0;
    for(; rr < NUM_RANKS; ++rr)
    {
        if(rhs.get_rank() == RANK_NAMES_BY_WEIGHT[rr])
            break;
    }
    
    //Check
    if(lr < rr)
        return true;
    else 
        return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
    //Find suit of lhs
    int ls = 0;
    for(; ls < NUM_SUITS; ++ls)
    {
        if(lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[ls])
            break;
    }

    //Find rank of rhs
    int rs = 0;
    for(; rs < NUM_RANKS; ++rs)
    {
        if(rhs.get_rank() == RANK_NAMES_BY_WEIGHT[rs])
            break;
    }
    
    //Check suit
    if(ls > rs)
        return true;
    else if(ls < rs)
        return false;
    
    //Find rank of lhs
    int lr = 0;
    for(; lr < NUM_RANKS; ++lr)
    {
        if(lhs.get_rank() == RANK_NAMES_BY_WEIGHT[lr])
            break;
    }

    //Find rank of rhs
    int rr = 0;
    for(; rr < NUM_RANKS; ++rr)
    {
        if(rhs.get_rank() == RANK_NAMES_BY_WEIGHT[rr])
            break;
    }
    
    //Check
    if(lr > rr)
        return true;
    else 
        return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs)
{
    if(lhs.get_suit == rhs.get_suit)
        if(lhs.get_rank == rhs.get_rank)
            return true;
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs)
{
    if(lhs.get_suit != rhs.get_suit)
        if(lhs.get_rank != rhs.get_rank)
            return true;
    return false;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit)
{
    if(suit == "Spades")
        return "Clubs";
    else if(suit == "Clubs")
        return "Spades";
    else if(suit == "Hearts")
        return "Diamonds";
    else
        return "Hearts";
}