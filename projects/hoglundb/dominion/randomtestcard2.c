//Random test for the smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>


int RandTestSmithyCardEffect(int currentPlayer, int handPos, struct gameState *post){

  int result;
  result = smithyCardEffect( post, currentPlayer, handPos);
  assert(result == 0);
  return result;
}


int PerformRandTest(){
  int i, n, p;

  struct gameState G;

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 200; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
      p = floor(Random() * 3);
      int j;

      //Make sure game state is reasonable for each player
      for(j = 0; j < p + 1; j++){
        G.deckCount[j] = floor(Random() * MAX_DECK);
        G.discardCount[j] = floor(Random() * MAX_DECK);
        G.handCount[j] = floor(Random() * MAX_HAND);
      }
      //More restrictions to inforce a same game state
      G.playedCardCount = floor(Random() * MAX_DECK);
      G.numBuys = floor(Random() * 10);
      G.numPlayers = floor(Random() * 3);
       int handPos = floor(Random() * MAX_HAND);
       int result = RandTestSmithyCardEffect(p, handPos, &G);
       assert(result == 0);
    }
  }
  return 0;
}

int main(){
  printf("\n---Beginning random tests for smithy card---\n");


    PerformRandTest();


  printf("---All 200 Random Tests for smithy Card Succeeded!---\n\n");
  return 0;
}
