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
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    string set_trump (vector<Player*> players, const int dealer, const Card &upcard) {
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
