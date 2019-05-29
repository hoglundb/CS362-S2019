//smithyCardEffect() unit test
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
  int allPassed = 1;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int handpos = 0;

  struct gameState G, testG;

  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------Testing Function: %s----------------\n \n", "smithyCardEffect()");
  //Test current player recieves exactly 3 CARDS
  printf("Testing that player draws 3 cards into their hand: \n");
  memcpy(&testG, &G, sizeof(struct gameState));
//  smithyCardEffect(&testG, thisPlayer, handpos
cardEffect(smithy, 0, 0, 0, &testG, handpos, NULL);
  printf("Player cards = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]  + 2);
  printf("Player deck = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
  if( testG.handCount[thisPlayer] != G.handCount[thisPlayer]  + 2){
    allPassed = 0;
  }
  if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 3){
    allPassed = 0;
  }
  if(allPassed == 0){
    printf("Test Falure: player did not draw three cards into their hand from their deck\n");
  }

  printf("\n ----- SUCCESS: Testing complete %s ------\n\n", "smithyCardEffect()");

  return 0;
}
