// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

// add any necessary #include or using directives here
using namespace std;

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

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}
//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    if(is_left_bower(trump)) {
        return trump;
    }
    return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    if(rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING || rank == RANK_ACE) {
        return true;
    }
    return false;
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    if (rank == RANK_JACK && suit == trump) {
        return true;
    }
    return false;
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    if(rank == RANK_JACK && suit == Suit_next(trump)) {
        return true;
    }
    return false;
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if(is_left_bower(trump)) {
        return true;
    }
    if (suit == trump) {
        return true;
    }
    return false;
}
//EFFECTS compares just ranks of two cards and returns true if lhs is less than rhs
static bool rank_less(const Card &lhs, const Card &rhs)
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
static bool suit_less(const Card &lhs, const Card &rhs)
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
    for(; rs < NUM_SUITS; ++rs)
    {
        if(rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[rs])
            break;
    }
    
    //Check suit
    if(ls < rs)
        return true;
    else
        return false;
}

//EFFECTS compares just ranks of two cards and returns true if lhs is greater than rhs
static bool rank_more(const Card &lhs, const Card &rhs)
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
static bool suit_more(const Card &lhs, const Card &rhs)
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
    for(; rs < NUM_SUITS; ++rs)
    {
        if(rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[rs])
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
    if(rank_less(lhs,rhs))
        return true;
    else if(lhs.get_rank() == rhs.get_rank())
        return suit_less(lhs,rhs);
    else 
        return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
     if(rank_more(lhs,rhs))
        return true;
    else if(lhs.get_rank() == rhs.get_rank())
        return suit_more(lhs,rhs);
    else
        return false;
        
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs)
{
    if(lhs.get_suit() == rhs.get_suit())
        if(lhs.get_rank() == rhs.get_rank())
            return true;
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs)
{
    if(lhs.get_suit() != rhs.get_suit())
        return true;
    else if(lhs.get_rank() != rhs.get_rank())
        return true;
    else    
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
    return os << card.get_rank() << " of " << card.get_suit();
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump)
{
    //Check Trump
    if( a.is_trump(trump) && b.is_trump(trump))
    {
        if(b.is_right_bower(trump))
            return true;
        else if(a.is_right_bower(trump))
            return false;
        else if(b.is_left_bower(trump))
            return true;
        else if(a.is_left_bower(trump))
            return false;
        else
            return a < b;
        
    }
    else 
    {
        if( a.is_trump(trump) && !b.is_trump(trump))
            return false;
        else if(!a.is_trump(trump) && b.is_trump(trump))
            return true;
        else
            return a < b;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, 
                        const std::string &trump)
{
 //Check Trump
    if( a.is_trump(trump) && b.is_trump(trump))
    {
        return Card_less(a,b,trump);
    }
    else 
    {
        if( a.is_trump(trump) && !b.is_trump(trump))
            return false;
        else if(!a.is_trump(trump) && b.is_trump(trump))
            return true;
        else if(a.get_suit() != led_card.get_suit() && b.get_suit() ==
                led_card.get_suit())
            return true;
        else if(a.get_suit() == led_card.get_suit() && b.get_suit() !=
                led_card.get_suit())
            return false;
        else
            return a < b;
    }
}
