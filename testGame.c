// test_game.h
//Created by Michael, Josfer Lauchlan and Inura
//For COMP1917 to test whether the game.c of another group will work with our AI
//Below are the interfaces we will use to make the test steps
// action codes

// aren't these codes meant to be #defined? (Josfer)
// PASS                 0
// BUILD_CAMPUS         1
// BUILD_GO8            2
// OBTAIN_ARC           3
// START_SPINOFF        4
// OBTAIN_PUBLICATION   5
// OBTAIN_IP_PATENT     6
// RETRAIN_STUDENTS     7
 
// disciplines
// STUDENT_THD          0
// STUDENT_BPS          1
// STUDENT_BQN          2
// STUDENT_MJ           3
// STUDENT_MTV          4
// STUDENT_MMONEY       5
//Boolean Operators
// TRUE                 1
// FALSE                0


//Written by Inura De Zoysa
Game * knowledgeIsland;
While(assert (knowledgeIsland =! NULL)){
knowledgeIsland =  newGame (discipline[], dice[]);
}

//To test that the initial turn number is correct
int turnNumber = 0;
turnNumber = getTurnNumber(knowledgeIsland);
assert (turnNumber == -1);

//To test that the starting player is correct
int whoseTurn = 0;
whoseTurn = getWhoseTurn(knowledgeIsland);
assert (whoseTurn == 1);

action player;
player.actionCode = 1;
player.destination = [L,L,R,R,B];
// used for the retrain students action
player.disciplineFrom = STUDENT_THD;  
player.disciplineTo = STUDENT_THD;


//To test if placing UNIS works
assert(isLegalAction (knowledgeIsland, player) == TRUE);
makeAction (knowledgeIsland, Player);
assert(isLegalAction (knowledgeIsland, player) == FALSE);


player.actioncode = 7;
player.disciplineFrom = STUDENT_THD;  
player.disciplineTo = STUDENT_M;
assert(isLegalAction (knowledgeIsland, player) == TRUE);

throwDice (knowledgeIsland, diceScore);



disposeGame(knowledgeIsland);
assert(knowledgeIsland == NULL);

printf("All test passed, you are Awesome!");
