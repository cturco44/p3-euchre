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
    int team1tricks;
    int team2tricks;
    int winPoints;
    vector<Card> trick;
    string trump;

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

    int trick() {
        int leadPlayer = (dealer%3)+1;
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

    }

    
    void deal();
    void set_trump (Player* player0, Player* player1, Player* player2, Player* player3, int dealer) {
        
    }

};

int main(int argc, char **argv) {
    //Initialize the game
    Game game(argv[1],argv[2],argv[3],
              argv[4],argv[5],argv[6],argv[7],
              argv[8],argv[9],argv[10],argv[11]);

}
