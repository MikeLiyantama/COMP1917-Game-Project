#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#define WINNING_KPI 150
#define NUMBER_OF_PLAYERS 3
 
 
 #define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,\
 STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
 STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
 STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
 STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
 #define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
 
int rollDice(void);
int rollDie(void);
void playerTurn (action move);
int advancePlayer (int currentPlayer);
 
int main (int argv, char * argc[]){
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game g = newGame (disciplines, dice);
    int currentPlayer = UNI_A;
 
while (getKPI(g, currentPlayer) < WINNING_KPI) {
    int diceValue = rollDice(); //simulate throw of two dice
    throwDice(g,diceValue);
    action move;
    playerTurn(move);
    // implemented in mechanicalTurk.c
    //loop until player action is PASS
  while (move.actionCode != PASS) {
    assert(isLegal(g,move) == TRUE);
    if (move.actionCode == START_SPINOFF) {
    int die = rollDie();
        if (die < 3) {
            move.actionCode = OBTAIN_IP_PATENT;
        } else {
            move.actionCode = OBTAIN_PUBLICATION;
        }
       }
    makeAction(g, move);
    }
    currentPlayer = advancePlayer(currentPlayer); // cycle through A, B, C
}
    printf("Player %d is the winner!!!", (currentPlayer+1));
    disposeGame (g);
    return EXIT_SUCCESS;
}
 
int rollDice (void) {
   int number = rollDie() + rollDie();
   return number;
}
 
int rollDie (void) {
 
   int Randomvalues = rand();
   int sideOfDie = Randomvalues%6 +1;
   return sideOfDie;
}
 
void playerTurn (action move) {
    printf( "Give action code\n "
            "PASS 0 \n"
            "BUILD_CAMPUS 1 \n"
            "BUILD_GO8 2 \n"
            "OBTAIN_ARC 3 \n"
            "START_SPINOFF 4 \n"
            "RETRAIN_STUDENTS 7 \n");
    scanf("%d",move.actionCode);
    printf("Give the path in L, R, B OR leave it empty\n");
    scanf("%s", move.destination);
    printf("Put values if you want to exchange students from to");
    scanf ("%d %d", move.disciplineFrom, move.disciplineTo);
}
 
int advancePlayer (int currentPlayer){
    int player = currentPlayer++;
    player = UNI_A + player%3;
    return player;
}
