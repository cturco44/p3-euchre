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

//EFFECTS compares just ranks of two cards and returns true if lhs is less than rhs
bool rank_less(const Card &lhs, const Card &rhs)
{
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

//EFFECTS compares just suits of two cards and retursn true if lhs is less than rhs
bool suit_less(const Card &lhs, const Card &rhs)
{
    //Find suit of lhs
    int ls = 0;
    for(; ls < NUM_SUITS; ++ls)
    {
        if(lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[ls])
            break;
    }

    //Find suit of rhs
    int rs = 0;
    for(; rs < NUM_RANKS; ++rs)
    {
        if(rhs.get_suit() == RANK_NAMES_BY_WEIGHT[rs])
            break;
    }
    
    //Check suit
    if(ls < rs)
        return true;
    else
        return false;
}

//EFFECTS compares just ranks of two cards and returns true if lhs is greater than rhs
bool rank_more(const Card &lhs, const Card &rhs)
{
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

//EFFECTS compares just suits of two cards and retursn true if lhs is greater than rhs
bool suit_more(const Card &lhs, const Card &rhs)
{
    //Find suit of lhs
    int ls = 0;
    for(; ls < NUM_SUITS; ++ls)
    {
        if(lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[ls])
            break;
    }

    //Find suit of rhs
    int rs = 0;
    for(; rs < NUM_RANKS; ++rs)
    {
        if(rhs.get_suit() == RANK_NAMES_BY_WEIGHT[rs])
            break;
    }
    
    //Check suit
    if(ls > rs)
        return true;
    else
        return false;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs)
{  
    if(suit_less(lhs,rhs))
        return true;
    else if(lhs.get_suit() == rhs.get_suit())
        return rank_less(lhs,rhs);
    else 
        return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
     if(suit_more(lhs,rhs))
        return true;
    else if(lhs.get_suit() == rhs.get_suit())
        return rank_more(lhs,rhs);
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

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card)
{
    os << card.get_rank() << " of " << card.get_suit();
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump)
{
    if( a.get_suit() != trump && b.get_suit != trump)
        return a < b;
    else 
    {
        if( a.get_suit() != trump && b.get_suit == trump)
            return true;
        else if(a.get_suit() == trump && b.get_suit != trump)
            return false;
        else
            rank_less(a,b);
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, 
                        const std::string &trump)
{
    if( a.get_suit() != trump && b.get_suit != trump)
    {
        if(led_card.get_suit() != a.get_suit() && led_card.get_suit() == b.get_suit())
            return true;
        else if(led_card.get_suit() == a.get_suit() && led_card.get_suit != b.get_suit())
            return false;
        else
            return rank_less(a,b);
    }
    else 
    {
        if( a.get_suit() != trump && b.get_suit == trump)
            return true;
        else if(a.get_suit() == trump && b.get_suit != trump)
            return false;
        else
            rank_less(a,b);
    }
}
