//Random tests for the council_room card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int council_roomFunc(struct gameState *state, int handPos);

int checkCardEffect(int currentPlayer, int handPos, struct gameState *G){

  int result;
  //result = councilRoomCardEffect(post, currentPlayer, handPos);
  result = council_roomFunc(G, handPos);
  //drawCard(currentPlayer, post);
  assert(result == 0);
  return result;
}

int PerformRandTest(){
  int i, n, p;

  struct gameState G;

  SelectStream(2);
  PutSeed(3);

  //Fill game struct with random bytes
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

    checkCardEffect(G.whoseTurn, 0, &G);
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
