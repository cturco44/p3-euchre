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
    int orderdUp;
    int dealer;
    int team1tricks;
    int team2tricks;

public:
    Game(string filename, string shuffle, string winPoints,
                        string player0name, string player0type,
                        string player1name, string player1type,
                        string player2name, string player2type,
                        string player3name, string player3type);
    void deal(Player* player0, Player* player1, Player* player2, Player* player3);
    
    void trump (Player* player0, Player* player1, Player* player2, Player* player3, int dealer) {
        
        
        assert(false);
    }

};

int main(int argc, char **argv) {
    //Initialize the game
    Game game(argv[1],argv[2],argv[3],
              argv[4],argv[5],argv[6],argv[7],
              argv[8],argv[9],argv[10],argv[11]);
    
    //Player 0 and 2 are partners
    //Dealer is set to player 0
    
    //Play a Hand:
    //Deal
    //Select Trump and take into account who ordered up
    //Play a trick x 5
    //Return number of tricks taken



}
