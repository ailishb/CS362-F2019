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

    printf("Begin tributeEffect() test:\n");
    
    /*
    Test 1: Test that if next player reveals a victory card, current
    player draws two cards.
    */
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game
    // Set up tributeRevealedCards
    int tributeRevealedCards[2] = {-1, -1};
    // Set next player's two cards to estates
    int i;
    for (i = 0; i < 2; i++) {
        drawCard(1, &G);
        G.hand[1][i] = estate;
    }

    // Get initial handcount of current player
    int initialHandCount = G.handCount[0];

    // call the refactored function
    tributeEffect(&G, 1, tributeRevealedCards, 0);
    
    // verify that your asserts pass, for the bugs your asserts may fail
    if (assertIntEquals(initialHandCount + 4, G.handCount[0])) {
        printf("tributeEffect Test 1 passed.\n");
    } else {
        printf("tributeEffect Test 1 failed.\n");
    }

    /*
    Test 2: Test that the coin count increases as expected if revealed
    card is a treasure and hand count is as expected.
    */
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);

    // Reset tribute revealed cards
    tributeRevealedCards[0] = -1;
    tributeRevealedCards[1] = -1;
    
    // Get initial coin count
    int initialCoinCount = G.coins;

    // Get current player's initial hand count
    initialHandCount = G.handCount[0];

    // Add two treasure cards to next player's hand
    for (i = 0; i < 2; i++) {
        drawCard(1, &G);
        G.hand[1][i] = gold;
    }

    // Call refactored function
    tributeEffect(&G, 1, tributeRevealedCards, 0);
   
    // Verify asserts passed
    if (assertIntEquals(initialCoinCount + 4, G.coins) && assertIntEquals(initialHandCount, G.handCount[0])) {
        printf("tributeEffect Test 2 passed.\n");
    } else {
        printf("tributeEffect Test 2 failed.\n");
    }

    printf("Test completed!\n");

    return 0;
}
