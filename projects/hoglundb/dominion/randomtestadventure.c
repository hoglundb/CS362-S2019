//Program to test the adventure card using random testing

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>


//Calls adenture card effect function and gets the returned result
int RandTestAdventureCard(int drawntreasure, struct gameState* state, int currentPlayer, int cardDrawn, int temphand[MAX_HAND], int z){
  int result = adventureCardEffect(1, state, currentPlayer, cardDrawn, temphand, z);

  assert(result == 0);
  return 0;
}

//Sets up random test data for calling the advetureCardEffectFunction
int PerformRandTest(){
  SelectStream(2);
  PutSeed(3);
  int p, i,n;

  struct gameState G;

  //Fill game struct with random bytes
  for (n = 0; n <200; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }

    p =  floor(Random() * 2);

    //Make sure game state is reasonable for player p
    int deckCount = floor(rand() % MAX_DECK + 1);//floor(Random() * MAX_DECK);
    G.deckCount[p] = deckCount;
    G.discardCount[p] = floor(rand() % deckCount + 1);
    int handCount =  floor(rand() % MAX_HAND + 1);//;
    G.handCount[p] = handCount;

    //Restrict cards to what is allowed in the game
    for(i = 0; i < handCount; i++){
      G.hand[p][i] =  floor(rand() % 27 + 1);
    }
    for(i = 0; i < deckCount; i++){
      G.deck[p][i] = floor(rand() % 27 + 1);
    }

    int temphand[MAX_HAND];

    int drawntreasure = floor(rand() % MAX_HAND);
    int cardDrawn = floor(rand() % 27 + 1);
    int z =  floor(rand() % 27 + 1);

   int result =RandTestAdventureCard(drawntreasure, &G, p, cardDrawn, temphand, z);
    assert(result == 0);
  }
 return 0;
}



int main(){
  srand(time(0));
  printf("\n---Beginning random test for the adventure card---\n");

  PerformRandTest();

  printf("---All 200 Random Tests for Adventure Card Succeeded!--\n\n\n");
  return 0;
}
