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
    bool shuffle;
    bool error;
    
    int to_left(int start, int plus) {
        if (start + plus > 3) {
            return start + plus - 4;
        }
        else {
            return start + plus;
        }
    }

public:
    Game(string filename, string shuffle1, string endPoints,
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
    
    error = false;
        
    if(shuffle1 == "shuffle") {
        shuffle = true;
    } else {
        shuffle = false;
    }
        
    //Declare winpoints
    winPoints = stoi(endPoints);
        
    //Initialize all other member variables
    team1tricks = 0;
    team2tricks = 0;
    team1Score = 0;
    team2Score = 0;
    roundNum = 0;
    dealer = 0;
    orderedUp = 0;
    }
    void delete_players() {
        delete player0;
        delete player1;
        delete player2;
        delete player3;
    }
    void increment_dealer() {
        if (dealer == 3) {
            dealer = 0;
        } else {
            ++dealer;
        }
    }
    string get_player_name(int index) {
        return players[index]->get_name();
    }
    int get_highest_score() {
        if (team1Score > team2Score) {
            return team1Score;
        }
        else {
            return team2Score;
        }
    }
    int get_team1_score() {
        return team1Score;
    }
    int get_team2_score() {
        return team2Score;
    }
    string get_dealer_name() {
        return players[dealer]->get_name();
    }
    int get_win_points() {
        return winPoints;
    }
    string get_trump() {
        return trump;
    }
    
    //Sorts cards low to high
     void sort_with_trump(const string trump, vector<Card> &hand1,
                          const Card &led_card) {
         int size = int(hand1.size());
        
         for (int i = 0; i < size; ++i) {
             for(int j = 1; j < size - i; ++j) {
                 if(Card_less(hand1[i + j], hand1[i], led_card, trump)) {
                     Card holder = hand1[i];
                     hand1[i] = hand1[i + j];
                     hand1[i + j] = holder;
                 }
             }
         }
     }

    int run_trick(int leadPlayer) {
        vector<Card> orderedCards;
        vector<int> player_played;
        
        //Player leads card
        trick.push_back((players.at(leadPlayer))->lead_card(trump));
        player_played.push_back(leadPlayer);
        
        //Added cout
        cout << trick.at(0) << " led by " << players.at(leadPlayer)->get_name() << endl;
        
        //Others play cards
        for(int i = 1; i <= 3; ++i) {
            trick.push_back((players.at(to_left(leadPlayer, i))->
                             play_card(trick.at(0),trump)));
            player_played.push_back(to_left(leadPlayer, i));
            
            //added cout
            cout << trick.at(i) << " played by "
            << players.at(to_left(leadPlayer, i))->get_name() << endl;
            
        }
        
        //Sort played cards
        orderedCards = trick;
        sort_with_trump(trump, trick, orderedCards[0]);
        

        //Search for who played the highest card
        for(int i = 0; i < 4; i++) {
            if(orderedCards.at(i) == trick.at(3)) {
                trick.erase(trick.begin(), trick.end());
                return player_played[i];
            }
                
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
        int lead = to_left(dealer, 1);
        bool euchred = false;
        bool marched = false;
        int winner = 0;
        for(int i = 0; i < 5; ++i) {
            lead = run_trick(lead);
            cout << players[lead]->get_name() << " takes the trick" << endl << endl;
            if (lead == 0 || lead == 2) {
                ++team1tricks;
            }
            if(lead == 1 || lead == 3) {
                ++team2tricks;
            }
        }

        score(winner, euchred, marched);
        //Print score after hand
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
        << " have " << team2Score << " points" << endl << endl;
        team1tricks = 0;
        team2tricks = 0;
        
    }
    Card deal() {
        int dealtNum;
        pack.reset();
        if (shuffle) {
            pack.shuffle();
        }
        for(int i = 1; i <= 8; i++) {
            //Check how many cards need be given
            if((i)%2 == 1 && i <=4)
                dealtNum = 3;
            else if(i <=4)
                dealtNum = 2;
            else if((i)%2==1)
                dealtNum = 2;
            else
                dealtNum = 3;

            //Distribute Cards
            for(int j = 0; j < dealtNum; j++) {
                (players.at((dealer+i)%4))->add_card(pack.deal_one());
            }
        }
        return pack.deal_one();
    }
    
    void set_trump (const Card &upcard) {
        string order_up_suit;
        int round = 0;
            for (int i = 0; i < 8; ++i) {
                int x = i % 4;
                if (i < 4) {
                    round = 1;
                } else {
                    round = 2;
                }
                bool isdealer;
                if (to_left(dealer, x + 1) == dealer) {
                    isdealer = true;
                }
                else {
                    isdealer = false;
                }
                if(players[to_left(dealer, x + 1)]->make_trump(upcard,
                                                               isdealer, round,
                                                               order_up_suit)) {
                    cout << players[to_left(dealer, x + 1)]->get_name()
                    << " orders up " << order_up_suit << endl << endl;
                    orderedUp = to_left(dealer, x + 1);
                    trump = order_up_suit;
                    
                    if(round == 1) {
                        players[dealer]->add_and_discard(upcard);
                    }
                    return;
                }
                else {
                    cout << players[to_left(dealer, x + 1)]->get_name()
                    << " passes" << endl;
                }
            }
        
        //Should not get here
        assert(false);
    }
    

};

int main(int argc, char **argv) {
    //Checks for input errors
    bool error = false;
    string points_string = string(argv[3]);
    int points = stoi(points_string);
    if (argc != 12) {
        error = true;
    }
    if(points < 1 || points > 100) {
        error = true;
    }
    string shuffle_type = string(argv[2]);
    if(shuffle_type != "shuffle" && shuffle_type != "noshuffle") {
        error = true;
    }
    for(int i = 5; i <= 11; i += 2) {
        string player_type = string(argv[i]);
        if(player_type != "Simple" && player_type != "Human") {
            error = true;
        }
    }
    if (error) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        
        return 5;
    }
    //Initialize the game
    Game game(argv[1],argv[2],argv[3],
              argv[4],argv[5],argv[6],argv[7],
              argv[8],argv[9],argv[10],argv[11]);
    
    //Prints arguments as required
    for (int i = 0; i < 12; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;
    int hand = 0;
    while(game.get_highest_score() < game.get_win_points()) {
        cout << "Hand " << hand << endl;
        cout << game.get_dealer_name() << " deals" << endl;
        Card upcard = game.deal();
        cout << upcard << " turned up" << endl;
        game.set_trump(upcard);
        game.round();
        ++hand;
        game.increment_dealer();
        
    }
    
    if(game.get_team1_score() > game.get_team2_score()) {
        cout << game.get_player_name(0) << " and "
        << game.get_player_name(2) << " win!" << endl;
    }
    else {
        cout << game.get_player_name(1) << " and "
        << game.get_player_name(3) << " win!" << endl;
    }
    game.delete_players();
}
