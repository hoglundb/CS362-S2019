//Random tests for the adventure card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int checkCardEffect(int currentPlayer, int handPos, struct gameState *post){

  int result;
  result = councilRoomCardEffect(post, currentPlayer, handPos);
  //drawCard(currentPlayer, post);
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
    }
    p =  floor(rand() % 2 + 1);
    int j;

    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);

    //Make sure game state is reasonable for each player
    for(j = 0; j < p; j++){
      G.deckCount[j] = floor(Random() * MAX_DECK);
      G.discardCount[j] = floor(Random() * MAX_DECK);
      G.handCount[j] = floor(Random() * MAX_HAND);
    }

    //More restrictions to inforce a same game state
    G.playedCardCount = floor(Random() * MAX_DECK);
    G.numBuys = floor(Random() * MAX_DECK);
    G.numPlayers =  floor(Random() * 3);
    int handPos = floor(Random() * MAX_HAND);
    checkCardEffect(p, handPos, &G);
  }
  return 0;
}

int main(){

srand(time(0));
  printf("\n---Beginning random test for the council_room card---\n");
  PerformRandTest();
  printf("---All 200 Random Tests for council_room card succeeded---\n\n");

  return 0;
}
