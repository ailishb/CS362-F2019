#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittest_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>

int main () {

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
    // declare the game state
    struct gameState G;

    printf("Begin mineEffect() test:\n");
    
    /*
    Test 1: Test that a silver can be successfully exchanged for a gold.
    */
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game

    // Get initial handcount of current player
    int initialHandCount = G.handCount[0];
    int initialSupplyCount = G.supplyCount[silver];
    // Add silver to player 0's hand
    G.hand[0][4] = silver;

    // call the refactored function
    mineEffect(4, gold, &G, 0, 0);
    
    // verify that your asserts pass, for the bugs your asserts may fail
    if (assertIntEquals(initialHandCount, G.handCount[0]) && assertIntEquals(G.hand[0][4], gold) &&
    assertIntEquals(initialSupplyCount, G.supplyCount[silver])) {
        printf("mineEffect Test 1 passed.\n");
    } else {
        printf("mineEffect Test 1 failed.\n");
    }

    printf("Test completed!\n\n");

    return 0;
}
