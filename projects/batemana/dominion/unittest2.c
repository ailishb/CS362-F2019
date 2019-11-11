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

    printf("Begin minionEffect() test:\n");
    
    /*
    Test 1: Test that if player chooses to discard hand, four new
    cards are drawn.
    */
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game
    int initialDiscardCount = G.discardCount[0];
    // call the refactored function
    minionEffect(0, 1, &G, 0, 0);
    // verify that your asserts pass, for the bugs your asserts may fail
    if (assertIntEquals(G.handCount[0], 4) && 
        assertIntEquals(initialDiscardCount + 4, G.discardCount[0])) {
        printf("minionEffect Test 1 passed.\n");
    } else {
        printf("minionEffect Test 1 failed.\n");
    }

    /*
    Test 2: Test that if player does not discard, they gain two coins.
    */
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    // Get initial coin count
    int initialCoins = G.coins;
    // Call refactored function
    minionEffect(1, 0, &G, 0, 0);
   
    // Verify asserts passed
    if (assertIntEquals(initialCoins + 2, G.coins)) {
        printf("minionEffect Test 2 passed.\n");
    } else {
        printf("minionEffect Test 2 failed.\n");
    }

    printf("Test completed!\n");

    return 0;
}
