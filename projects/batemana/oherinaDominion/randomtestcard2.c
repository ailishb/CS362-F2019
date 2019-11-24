#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "rngs.h"
#include "unittest_helpers.h"
#include "randomtest_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
    srand(time(NULL));
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
    // declare the game state
    struct gameState G;

    printf("Begin minionEffect() random testing:\n");
    int counter = 0;
    for (counter = 0; counter < 100; counter++) {
        /*
        Test 1: Test that if player chooses to discard hand, four new
        cards are drawn.
        */
        memset(&G, 23, sizeof(struct gameState)); // set the game state
        initializeGame(2, k, 123, &G); // initialize a new game
        // Randomize gameState
        randomizeGamestate(&G);
        int choice1 = rand() % 2;
        int choice2 = rand() % 2;
        int initialCoins = G.coins;
        int initialDiscardCount = G.discardCount[0];
        
        // call the refactored function
        minionEffect(minion, choice1, choice2, &G, 0);
        // verify that your asserts pass, for the bugs your asserts may fail
        if (choice2) {
            if (assertIntEquals(G.handCount[G.whoseTurn], 4) && 
                assertIntEquals(initialDiscardCount + 4, G.discardCount[G.whoseTurn])) {
                printf("minionEffect Test 1 passed.\n");
            } else {
                printf("minionEffect Test 1 failed.\n");
            }
        } else if (choice1) {
            if (assertIntEquals(initialCoins + 2, G.coins)) {
                printf("minionEffect Test 2 passed.\n");
            } else {
                printf("minionEffect Test 2 failed.\n");
            }
        }
    }
    printf("%d iterations run for minionEffect function.\n", counter);
    return 0;
}
