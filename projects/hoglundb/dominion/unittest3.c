//Tests the baronCardEffect() function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
  int allPassed = 1;
  int choice1 = 1, choice2 = 5, choice3 = 0;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  struct gameState G, testG;

  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------Testing Function: %s----------------\n \n", "baronCardEffect()");
  //Test if player discards estete
  printf("Testing for if Player discards an estate: \n");
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 1; //discard the estate

  testG.hand[thisPlayer][3] = estate;
  baronCardEffect(&testG, thisPlayer, choice1, choice2, choice3);

  printf("Player coin count = %d, expected = %d, player hand count = %d, expected = %d\n ", testG.coins, G.coins + 4, testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
  printf("Player num buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
  if(testG.coins != G.coins + 4){
    printf("Test Falure: Incorrect player coin count");
    allPassed = 0;
  }
  if(testG.numBuys !=  G.numBuys + 1){
    printf("Test Falure: Incorrect number of buys\n");
    allPassed=0;
  }
  if( testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 1){
    printf("Test Falure: Incorrect hand count\n");
    allPassed = 0;
  }
  printf("\n");

//Test case when plyaer does not discard estate
  printf("---Testing if player does not discard an estate ---\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 0; //do not discard the estate
  baronCardEffect(&testG, thisPlayer, choice1, choice2, choice3);
  printf("Player coin count = %d, expected = %d, player hand count = %d, expected = %d\n", testG.coins, G.coins, testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("Player num buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
  allPassed = 1;
  if(testG.coins != G.coins){
    printf("Test Falure: Incorrect player coin count\n");
    allPassed = 0;
  }

  if(testG.numBuys !=  G.numBuys + 1){
    printf("Test Falure: Incorrect number of buys\n");
    allPassed=0;
  }


  if( testG.handCount[thisPlayer] != G.handCount[thisPlayer]){
    printf("Test Falure: Incorrect hand count\n");
    allPassed = 0;
  }
  if(allPassed == 1){
    printf("Test passed\n");
  }
  //Test that estate was added to deck
  printf("\n---Testing that estate card was discarded\n");
  printf("Discard pile count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
  if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + 1){
    printf("Test Failed: card was not discarded\n");
  }
  else printf("Test Passed\n");
  printf("\n");

  if(allPassed == 1)
  printf("\n ----- SUCCESS: Testing complete %s ------\n\n", "baronCardEffect()");
  else printf("\n-----Testing completed for %s. Not all tests passed\n", "baronCardEffect()");


  return 0;
}
