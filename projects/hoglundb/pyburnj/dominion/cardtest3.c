//unit test fot the great hall function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

int main(){

  int allPassed = 1;
  int i;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  struct gameState G, testG;

  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, great_hall, smithy, council_room};

  initializeGame(numPlayers, k, seed, &G);
  printf("----------------Testing Card: %s---------------\n", TESTCARD);

  //Test: make sure the the player draws one card)
  printf("---Testing the the player drew one card---\n");

  //Create a test game state object and call cardEffect on it
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("Cards in hand = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] );
  if(!testG.handCount[thisPlayer]== G.handCount[thisPlayer]){
    allPassed = 0;
    printf("Test Falure: incorrect number of cards in player hand\n");
  }
  printf("Cards in deck = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
  if(!testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1){
    allPassed = 0;
    printf("Test Falure: incorrect deck count\n");
  }
  if(allPassed == 1){
    printf("Test Passed\n");
  }

  printf("\n");

  printf("---Testing that the player has an additional action---\n");
  printf("Number of actions = %d, expected = %d\n", testG.numActions, G.numActions + 1);
  if(!testG.numActions ==  G.numActions + 1){
    allPassed = 0;
    printf("Test Falure: Incorrect number of actions for player\n");
  }
  else printf("Test Passed\n");
  printf("\n");

  //Test that no state chance occured for other players.
  printf("---Checking that no game state change occured for all %d opponent(s)---\n", G.numPlayers - 1);
  for(i = 1; i < G.numPlayers; i++){
      allPassed = 1;
     printf("Opponent%d game state:\n", i);
     printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
     printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
     printf("coin count = %d, expected = %d\n", testG.coins, G.coins);
     if(!testG.handCount[i] == G.handCount[i]){
       allPassed = 0;
       printf("Test Falure: game state change for hand count of player %d", i);
     }
     if(!testG.deckCount[i] == G.deckCount[i]){
       allPassed = 0;
       printf("Test Falure: game state change for deck count of player %d", i);
     }
     if(!testG.coins == G.coins){
       allPassed = 0;
       printf("Test Falure: game state change for coins of player %d", i);
     }
     if(allPassed == 1){
       printf("Test passed for player %d\n", i);
     }
     printf("\n");
  }
  //Test that no state change occured to the victory card
  printf("---Checking that no game state change occured for victory card pile---\n");
  printf("Estate card count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
  printf("Duchy card count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
  printf("Province card count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
  allPassed = 1;
  if(!testG.supplyCount[estate] == G.supplyCount[estate]){
    allPassed = 0;
    printf("Test Falure: incorrect number of estate cards in supply\n");
  }
  if(!testG.supplyCount[duchy] == G.supplyCount[duchy]){
    allPassed= 0;
    printf("Test Falure: incorrect number of duchy cards in supply\n");
  }
  if(!testG.supplyCount[province] == G.supplyCount[province]){
    allPassed=0;
    printf("Test Falure: incorrect number of provence cards in supply");
  }
  if(allPassed == 1){
    printf("Test Passed\n");
  }
  printf("\n");

  //Test that no state change occured to the vicotry card and kingdom card piles
  printf("---Checking that no game state change occured for kingdom card pile\n");
  printf("adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
  allPassed = 1;
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
  if(allPassed == 1){
    printf("Test Passed\n");
  }
  printf("\n ----- SUCCESS: Testing complete %s ------\n\n", TESTCARD);
  return 0;
}
