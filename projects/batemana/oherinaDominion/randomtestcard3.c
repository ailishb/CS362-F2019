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

    printf("Begin tributeEffect() random testing:\n");
    int counter = 0;

    for (counter = 0; counter < 100; counter++) {
        /*
        Test 1: Test that if next player reveals a victory card, current
        player draws two cards.
        */
        memset(&G, 23, sizeof(struct gameState)); // set the game state
        initializeGame(2, k, 123, &G); // initialize a new game
        // Randomize game:
        randomizeGamestate(&G);
        // printHand(0, &G);
        // printHand(1, &G);

        // Get initial handcount of current player
        int initialHandCount = G.handCount[G.whoseTurn];
        int initialCoinCount = G.coins;
        int initialActionsCount = G.numActions;
        // Get number of "next player"
        G.whoseTurn = 0;
        int nextPlayer = 1;
		int tributeRevealedCards[2] = {-1, -1};
		
        if ((G.discardCount[nextPlayer] + G.deckCount[nextPlayer]) <= 1) {
            if (G.deckCount[nextPlayer] > 0) {
				tributeRevealedCards[0] = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
			}
			else if (G.discardCount[nextPlayer] > 0) {
				tributeRevealedCards[0] = G.discard[nextPlayer][G.discardCount[nextPlayer]-1];
			}
			else {
				// No Card to Reveal
				if (DEBUG) {
					printf("No cards to reveal\n");
				}
			}
		} else {
			if (G.deckCount[nextPlayer] == 0) {
				tributeRevealedCards[0] = G.discard[nextPlayer][G.discardCount[nextPlayer]-1];
				tributeRevealedCards[1] = G.discard[nextPlayer][G.discardCount[nextPlayer]-2];
			} else {
				tributeRevealedCards[0] = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
				tributeRevealedCards[1] = G.deck[nextPlayer][G.deckCount[nextPlayer]-2];
			}
		}
        
		// call the refactored function
        tributeEffect(tribute, &G, 0);
        
        // Get count of types of revealed cards
        // printf("tributeRevealedcard 1: %d\n", tributeRevealedCards[0]);
        // printf("tributeRevealedCard 2: %d\n", tributeRevealedCards[1]);

        int countActionCards = 0;
        int countTreasureCards = 0;
        int countVictoryCards = 0;

        int i;
        for (i = 0; i < 2; i++) {
        	if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
        		countTreasureCards++;
			} else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
        		countVictoryCards++;
			} else { //Action Card
        		countActionCards++;
			} 
        }

		if (countActionCards == 2) {
            if (assertIntEquals(initialActionsCount + 4, G.numActions)) {
                printf("tributeEffect Test 1 passed.\n");
            } else {
                printf("tributeEffect Test 1 failed.\n");
            }
		} else if (countTreasureCards == 2) {
            if (assertIntEquals(initialCoinCount + 4, G.coins) && assertIntEquals(initialHandCount,
            G.handCount[G.whoseTurn])) {
                printf("tributeEffect Test 2 passed.\n");
            } else {
                printf("tributeEffect Test 2 failed.\n");
            }
        } else if (countVictoryCards == 2) {
            if (assertIntEquals(initialHandCount + 4, G.handCount[G.whoseTurn])) {
                printf("tributeEffect Test 3 passed.\n");
            } else {
                printf("tributeEffect Test 3 failed.\n");
            }
        } else if (countActionCards == 1 && countTreasureCards == 1) {
            if (assertIntEquals(initialActionsCount + 2, G.numActions) && assertIntEquals(initialCoinCount + 2, G.coins)) {
                printf("tributeEffect Test 4 passed.\n");
            } else {
                printf("tributeEffect Test 4 failed.\n");
            }
        } else if (countActionCards == 1 && countVictoryCards == 1) {
 if (assertIntEquals(initialActionsCount + 2, G.numActions) && assertIntEquals(initialHandCount + 2,
 G.handCount[G.whoseTurn])) {
                printf("tributeEffect Test 5 passed.\n");
            } else {
                printf("tributeEffect Test 5 failed.\n");
            }
        } else if (countTreasureCards == 1 && countVictoryCards == 1) {
 if (assertIntEquals(initialHandCount + 2, G.handCount[G.whoseTurn]) && assertIntEquals(initialCoinCount + 2, G.coins)) {
                printf("tributeEffect Test 6 passed.\n");
            } else {
                printf("tributeEffect Test 6 failed.\n");
            }
        }
    }
    printf("%d iterations run for tributeEffect function.\n", counter);

    return 0;
}
