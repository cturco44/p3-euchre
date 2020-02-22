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
    Card NineSPADES(Card::SUIT_SPADES,Card::RANK_NINE);
    Card TenSPADES(Card::SUIT_SPADES,Card::RANK_TEN);
    Card JackSPADES(Card::SUIT_SPADES,Card::RANK_JACK);
    Card QueenSPADES(Card::SUIT_SPADES,Card::RANK_QUEEN);
    Card KingSPADES(Card::SUIT_SPADES,Card::RANK_KING);
    Card AceSPADES(Card::SUIT_SPADES,Card::RANK_ACE);
    Card NineHEARTS(Card::SUIT_HEARTS,Card::RANK_NINE);
    Card TenHEARTS(Card::SUIT_HEARTS,Card::RANK_TEN);
    Card JackHEARTS(Card::SUIT_HEARTS,Card::RANK_JACK);
    Card QueenHEARTS(Card::SUIT_HEARTS,Card::RANK_QUEEN);
    Card KingHEARTS(Card::SUIT_HEARTS,Card::RANK_KING);
    Card AceHEARTS(Card::SUIT_HEARTS,Card::RANK_ACE);
    Card NineCLUBS(Card::SUIT_CLUBS,Card::RANK_NINE);
    Card TenCLUBS(Card::SUIT_CLUBS,Card::RANK_TEN);
    Card JackCLUBS(Card::SUIT_CLUBS,Card::RANK_JACK);
    Card QueenCLUBS(Card::SUIT_CLUBS,Card::RANK_QUEEN);
    Card KingCLUBS(Card::SUIT_CLUBS,Card::RANK_KING);
    Card AceCLUBS(Card::SUIT_CLUBS,Card::RANK_ACE);
    Card NineDIAMONDS(Card::SUIT_DIAMONDS,Card::RANK_NINE);
    Card TenDIAMONDS(Card::SUIT_DIAMONDS,Card::RANK_TEN);
    Card JackDIAMONDS(Card::SUIT_DIAMONDS,Card::RANK_JACK);
    Card QueenDIAMONDS(Card::SUIT_DIAMONDS,Card::RANK_QUEEN);
    Card KingDIAMONDS(Card::SUIT_DIAMONDS,Card::RANK_KING);
    Card AceDIAMONDS(Card::SUIT_DIAMONDS,Card::RANK_ACE);
    
    cards = {NineSPADES,TenSPADES,JackSPADES,QueenSPADES,KingSPADES,AceSPADES,
             NineHEARTS,TenHEARTS,JackHEARTS,QueenHEARTS,KingHEARTS,AceHEARTS,
             NineCLUBS,TenCLUBS,JackCLUBS,QueenCLUBS,KingCLUBS,AceCLUBS,
             NineDIAMONDS,TenDIAMONDS,JackDIAMONDS,QueenDIAMONDS,KingDIAMONDS,AceDIAMONDS};
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
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

}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if(next==32)
        return true;
    else 
        return false;
}
