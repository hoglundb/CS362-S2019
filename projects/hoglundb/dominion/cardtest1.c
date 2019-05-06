//Test for the smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main(){

  int allPassed = 1;
  int newCards = 0;
  int discarded = 1; int xtraCoins = 0;
  int shuffledCards = 0;

  int i;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  struct gameState G, testG;

  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------Testing Card: %s----------------\n \n", TESTCARD);
  //Test current player recieves exactly 3 CARDS
  printf("Testing that Player draws 3 cards. \n");
  memcpy(&testG, &G, sizeof(struct gameState));
  newCards = 3;
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded );
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards );
  printf("coin count = %d, expected = %d\n", testG.coins, G.coins + xtraCoins );
  if(!testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded){
    printf("Test Failure: hand count was not correct!\n");
    allPassed = 0;
  }
  if(!testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards ){
    printf("Test Falure: deck count was not correct!\n");
    allPassed = 0;
  }
  if(!testG.coins == G.coins + xtraCoins){
    printf("Test Falure: coin count was not correct\n");
    allPassed = 0;;
  }
  printf("\n");
//
  //Test that 3 cards came from this player's pile

  //Test that no state chance occured for other players.
  printf("---Checking that no game state change occured for all %d opponent(s)---\n", G.numPlayers - 1);
  for(i = 1; i < G.numPlayers; i++){
     printf("Opponent%d game state:\n", i);
     printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
     printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
     printf("coin count = %d, expected = %d\n", testG.coins, G.coins);
     if(!testG.handCount[i] == G.handCount[i]){
       printf("Test Falure for hand count of opponent %d\n", i);
      allPassed = 0;
     }
     if(!testG.deckCount[i] == G.deckCount[i]){
       printf("Test Falure for deck count with player %d\n", i);
       allPassed = 0;
     }
     if(!testG.coins == G.coins){
       printf("Test Falure for coins with player %d\n", i);
       allPassed = 0;
     }
     printf("\n");
  }
  //Test that no state change occured to the victory card
  printf("---Checking that no game state change occured for victory card pile---\n");
  printf("Estate card count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
  printf("Duchy card count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
  printf("Province card count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
  if(!testG.supplyCount[estate] == G.supplyCount[estate]){
    printf("Test Falure for estate card count\n");
    allPassed = 0;
  }
  if(!testG.supplyCount[duchy] == G.supplyCount[duchy]){
    printf("Test Falure for duchy card count\n");
    allPassed = 0;
  }
  if(!testG.supplyCount[province] == G.supplyCount[province]){
    printf("Test Falure for province card count\n");
    allPassed = 0;
  }
  printf("\n");

  //Test that no state change occured to the vicotry card and kingdom card piles
  printf("---Checking that no game state change occured for kingdom card pile\n");
  printf("adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
  if(!testG.supplyCount[adventurer] == G.supplyCount[adventurer]){
    printf("Test Falure: game state changed for adventure in kindom card pile\n");
    allPassed = 0;
  }
  printf("embargo count = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]);
  if(! testG.supplyCount[embargo]== G.supplyCount[embargo]){
    printf("Test Falure: game state chage for embargo card in kingdom card pile\n");
    allPassed = 0;
  }
  printf("village count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
  if(!testG.supplyCount[village]== G.supplyCount[village]){
    printf("Test Falure: game state change for village card in kingdom card pile\n");
    allPassed = 0;
  }
  printf("minion count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
  if(!testG.supplyCount[minion]== G.supplyCount[minion]){
    printf("Test Falure: game state change for minion in kingdom card pile\n");
    allPassed = 0;
  }
  printf("mine count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);
  if(!testG.supplyCount[mine]== G.supplyCount[mine]){
    printf("Test Falure: game state change for mine card in kingdom card pile\n");
    allPassed = 0;
  }
  printf("cutpurse count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
  if(! testG.supplyCount[cutpurse]== G.supplyCount[cutpurse]){
    printf("Test Falure: game state change for cutpurse card in kingdom card pile\n");
    allPassed = 0;
  }
  printf("sea_hag count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
  if(!testG.supplyCount[sea_hag]== G.supplyCount[sea_hag]){
    printf("Test Falure: game state change for sea_hag in kingdom card pile\n");
    allPassed = 0;
  }
  printf("tribute count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
  if(!testG.supplyCount[tribute]== G.supplyCount[tribute]){
    printf("Test Falure: game state change for tribute card in kingdom card pile\n");
    allPassed = 0;
  }
  printf("smithy count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
  if(!testG.supplyCount[smithy]== G.supplyCount[smithy]){
    printf("Test Falure: game state change for smithy card in kingdom card pile\n");
    allPassed = 0;
  }
  printf("council_room count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);
  if(!testG.supplyCount[council_room]== G.supplyCount[council_room]){
    printf("Test Falure: game state change for council_room card in kingdom card pile\n");
    allPassed = 0;
  }
  printf("\n");
  if(allPassed == 1)
  printf("\n ----- SUCCESS: Testing complete %s ------\n\n", TESTCARD);
  else printf("\n-----Testing completed for %s. Not all tests passed\n", TESTCARD);
  return 0;
}
