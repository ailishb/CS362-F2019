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

    printf("Begin ambassadorEffect() test:\n");
    
    /*
    Test 1: Test that other player gains a copy of the card that
    was chosen to discard.
    */
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game
    
    // Add a card to player 0's hand
    G.hand[0][2] = curse;
    // Set all cards in Player 1's hand to coppers
    int i;
    for (i = 0; i < 5; i++) {
        drawCard(1, &G);
        G.hand[1][i] = copper;
    }
    // call the refactored function
    ambassadorEffect(2, 1, &G, 0, 0);
    // verify that your asserts pass, for the bugs your asserts may fail
    if (assertIntEquals(G.hand[1][5], curse)) {
        printf("ambassadorEffect Test 1 passed.\n");
    } else {
        printf("ambassadorEffect Test 1 failed.\n");
    }

    /*
    Test 2: Test that the card chosen to discard is returned to
    the supply.
    */
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    // Get initial curse supply count
    int initialSupplyCurse = supplyCount(curse, &G);
    // Add a curse card to player 0's hand
    G.hand[0][2] = curse;
    // Call refactored function
    ambassadorEffect(2, 1, &G, 0, 0);
   
    // Verify asserts passed
    if (assertIntEquals(initialSupplyCurse + 1, supplyCount(curse, &G))) {
        printf("ambassadorEffect Test 2 passed.\n");
    } else {
        printf("ambassadorEffect Test 2 failed.\n");
    }

    printf("Test completed!\n");

    return 0;
}
