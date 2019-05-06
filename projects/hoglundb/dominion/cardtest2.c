//unit test for the adventure card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main(){

  int allPassed = 1;
  int i;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  struct gameState G, testG;

  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};

  initializeGame(numPlayers, k, seed, &G);
  printf("----------------Testing Card: %s---------------\n", TESTCARD);
  memcpy(&testG, &G, sizeof(struct gameState));
  printf("---Testing if two treasure cards were removed from deck---\n");
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  //Get number of treasure cards and expected number of treasure cards in player deck
  int numTreasureCardsInDeck = 0;
  int expectedTeasureCardsInDeck = 0;
  for(i = 0; i < testG.deckCount[thisPlayer]; i++){
    if(testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold){
      numTreasureCardsInDeck++;
    }
  }
  for(i = 0; i < G.deckCount[thisPlayer]; i++){
    if(G.deck[thisPlayer][i] == copper || G.deck[thisPlayer][i] == silver || G.deck[thisPlayer][i] == gold){
      expectedTeasureCardsInDeck++;
    }
  }
  expectedTeasureCardsInDeck -= 2;

  printf("Teasure Cards In deck=%d, expected = %d\n", numTreasureCardsInDeck, expectedTeasureCardsInDeck);
  if(!numTreasureCardsInDeck == expectedTeasureCardsInDeck){
     allPassed = 0;
     printf("Test Failure: Incorrect number of treasure cards in deck\n");
  }
  else printf("Test Passed\n");

  //Check that two treasure cards where added to the players hand
  int numTreasureCardsInHand = 0;
  int expectedNumTreasureCardsInHand = 0;
  for(i =0; i< testG.handCount[thisPlayer]; i++){
    if(testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold){
      numTreasureCardsInHand++;
    }
  }
  for(i =0; i< G.handCount[thisPlayer]; i++){
    if(G.hand[thisPlayer][i] == copper || G.hand[thisPlayer][i] == silver || G.hand[thisPlayer][i] == gold){
      expectedNumTreasureCardsInHand++;
    }
  }
  expectedNumTreasureCardsInHand+=2;
  printf("Teasure Cards In hand = %d, expected = %d\n", numTreasureCardsInHand, expectedNumTreasureCardsInHand);
  if(!numTreasureCardsInHand == expectedNumTreasureCardsInHand){
    printf("Test Failure: Incorrect number of treasure cards in hand\n");
    allPassed = 0;
  }
  else printf("Test Passed\n");
  printf("\n");

  //Check that the revealed cards are put in the discard pile.
  printf("---testing that all non-treasure revealed cards were put back in the discard pile---\n");
  int numRevealedCards = 0;
  int treasureFound = 0;
  i = 0;
  while(treasureFound < 2){
      if(G.deck[thisPlayer][i] == copper || G.deck[thisPlayer][i] == silver || G.deck[thisPlayer][i] == gold){
        treasureFound++;
      }
      numRevealedCards++;
      i++;
  }
  numRevealedCards-=2;

  printf("Non treasure revailed cards = %d\n", numRevealedCards);
  printf("Cards in discard/draw pile = %d, expected = %d\n", testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer], G.discardCount[thisPlayer] + G.deckCount[thisPlayer] - 2); /// numRevealedCards);
  if( testG.discardCount[thisPlayer] + testG.deckCount[thisPlayer] !=G.discardCount[thisPlayer] + G.deckCount[thisPlayer] - 2){
    printf("Test Failure. Cards not discarded\n");
    allPassed = 0;
  }
  else printf("Test Passed\n");
  printf("\n");
  //Test that no state chance occured for other players.
  printf("---Checking that no game state change occured for all %d opponent(s)---\n", G.numPlayers - 1);
  allPassed = 1;
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

  }
  if(allPassed == 1){
    printf("Test Passed: No game state change occured for other players\n");
  }
  printf("\n");
  //Test that no state change occured to the victory card
  printf("---Checking that no game state change occured for victory card pile---\n");
  allPassed = 1;
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
  if(allPassed == 1){
    printf("Test Passed: No state change for victory card pile\n");
  }

  printf("\n ----- SUCCESS: Testing complete %s ------\n\n", TESTCARD);
  return 0;
}
