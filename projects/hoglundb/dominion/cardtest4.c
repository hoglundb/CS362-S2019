//Card test for the steward card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "steward"

int main(){
  int newCards = 0;
  int allPassed = 1;
  int discarded = 1; int xtraCoins = 0;
  int shuffledCards = 0;

  int i, j, m;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int remove1, remove2;
  int seed  = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  struct gameState G, testG;

  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};

  initializeGame(numPlayers, k, seed, &G);
  printf("----------------Testing Card: %s---------------\n", TESTCARD);

  //Test 1: player draws 2 cards (choice = 1 + 2 cards)
  printf("Testing when player draws 2 cards: choice1  = 1 +2 cards\n");

  //Create a test game state object and call cardEffect on it
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 1;
  cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

//Player gets 2 new cards and no xtraCoins
newCards = 2;
xtraCoins = 0;

//Compair test game state to the expected game state
printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
allPassed = 1;
if(!testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded){
  printf("Test Falure: incorrect player hand count\n");
  allPassed = 0;
}
if(!testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards){
  printf("Test Falure: incorrect deck count\n");
  allPassed = 0;
}
if(!testG.coins == G.coins + xtraCoins){
  printf("Test Falure: incorrect coin count\n");
  allPassed = 0;
}
if(allPassed == 1){
  printf("Test Passed\n");
}
printf("\n\n");

//--------------------TEST 2: choice1 = 2 + 2 coins--------------------
printf("TEST when player chooses to coins: choice1 = 2 = +2 coins\n");
  //compy game state into a test game game game
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 2;
  cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 0;
  xtraCoins = 2;
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

  allPassed = 1;
  if(!testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded){
    allPassed = 0;
    printf("Test Falure: incorrect player hand count\n");
  }
  if(!testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards){
    allPassed = 0;
    printf("Test Falure: incorrect deck count\n");
  }
  if(!testG.coins == G.coins + xtraCoins){
    allPassed = 0;
    printf("Test Falure: incorrect coin count\n");
  }
  if(allPassed == 1){
    printf("Test Passed\n");
  }
	printf("\n");

  //------------------TEST3: choice1 = 3:trash two cards-----------//
  printf("---Test when player trashes to cards for all card combos---\n");
  choice1 = 3;
  //Test trashing of all combinations of 2 cards for this player
  allPassed = 1;
  for(i = 1; i < G.handCount[thisPlayer]; i++){
    for(j = i + 1; j < G.handCount[thisPlayer]; j++){
      G.hand[thisPlayer][0] = steward;
			G.hand[thisPlayer][1] = copper;
			G.hand[thisPlayer][2] = duchy;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));

			printf("starting cards: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}
			printf("; ");

			choice2 = j;
			choice3 = i;
			remove1 = testG.hand[thisPlayer][i];
			remove2 = testG.hand[thisPlayer][j];
			cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("removed: (%d)(%d); ", remove1, remove2);
			printf("ending cards: ");

			// tests that the removed cards are no longer in the player's hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
				if(testG.hand[thisPlayer][m] == remove1){
          printf("Test Falure: card still in player hand\n");
          allPassed = 0;
        }
				if(testG.hand[thisPlayer][m] == remove2){
          allPassed = 0;
          printf("Test Falure: card still in player hand\n");
        }
			}
      printf(", expected: ");
			for (m=1; m<G.handCount[thisPlayer]; m++) {
				if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
					printf("(%d)", G.hand[thisPlayer][m]);
				}
			}
			printf("\n");

      //test for the correct number of remaining cards
        newCards = 0;
  			xtraCoins = 0;
  			discarded = 3;
  			printf("hand count = %d, expected hand count = %d ;", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  			printf("deck count = %d, expected deck count = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
        printf("\n");
  			if(!testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded){
          allPassed = 0;
          printf("Test Falure: incorrect number of player cards left in hand\n");
        }
  			if(!testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards){
          allPassed = 0;
          printf("Test Falure: incorrect number of player cards left in hand\n");
        }

    }
  }
  if(allPassed == 1){
    printf("Test Passed\n");
  }
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
