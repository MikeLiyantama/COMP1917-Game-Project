#include <stdio.h>
#include <stdlib.h>
#include "game.h"

/* This code below is from  Salil's lecture

#define WINNING_KPI 150

Game g = newGame (disciplines, dice);
int currentPlayer = UNI_A;

while (getKPI(g, currentPlayer) < WINNING_KPI) {
    diceValue = rollDice(); //simulate throw of two dice
    throwDice(g,diceValue);
    action move = decideAction(g);    // implemented in mechanicalTurk.c
  
    //loop until player action is PASS
  
    while (move.actionCode != PASS) {
        assert(isLegal(g,move) == TRUE);
        if (move.actionCode == START_SPINOFF) {
            //decide if outcome is patent or publication
        }
        makeAction(g, move);
        move = decideAction(g);
    }
    currentPlayer = advancePlayer(currentPlayer); // cycle through A, B, C
}

//print statistics
// free memory

*/
