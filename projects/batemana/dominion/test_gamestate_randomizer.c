#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include "randomtest_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion};
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    printf("Game state before randomization: \n");
    printStateFull(&G);
    randomizeGamestate(&G);
    printf("Game state after randomization: \n");
    printStateFull(&G);
}
