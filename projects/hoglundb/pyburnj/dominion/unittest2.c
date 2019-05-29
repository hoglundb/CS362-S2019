//Tests the mineCardEffect() function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
  int allPassed = 1;
  int handpos = 4;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  struct gameState G, testG;

  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------Testing Function: %s----------------\n \n", "mineCardEffect()");
  //Test current player can choose to trach a copper and gain a silver
  printf("Testing for if Player trashes a copper and gains a silver: \n");
  memcpy(&testG, &G, sizeof(struct gameState));
  mineCardEffect(&testG, thisPlayer, 0, 5, 0, handpos);
  printf("Gained card = %d, expected = %d, ", testG.hand[thisPlayer][0], 5);
  if( testG.hand[thisPlayer][0] !=  5) {
    allPassed = 0;
  }
  printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
  if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 1){
    allPassed = 0;
  }
  if(allPassed == 0) printf("Test Falure: Error in trashing a copper for a silver\n");
  else printf("Test Passed\n");
  printf("\n");

  //Test for if a player trashes a silver and gains a gold
  printf("Testing for if Player trashes a silver and gains a gold: \n");
  memcpy(&testG, &G, sizeof(struct gameState));
  testG.hand[thisPlayer][handpos] = 5;
  mineCardEffect(&testG, thisPlayer, 0, 6, 0, handpos);
  printf("Gained card = %d, expected = %d, ", testG.hand[thisPlayer][0], 6);
  if( testG.hand[thisPlayer][0] !=  6) {
    allPassed = 0;
  }
  printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
  if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 1){
    allPassed = 0;
  }
  if(allPassed == 0) printf("Test Falure: Error in trashing a copper for a silver\n");
  else printf("Test Passed\n");
  printf("\n");

  //Test for if a player trashes a copper and attempts to gain a gold
  printf("Test if a player trashes a copper and attempts to gain a gold\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  testG.hand[thisPlayer][handpos] = 4; //This hand position holds a copper
  int testResult = mineCardEffect(&testG, thisPlayer, 0, 6, 0, handpos);
  if(testResult == -1){
    printf("Test Passed: Player cannot gain a gold from trashing a copper\n");
  }
  else printf("Test Failed: Function should return an error on illigal move\n");


  if(allPassed == 1)
  printf("\n ----- SUCCESS: Testing complete %s ------\n\n", "mineCardEffect()");
  else printf("\n-----Testing completed for %s. Not all tests passed\n", "mineCardEffect()");

  return 0;
}
