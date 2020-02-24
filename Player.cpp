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
public:
    SimplePlayer(std::string name_in)
      : name(name_in) {}
    //EFFECTS returns player's name
    virtual const std::string & get_name() const {
        return name;
    }
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) {
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const {
        assert(round == 1 || round == 2);
        if(round == 1) {
            int num_good_trump = 0;
            for(int i = 0; i < hand.size(); ++i) {
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
            for(int i = 0; i < hand.size(); ++i) {
                if(hand[i].get_suit() == Suit_next(upcard.get_suit())
                   && hand[i].is_face()) {
                    ++num_good_trump;
                }
            }
            if(num_good_trump >= 1) {
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
    virtual void add_and_discard(const Card &upcard) {
        assert(hand.size() >= 1);
        Card smallest = upcard;
        int smallest_index = 6;
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i] < smallest) {
                smallest = hand[i];
                smallest_index = i;
            }
        }
        if (smallest_index != 6) {
            hand[smallest_index] = upcard;
        }
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(const std::string &trump) {
        assert(hand.size() >= 1);
        sort(hand.begin(), hand.end());
    
        if (hand[0].is_trump(trump)) {
            
            return hand[hand.size() - 1];
        }
        return hand[0];
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, const std::string &trump) {
        assert(hand.size() >= 1);
        std::string led_suit = led_card.get_suit();
        std::vector<Card> of_led_suit;
        
        for (int i = 0; i < hand.size(); ++i) {
            if(hand[i].get_suit() == led_suit) {
                of_led_suit.push_back(hand[i]);
            }
        }
        std::sort(of_led_suit.begin(), of_led_suit.end());
        of_led_suit[of_led_suit.size() - 1];
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

