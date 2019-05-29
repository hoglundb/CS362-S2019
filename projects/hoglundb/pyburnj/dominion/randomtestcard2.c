//Random test for the smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int smithyFunc(struct gameState *state, int handPos);
int RandTestSmithyCardEffect(int handPos, struct gameState *post){

  int result = 0;
  //result = smithyCardEffect( post, currentPlayer, handPos);
  result = smithyFunc(post, handPos);
  assert(result == 0);
  return result;
}


int PerformRandTest(){
  int i, n, p;

  struct gameState G;

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n <200; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }

    int deckCount = floor(rand() % MAX_DECK + 1);//floor(Random() * MAX_DECK);

    G.numPlayers = floor(rand() % 3 + 1);

    for(p = 0; p < G.numPlayers; p++){
      G.deckCount[p] = floor(rand() % MAX_DECK + 1);
      for(i = 0; i < G.deckCount[p]; i++){
        G.deck[p][i] = floor(rand() % 27 + 1);
      }
        G.discardCount[p] = floor(rand() % deckCount + 1);
        G.handCount[p] = floor(rand() % MAX_HAND + 1);
        for(i = 0; i < G.handCount[p]; i++){
          G.hand[p][i] = floor(rand() % 27 + 1);
        }
    }

    G.playedCardCount = floor(rand() % MAX_DECK + 1);
    for(i = 0; i < G.playedCardCount; i++){
      G.playedCards[i] = floor(rand()%27 + 1);
    }

    G.whoseTurn =  floor(rand() % G.numPlayers);

    RandTestSmithyCardEffect(0, &G);
}
  return 0;
}

int main(){
  printf("\n---Beginning random tests for smithy card---\n");


    PerformRandTest();


  printf("---All 200 Random Tests for smithy Card Succeeded!---\n\n");
  return 0;
}
