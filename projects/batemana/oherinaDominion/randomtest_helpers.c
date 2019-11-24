#include "dominion.h"
#include "rngs.h"
#include "randomtest_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomizeGamestate(struct gameState *state) {
    state->whoseTurn = rand() % 2;
    state->coins = rand() % 11;
    state->numBuys = rand() % 4;
    int i;
    int k;
    // Randomize deckCount and decks of all players
    for (i = 0; i < state->numPlayers; i++) {
        state->deckCount[i] = rand() % 15;
        for (k = 0; k < state->deckCount[i]; k++) {
            // Get random card that is in game
            int card = rand() % (treasure_map + 1);
            while (state->supplyCount[card] == -1) {
                card = rand() % (treasure_map + 1);
            }
            state->deck[i][k] = card;
        }
    }
    // Randomize handcount and hands of all players
    for (i = 0; i < state->numPlayers; i++) {
        state->handCount[i] = rand() % 10;
        for (k = 0; k < state->handCount[i]; k++) {
            // Get random card that is in game
            int card = rand() % (treasure_map + 1);
            while (state->supplyCount[card] == -1) {
                card = rand() % (treasure_map + 1);
            }
            state->hand[i][k] = card;
        }
    }
    // Randomize supplycount of all cards
    for (i = 0; i <= treasure_map; i++) {
        if (state->supplyCount[i] != -1) {
            state->supplyCount[i] = rand() % 50;
        }
    }
};
