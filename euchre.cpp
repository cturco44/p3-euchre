#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Pack.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include "Player.h"
#include <array>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

/*
The Plan:
Create a Main game class with member functions
Main will:
1. Read in values from command line
2. Shuffle accordingly
3. Create a for loop that will run until one of the teams has reached the max score
4. Create a function that plays a hand
5. Create a function that plays a trick
6. Createa a function to change score
*/

class Game {
private:
    int team1Score;
    int team2Score;
    int roundNum;
    Pack pack;
    Player* player0;
    Player* player1;
    Player* player2;
    Player* player3;
    vector<Player*> players;
    int orderedUp;
    int dealer;
    //Players 0 and 2
    int team1tricks;
    
    //Players 1 and 3
    int team2tricks;
    int winPoints;
    vector<Card> trick;
    string trump;
    
    int to_left(int start, int plus) {
        if (start + plus > 3) {
            return start + plus - 4;
        }
        else {
            return start + plus;
        }
    }

public:
    Game(string filename, string shuffle, string endPoints,
                        string player0name, string player0type,
                        string player1name, string player1type,
                        string player2name, string player2type,
                        string player3name, string player3type) {
    //Create Players
    player0 = Player_factory(player0name, player0type);
    player1 = Player_factory(player1name, player1type);
    player2 = Player_factory(player2name, player2type);
    player3 = Player_factory(player3name, player3type);
    players = {player0, player1, player2, player3};

    //Create Pack
    ifstream packIn;
    packIn.open(filename);
    pack = Pack(packIn);
    if(shuffle == "shuffle")
        pack.shuffle();
    
    //Declare winpoints
    winPoints = stoi(endPoints);

    //Initialize all other member variables
    team1Score = 0;
    team2Score = 0;
    roundNum = 0;
    dealer = 0;
    orderedUp = 0;
    }
    //Sorts cards low to high
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

    int run_trick(int leadPlayer) {
        vector<Card> orderedCards;
        
        //Player leads card
        trick.push_back((players.at(leadPlayer))->lead_card(trump));
        orderedCards.push_back(trick.at(0));
        
        //Others play cards
        for(int i = 1; i <= 3; ++i) {
        trick.push_back((players.at(leadPlayer+i)->play_card(trick.at(0),trump)));
        orderedCards.push_back(trick.at(i));
        }

        //Sort played cards
        sort_with_trump(trump, trick);

        //Search for who played the highest card
        for(int i = 0; i < 4; i++) {
            if(orderedCards.at(i) == trick.at(3))
                return i;
        }
        //Should not get here
        assert(false);

    }
    void score (int &round_winner, bool &euchred, bool &marched) {
        euchred = false;
        marched = false;
        
        int team_ordered_up = 0;
        if (orderedUp == 0 || orderedUp == 2) {
            team_ordered_up = 1;
        }
        else {
            team_ordered_up = 2;
        }
        if(team1tricks > team2tricks) {
            round_winner = 1;
        }
        else {
            round_winner = 2;
        }
        //euchred
        if (round_winner == 1 && team_ordered_up == 2) {
            team1Score += 2;
            euchred = true;
            return;
        }
        if (round_winner == 2 && team_ordered_up == 1) {
            team2Score += 2;
            euchred = true;
            return;
        }
        
        //marched
        if(round_winner == 1 && team1tricks == 5) {
            team1Score += 2;
            marched = true;
            return;
        }
        if(round_winner == 2 && team2tricks == 5) {
            team2Score += 2;
            marched = true;
            return;
        }
        
        if(round_winner == 1) {
            ++team1Score;
            return;
        }
        if(round_winner == 2) {
            ++team2Score;
            return;
        }
    }
    void round() {
        int lead = dealer;
        bool euchred = false;
        bool marched = false;
        int winner = 0;
        for(int i = 0; i < 5; ++i) {
            lead = run_trick(lead);
            if (lead == 0 || lead == 2) {
                ++team1tricks;
            }
            if(lead == 1 || lead == 3) {
                ++team2tricks;
            }
        }
        //Print score after hand
        score(winner, euchred, marched);
        if(winner == 1) {
            cout << players[0]->get_name() << " and "
            <<  players[2]->get_name() << " win the hand" << endl;
            
        }
        if (winner == 2) {
            cout << players[1]->get_name() << " and "
            <<  players[3]->get_name() << " win the hand" << endl;
        }
        if(euchred) {
            cout << "euchred!" << endl;
        }
        if(marched) {
            cout << "march!" << endl;
        }
        cout << players[0]->get_name() << " and " <<  players[2]->get_name()
        << " have " << team1Score << " points" << endl;
        
        cout << players[1]->get_name() << " and " <<  players[3]->get_name()
        << " have " << team2Score << " points" << endl;
        
    }
    void deal() {
        int dealtNum;
        for(int i = 1; i <= 8; i++) {
            //Check how many cards need be given
            if((dealer+i)%2 == 1 && i <=4)
                dealtNum = 3;
            else if(i <=4)
                dealtNum = 2;
            else if((dealer+i)==1)
                dealtNum = 2;
            else
                dealtNum = 3;

            //Distribute Cards
            for(int j = 0; j < dealtNum; j++) {
                (players.at((dealer+i)%4))->add_card(pack.deal_one());
            }
            
        }
    }
    
    string set_trump (const Card &upcard) {
        string order_up_suit;
        for (int round = 1; round <=2; ++round) {
            for (int i = 0; i < 4; ++i) {
                bool isdealer;
                if (to_left(dealer, i) == dealer) {
                    isdealer = true;
                }
                else {
                    isdealer = false;
                }
                if(players[to_left(dealer, i)]->make_trump(upcard, isdealer, round, order_up_suit)) {
                    
                    orderedUp = to_left(dealer, i);
                    return order_up_suit;
                }
            }
        }
        //Should not get here
        assert(false);
    }
    

};

int main(int argc, char **argv) {
    //Initialize the game
    Game game(argv[1],argv[2],argv[3],
              argv[4],argv[5],argv[6],argv[7],
              argv[8],argv[9],argv[10],argv[11]);

}
