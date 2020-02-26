#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Player.h"
#include <array>
#include <vector>
#include <algorithm>


using namespace std;

class SimplePlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;
    
    void sort_with_trump(const string trump, vector<Card> &hand1) {
         int size = int(hand1.size());
        
         for (int i = 0; i < size; ++i) {
             for(int j = 1; j < size - i; ++j) {
                 if(Card_less(hand1[i + j], hand1[i], trump)) {
                     Card holder = hand1[i];
                     hand1[i] = hand1[i + j];
                     hand1[i + j] = holder;
                 }
             }
         }
     }
    
public:
    SimplePlayer(std::string name_in)
      : name(name_in) {}
    //EFFECTS returns player's name
    virtual const std::string & get_name() const override{
        return name;
    }
 
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) override{
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const override{
        assert(round == 1 || round == 2);
        if(round == 1) {
            int num_good_trump = 0;
            for(int i = 0; i < int(hand.size()); ++i) {
                if(hand[i].is_face() && hand[i].is_trump(upcard.get_suit())) {
                    ++num_good_trump;
                }
            }
            if(num_good_trump >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }
        if(round == 2) {
            int num_good_trump = 0;
            for(int i = 0; i < int(hand.size()); ++i) {
                if(hand[i].get_suit(Suit_next(upcard.get_suit())) == Suit_next(upcard.get_suit())
                   && hand[i].is_face()) {
                    ++num_good_trump;
                }
            }
            if(num_good_trump >= 1) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            if(is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else {
                return false;
            }
        }
        //Shouldn't make it here
        assert(false);
        return false;
    }
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    
    //If the trump suit is ordered up during round one, the dealer picks up
    //the upcard. The dealer then discards the lowest card in their hand,
    //even if this is the upcard, for a final total of five cards.
    //(Note that at this point, the trump suit is the suit of the upcard.)
    virtual void add_and_discard(const Card &upcard) override{
        assert(hand.size() >= 1);
        //int size = int(hand.size());
        string trump = upcard.get_suit();
        sort_with_trump(trump, hand);
        
        if(Card_less(hand[0], upcard, trump)) {
            hand[0] = upcard;
        }
        
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    
    //When a Simple Player leads a trick, they play the highest non-trump card
    //in their hand. If they have only trump cards, they play the highest
    //trump card in their hand.
    virtual Card lead_card(const std::string &trump) override{
        assert(hand.size() >= 1);
        sort_with_trump(trump, hand);
        Card holder;
        int size = static_cast<int>(hand.size());
        
        if(hand[0].is_trump(trump)) {
            holder = hand[size - 1];
            hand.erase(hand.begin() + size - 1);
            return holder;
        }
        for(int i = 0; i < size; ++i) {
            if(hand[i].is_trump(trump)) {
                holder = hand[i - 1];
                hand.erase(hand.begin() + (i - 1));
                return holder;
            }
        }
        return hand[hand.size() - 1];
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    
    //If a Simple Player can follow suit, they play the highest card that
    //follows suit. Otherwise, they play the lowest card in their hand.
    virtual Card play_card(const Card &led_card, const std::string &trump) override {
        assert(hand.size() >= 1);
        sort_with_trump(trump, hand);
        std::string led_suit = led_card.get_suit();
        int hand_size = int(hand.size());
        vector<Card> suit_holder;
        Card holder;
        
        for (int i = 0; i < hand_size; ++i) {
            if(hand[i].get_suit(trump) == led_suit) {
                suit_holder.push_back(hand[i]);
            }
        }
        if (int(suit_holder.size()) == 0) {
            holder = hand[0];
            hand.erase(hand.begin());
            return holder;
        }
        sort_with_trump(trump, suit_holder);
        holder = suit_holder[int(suit_holder.size()) - 1];
        for (int i = 0; i < hand_size; ++i) {
            if(holder == hand[i]) {
                hand.erase(hand.begin() + i);
                return holder;
            }
        }
        //should not make it here
        assert(false);
    }
    
};

class HumanPlayer : public Player {
private:
    string name;
    vector<Card> hand;
    static void print_hand(const vector<Card> &hand){
        for(size_t i = 0; i < hand.size(); ++i)
        {
            cout << i+1 << ". " << hand.at(i) << endl;
        }
    }
public:
    HumanPlayer(string name_in)
    : name(name_in) {}
    //EFFECTS returns player's name
    virtual const string & get_name() const override{
        return name;
    }
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) override{
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const override{
        print_hand(hand);
        string userDecision;
        if(round == 1)
        {
            cout<<"Enter pass or " << upcard.get_suit()<<":";
            cin >> userDecision;
            cout << endl;
            if(userDecision == "pass")
                return false;
            else if(userDecision == upcard.get_suit())
            {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else
            {
                cout<<"Invalid input"<<endl;
                return false;
            }
        }
        else if(round ==2){
            cout<<"Enter pass, Diamonds, Spades, Hearts, Clubs:";
            cin >> userDecision;
            cout<<endl;
            if(userDecision == "pass")
                return false;
            else if(userDecision == "Diamonds")
            {
                order_up_suit = "Diamonds";
                return true;
            }
            else if(userDecision == "Hearts")
            {
                order_up_suit = "Hearts";
                return true;
            }
            else if(userDecision == "Spades")
            {
                order_up_suit = "Spades";
                return true;
            }
            else if(userDecision == "Clubs")
            {
                order_up_suit = "Clubs";
                return true;
            }
            else{cout<<"Invalid input"<<endl; return false;}
        }
        else{cout<<"you messed up"; return false;}
        
    }
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) override{
        string userDecision;
        print_hand(hand);
        cout<< "-1. Discard " << upcard <<endl;
        cout<< "Choose:";
        cin >> userDecision;
        int choice = stoi(userDecision);
        if(choice != -1)
        {
            hand.erase(hand.begin()+choice-1);
            hand.push_back(upcard);
            sort(hand.begin(), hand.end());
            return;
        }
        else
            return;
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(const std::string &trump) override{
        string userDecision;
        print_hand(hand);
        cout<<"Select a card:";
        cin >> userDecision;
        int choice = stoi(userDecision);
        Card temp = hand.at(choice-1);
        hand.erase(hand.begin()+choice-1);
        std::sort(hand.begin(), hand.end());
        return temp;
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, const std::string &trump) override{
        string userDecision;
        print_hand(hand);
        cout<<"Select a card:";
        cin >> userDecision;
        int choice = stoi(userDecision);
        Card temp = hand.at(choice-1);
        hand.erase(hand.begin()+choice-1);
        std::sort(hand.begin(), hand.end());
        return temp;
    }
    
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
    if(strategy == "Simple") {
      return new SimplePlayer(name);
    }
    if(strategy == "Human") {
        return new HumanPlayer(name);
    }
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    return os << p.get_name();
}

