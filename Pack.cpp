#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Pack.h"
#include <array>
#include <vector>

using namespace std;
// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    Card NineSPADES(Card::RANK_NINE, Card::SUIT_SPADES);
    Card TenSPADES(Card::RANK_TEN, Card::SUIT_SPADES);
    Card JackSPADES(Card::RANK_JACK, Card::SUIT_SPADES);
    Card QueenSPADES(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card KingSPADES(Card::RANK_KING, Card::SUIT_SPADES);
    Card AceSPADES(Card::RANK_ACE, Card::SUIT_SPADES);
    Card NineHEARTS(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card TenHEARTS(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card JackHEARTS(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card QueenHEARTS(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card KingHEARTS(Card::RANK_KING, Card::SUIT_HEARTS);
    Card AceHEARTS(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card NineCLUBS(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card TenCLUBS(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card JackCLUBS(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card QueenCLUBS(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card KingCLUBS(Card::RANK_KING, Card::SUIT_CLUBS);
    Card AceCLUBS(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card NineDIAMONDS(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card TenDIAMONDS(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card JackDIAMONDS(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card QueenDIAMONDS(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card KingDIAMONDS(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card AceDIAMONDS(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    
    cards = {NineSPADES,TenSPADES,JackSPADES,QueenSPADES,KingSPADES,AceSPADES,
             NineHEARTS,TenHEARTS,JackHEARTS,QueenHEARTS,KingHEARTS,AceHEARTS,
             NineCLUBS,TenCLUBS,JackCLUBS,QueenCLUBS,KingCLUBS,AceCLUBS,
             NineDIAMONDS,TenDIAMONDS,JackDIAMONDS,QueenDIAMONDS,
        KingDIAMONDS,AceDIAMONDS};
    next = 0;
}

static void in_shuffle(Card* const ptr, int packSize)
{
    const int half = packSize/2;
    vector<Card> top(half);
    vector<Card> bottom(half);
    for(int i = 0; i < packSize/2; ++i)
    {
        top[i] = *(ptr+i);
    }
    for(int i = 0; i < packSize/2; ++i)
    {
        bottom[i] = *(ptr+(packSize/2)+i);
    }
    for(int i = 0; i < packSize/2; ++i)
    {
        *(ptr+2*i) = bottom[i];
        *(ptr+2*i+1) = top[i];
    }

}
// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    next = 0;
    for(int i=0; i<24; ++i)
    {
        string rank;
        string suit;
        string temp;
        pack_input >> rank >> temp >> suit;
        Card card(rank,suit);
        cards[i] = card;
    }
}
// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    Card temp = cards[next];
    ++next;
    return temp;
}
 // EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
    next = 0;
}
// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    reset();
    for(int i = 0; i < 7; ++i)
    {
        Card* const ptr = &cards.at(0);
        in_shuffle(ptr, PACK_SIZE);
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if(next==24)
        return true;
    else 
        return false;
}
