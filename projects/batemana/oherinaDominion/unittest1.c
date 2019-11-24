#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "rngs.h"
#include "unittest_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>

int main () {

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
    // declare the game state
    struct gameState G;

    printf("Begin baronEffect() test:\n");
    
    /*
    Test 1: Test that if Baron card discards an estate, the
    number of coins increases by 4.
    */
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game
    int initialCoins = G.coins;
    // call the refactored function
    baronEffect(baron, 1, &G, 0);
    // verify that your asserts pass, for the bugs your asserts may fail
    if (assertIntEquals(initialCoins + 4, G.coins)) {
        printf("baronEffect Test 1 passed!\n");
    } else {
        printf("baronEffect Test 1 failed.\n");
    }

    /*
    Test 2: Test that if player does not have an Estate card, an Estate card
    is added to player's hand.
    */
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    // Set all cards in player 0's hand to copper (no Estate cards)
    int handCount = G.handCount[0];
    int handIndex;
    for (handIndex = 0; handIndex < handCount; handIndex++) {
        G.hand[0][handIndex] = copper;
    }
    // Call refactored function
    baronEffect(baron, 1, &G, 0);
    // Count number of estates in player 0's deck now
    int estateCount = 0;
    handCount = G.handCount[0];
    for (handIndex = 0; handIndex < handCount; handIndex++) {
        if (G.hand[0][handIndex] == estate) {
            estateCount++;
        }
    }
    // Verify asserts passed
    if (assertIntEquals(1, estateCount)) {
        printf("baronEffect Test 2 passed.\n");
    } else {
        printf("baronEffect Test 2 failed.\n");
    }

    printf("Test completed!\n");

    return 0;
}
