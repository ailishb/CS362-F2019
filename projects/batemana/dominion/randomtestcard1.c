#include "dominion.h"
#include "dominion_helpers.h"
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

    printf("Begin baronEffect() random testing:\n");
    int counter = 0;
    
    for (counter = 0; counter < 100; counter++) {
        /*
        Test 1: Test that if Baron card discards an estate, the
        number of coins increases by 4.
        */
        memset(&G, 23, sizeof(struct gameState)); // set the game state
        initializeGame(2, k, 123, &G); // initialize a new game
        // Randomize game:
        randomizeGamestate(&G);
        
        int initialCoins = G.coins;
        int hasEstateBefore = 0;
        int hasEstateAfter = 0;
        int player = G.whoseTurn;
        int discardChoice = rand() % 2;
        
        // Check if player has estate before function
        int k;
        for (k = 0; k < G.handCount[player]; k++) {
            if (G.hand[player][k] == estate) {
                hasEstateBefore = 1;
                break;
            }
        }

        // call the refactored function
        baronEffect(discardChoice, &G, player);

        // Check if player has estate after function
         for (k = 0; k < G.handCount[player]; k++) {
            if (G.hand[player][k] == estate) {
                hasEstateAfter = 1;
                break;
            }
        }

        // Check to see if randomization has generated correct state for testing
        // Asserts are different depending on randomized choices and state
        if (discardChoice && hasEstateBefore) {
            if (assertIntEquals(initialCoins + 4, G.coins)) {
                printf("baronEffect Test 1 passed!\n");
            } else {
                printf("baronEffect Test 1 failed.\n");
            }
        } else if (!hasEstateBefore) {
            if (assertIntEquals(hasEstateAfter, 1)) {
                printf("baronEffect Test 2 passed!\n");
            } else {
                printf("baronEffect Test 2 failed.\n");
            }
        }

        printf("Test %d completed!\n", counter);
    }
    printf("%d iterations run for baronEffect function.", counter);
    return 0;
}
