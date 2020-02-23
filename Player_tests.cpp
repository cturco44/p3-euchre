// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
    
    Player * bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL("Bob", bob->get_name());

    delete bob;
}

// Add more tests here

TEST_MAIN()
