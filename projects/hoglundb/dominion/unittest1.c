//Tests the councilRoomCardEffect() function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
  int allPassed = 1;
  int i;
  int handpos = 0;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  struct gameState G, testG;

  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------Testing Function: %s----------------\n \n", "councilRoomCardEffect()");
  //Test current player recieves exactly 4 cards minus their discarded card
  printf("Testing that Player draws 4 cards: \n");
  memcpy(&testG, &G, sizeof(struct gameState));
  councilRoomCardEffect( &testG, thisPlayer, handpos);
  printf("Player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 4 - 1);
  if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 4 - 1){
    allPassed = 0;
    printf("Test Falure: incorrect player hand count\n");
  }
  else printf("Test Passed\n");
  printf("\n");
  printf("Testing that player gains 1 buy\n");
  printf("Number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
  if(testG.numBuys != G.numBuys + 1){
    allPassed = 0;
    printf("Test Falure: incorrect number of buys\n");
  }
  else printf("Test Passed\n");
  printf("\n");

  //Test that each player drew a card from their own pile
  printf("Testing that each opponent drew a card\n");
  for(i = 1; i < testG.numPlayers; i ++){
    printf("opponent %d: hand count = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] + 1);
    printf("deck/discard pile count = %d, expected = %d\n", testG.discardCount[i] + testG.deckCount[i], G.discardCount[i] + G.deckCount[i]  - 1);
    if(testG.handCount[i] != G.handCount[i] + 1 || testG.discardCount[i] + testG.deckCount[i] != G.discardCount[i] + G.deckCount[i]  - 1) {
      printf("Test Falure: opponent %d did not draw a card from their pile\n", i);
      allPassed = 0;
    }
    else printf("Test Passed\n");
  }

  if(allPassed == 1)
  printf("\n ----- SUCCESS: Testing complete %s ------\n\n", "councilRoomCardEffect()");
  else printf("\n-----Testing completed for %s. Not all tests passed\n", "councilRoomCardEffect()");
  return 0;
}
