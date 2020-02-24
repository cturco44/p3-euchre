#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Player.h"
#include <array>
#include <vector>
#include <algorithm>

class SimplePlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;
    static Card highest_of_suit(const std::string &suit, const std::vector<Card> &hand) {
        std::vector<Card> of_suit;
        for (int i = 0; i < hand.size(); ++i) {
            if(hand[i].get_suit() == suit) {
                of_suit.push_back(hand[i]);
            }
        }
        sort(of_suit.begin(), of_suit.end());
        return of_suit[of_suit.size() - 1];
    }
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
            Card holder = hand[hand.size() - 1];
            hand.erase(hand.begin() + hand.size() - 1);
            
            return holder;
        }
        int highest_nontrump = 0;
        for (int i = 0; i < hand.size(); ++i) {
            if(hand[i].get_suit() != trump) {
                ++highest_nontrump;
            }
            else {
                break;
            }
        }
        Card holder = hand[highest_nontrump];
        hand.erase(hand.begin() + highest_nontrump);
        return holder;
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, const std::string &trump) {
        assert(hand.size() >= 1);
        sort(hand.begin(), hand.end());
        std::string led_suit = led_card.get_suit();
        Card holder;
        
        holder = highest_of_suit(led_suit, hand);
        for (int i = 0; i < hand.size(); ++i) {
            if(hand[i] == holder) {
                hand.erase(hand.begin() + i);
                break;
            }
        }
        return holder;
    }
    
};

class HumanPlayer : public Player {
private:
    std::string name;
public:
    HumanPlayer(std::string name_in)
    : name(name_in) {}
    //EFFECTS returns player's name
    virtual const std::string & get_name() const {
        return name;
    }
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) {
        assert(false);
    }
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const {
        assert(false);
    }
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard) {
        assert(false);
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(const std::string &trump) {
        assert(false);
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card &led_card, const std::string &trump) {
        assert(false);
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
    assert(false);
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    return os << p.get_name();
}


