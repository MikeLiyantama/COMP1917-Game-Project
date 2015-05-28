// tests for Game.c
//Created by Michael, Josfer Lauchlan and Inura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Game.h"

#define TERRA_NULLIUS -1
#define WORKING_PATH {'L','R','R','B','R','R','R','B','R','R','R','R','B','R','R','R','B','R','R','R','R','B','R','R','R','B','R','R','R','R','B','R','R','R','B','R','R','R','R','B','R','R','R','B','R','R','R','R','B','R','R','L','B','L','L','R','R','B','R','R','R','R','B','R','R','R','R','B','R','R','R','R','B','R','R','R','R','B','R','R','R','L','B','L','L','R','R','R','R','R'}
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

void testGameState0 (Game g);
void testPlayerState0 (Game g, int playerNumber);
void testGameState1 (Game g);
void testPlayer1State1 (Game g, int playerNumber);
void testPlayer2State1 (Game g, int playerNumber);
void testPlayer3State1 (Game g, int playerNumber);
void testGameState2(Game g);
void testPlayer1State2 (Game g, int playerNumber);
void testPlayer2State2 (Game g, int playerNumber);
void testPlayer3State2 (Game g, int playerNumber);
void testGameState3(Game g);
void testPlayer1State3 (Game g, int playerNumber);
void testPlayer2State3 (Game g, int playerNumber);
void testPlayer3State3 (Game g, int playerNumber);

int main (int argc, char *argv[]) {

   int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
   int dice[NUM_REGIONS] = DEFAULT_DICE;

   Game g = newGame(disciplines, dice);
   
   action p1;
   p1.actionCode = PASS;
   action p2;
   p2.actionCode = PASS;
   action p3;
   p3.actionCode = PASS;
   

   testGameState0(g);
   throwDice(g, 4); 
   assert(isLegalAction(g,p1)==TRUE);
   makeAction(g, p1); 
   throwDice(g, 5);
   assert(isLegalAction(g,p2)==TRUE);
   makeAction(g, p2);
   throwDice(g, 5);
   assert(isLegalAction(g,p3)==TRUE);
   makeAction(g, p3);
   throwDice(g, 8);
   testGameState1(g);
   
   p1.actionCode = OBTAIN_ARC;
   strncpy(p1.destination, "R", PATH_LIMIT);
   assert(isLegalAction(g,p1)==TRUE);
   makeAction(g, p1);
   strncpy(p1.destination, "RL", PATH_LIMIT);
   assert(isLegalAction(g,p1)==TRUE);
   makeAction(g, p1);
   p1.actionCode=BUILD_CAMPUS;
   assert(isLegalAction(g,p1)==TRUE);
   makeAction(g, p1);
   p1.actionCode=PASS;
   assert(isLegalAction(g,p1)==TRUE);
   makeAction(g, p1);
   throwDice(g, 9);

   
   p2.actionCode = OBTAIN_ARC;
   strncpy(p2.destination, "RRLRLL", PATH_LIMIT);
   assert(isLegalAction(g,p2)==TRUE);
   makeAction(g, p2);
   strncpy(p2.destination, "RRLRLLL", PATH_LIMIT);
   assert(isLegalAction(g,p2)==TRUE);
   makeAction(g, p2);
   p2.actionCode=BUILD_CAMPUS;
   assert(isLegalAction(g,p2)==TRUE);
   makeAction(g, p2);
   p2.actionCode=PASS;
   assert(isLegalAction(g,p2)==TRUE);
   makeAction(g, p2);
   throwDice(g, 7);

   
   p3.actionCode = OBTAIN_ARC;
   strncpy(p3.destination, "LRLRLB", PATH_LIMIT);
   assert(isLegalAction(g,p3)==TRUE);
   makeAction(g, p3);
   strncpy(p3.destination, "LRLRR", PATH_LIMIT);
   assert(isLegalAction(g,p3)==TRUE);
   makeAction(g, p3);
   strncpy(p3.destination, "LRLRRR", PATH_LIMIT);
   assert(isLegalAction(g,p3)==TRUE);
   makeAction(g, p3);
   p3.actionCode=PASS;
   assert(isLegalAction(g,p3)==TRUE);
   makeAction(g, p3);
   throwDice(g, 8);
   
   testGameState2(g);
   
   p1.actionCode=PASS;
   assert(isLegalAction(g,p1)==TRUE);
   makeAction(g, p1);
   throwDice(g, 2);
   
   p2.actionCode=PASS;
   assert(isLegalAction(g,p2)==TRUE);
   makeAction(g, p2);
   throwDice(g, 2);
   
   p3.actionCode = RETRAIN_STUDENTS;
   strncpy(p3.destination, "\0", PATH_LIMIT);
   p3.disciplineFrom = STUDENT_BPS;
   p3.disciplineTo = STUDENT_MMONEY;
   assert(isLegalAction(g,p3)==TRUE);
   makeAction(g, p3);
   p3.actionCode=PASS;
   assert(isLegalAction(g,p3)==TRUE);
   makeAction(g, p3);
   throwDice(g, 2);

   testGameState3(g);
   
   int counter=0;
   while (counter<12){
      assert(getDiscipline(g,counter)==disciplines[counter]);
      //assert(getDiscipline(g,counter)==DEFAULT_DISCIPLINES[counter]);
      counter++;
   }

   counter = 0;

   while (counter<12){
      assert(getDiceValue(g,counter)==dice[counter]);
      //assert(getDiceValue(g,counter)==DEFAULT_DICE[counter]);
      counter++;
   }

   disposeGame(g);        
   assert(g == NULL);
   printf("All tests passed!\n You are awesome!!\n");

   return EXIT_SUCCESS;
}

//tests the state of the game at Terra Nullis
void testGameState0(Game g){

   assert((getMostARCs(g)) == NO_ONE);   
   assert((getWhoseTurn(g)) == NO_ONE);
   
   int count = 0;
   char tempPath1[91] = {'\0'};
   char workingPath1[90] = WORKING_PATH;
   while(count<90){
      tempPath1[count] = workingPath1[count];
      if(count == 26 || count == 51){
         assert(getCampus(g, tempPath1) == CAMPUS_A);
         printf("testing campus A\n");
      } else if(count == 17 || count == 44){
         assert(getCampus(g, tempPath1) == CAMPUS_B);
         printf("testing campus B\n");
      } else if(count == 8 || count == 35){
         assert(getCampus(g, tempPath1) == CAMPUS_C);
         printf("testing campus C\n");
      } else {
         assert(getCampus(g, tempPath1) == VACANT_VERTEX);
         printf("testing vertex %d\n", count);
      } 
      count++;
   }
   
   count = 0;
   char tempPath2[91] = {'\0'};
   char workingPath2[90] = WORKING_PATH;
   while(count<90){
      tempPath2[count] = workingPath2[count];
      assert(getARC(g, tempPath2) == VACANT_ARC);
      printf("testing arc %d\n", count);
      count++;
   }
   
   assert(getMostPublications(g) == NO_ONE);
   assert(getTurnNumber(g) == TERRA_NULLIUS);

   int playerNumber = 1;
   while (playerNumber <= 3){
      testPlayerState0(g, playerNumber);
      playerNumber++;
   }
   printf("Test Game State 0 passed!\n");
}

//test state of the player at Terra Nullis
void testPlayerState0 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 20);
   assert(getARCs(g, playerNumber) == 0);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 2);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }   
   printf("test player state 0 passed!\n");

}

void testGameState1(Game g){
   
   assert((getMostARCs(g)) == NO_ONE);   
   assert((getWhoseTurn(g)) == UNI_A);
   
   int count = 0;
   char tempPath1[91] = {'\0'};
   char workingPath1[90] = WORKING_PATH;
   while(count<90){
      tempPath1[count] = workingPath1[count];
      if(count == 26 || count == 51){
         assert(getCampus(g, tempPath1) == CAMPUS_A);
         printf("testing campus A\n");
      } else if(count == 17 || count == 44){
         assert(getCampus(g, tempPath1) == CAMPUS_B);
         printf("testing campus B\n");
      } else if(count == 8 || count == 35){
         assert(getCampus(g, tempPath1) == CAMPUS_C);
         printf("testing campus C\n");
      } else {
         assert(getCampus(g, tempPath1) == VACANT_VERTEX);
         printf("testing vertex %d\n", count);
      } 
      count++;
   }
   
   count = 0;
   char tempPath2[91] = {'\0'};
   char workingPath2[90] = WORKING_PATH;
   while(count<90){
      tempPath2[count] = workingPath2[count];
      assert(getARC(g, tempPath2) == VACANT_ARC);
      printf("testing arc %d\n", count);
      count++;
   }
   
   assert(getMostPublications(g) == NO_ONE);
   assert(getTurnNumber(g) == 3);

   int playerNumber = 1;
   while (playerNumber <= 3){
      if(playerNumber ==1){
         testPlayer1State1(g, playerNumber);
      } else if(playerNumber == 2){
         testPlayer2State1(g, playerNumber);
      } else {
         testPlayer3State1(g, playerNumber);
      }
      playerNumber++;
   }
   printf("Test Game State 1 passed!\n");
}

void testPlayer1State1 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 20);
   assert(getARCs(g, playerNumber) == 0);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 2);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
      disciplineTo = STUDENT_BPS;
      disciplineFrom++;
   }   
   printf("test player 1 state 1 passed!\n");

}

void testPlayer2State1 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 20);
   assert(getARCs(g, playerNumber) == 0);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 2);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 5);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }
   printf("test player 2 state 1 passed!\n");

}

void testPlayer3State1 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 20);
   assert(getARCs(g, playerNumber) == 0);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 2);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 2);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 2);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   } 
   printf("test player 3 state 1 passed!\n");

}

void testGameState2(Game g){

   assert(getMostARCs(g) == UNI_C);   
   assert(getWhoseTurn(g) == UNI_A);
   
   int count = 0;
   char tempPath1[91] = {'\0'};
   char workingPath1[90] = WORKING_PATH;
   while(count<90){
      tempPath1[count] = workingPath1[count];
      if(count == 26 || count == 51 || count == 53|| count == 81){
         assert(getCampus(g, tempPath1) == CAMPUS_A);
         printf("testing campus A\n");
      } else if(count == 17 || count == 44 || count == 42 || count == 78) {
         assert(getCampus(g, tempPath1) == CAMPUS_B);
         printf("testing campus B\n");
      } else if(count == 8 || count == 35){
         assert(getCampus(g, tempPath1) == CAMPUS_C);
         printf("campus C\n");
      } else {
         assert(getCampus(g, tempPath1) == VACANT_VERTEX);
         printf("testing vertex %d\n", count);
      } 
      count++;
   }
   
   count = 0;
   char tempPath2[91] = {'\0'};
   char workingPath2[90] = WORKING_PATH;
   while(count<90){
      tempPath2[count] = workingPath2[count];
      printf("[%d]:", count);
      if(count == 51 || count == 52 || count == 53){
         assert(getARC(g, tempPath2) == ARC_A);
         printf("testing arc A\n");
      } else if(count == 44 || count == 43 || count == 42){
         assert(getARC(g, tempPath2) == ARC_B);
         printf("testing arc B\n");
      } else if(count == 8 || count == 6 || count == 7 || count == 58){
         assert(getARC(g, tempPath2) == ARC_C);
         printf("testing arc C\n");
      } else {
         assert(getARC(g, tempPath2) == VACANT_ARC);
         printf("testing arc %d\n", count);
      } 
      count++;
   }
   
   assert(getMostPublications(g) == NO_ONE);
   assert(getTurnNumber(g) == 6);

   int playerNumber = 1;
   while (playerNumber <= 3){
      if(playerNumber ==1){
         testPlayer1State2(g, playerNumber);
      } else if(playerNumber == 2){
         testPlayer2State2(g, playerNumber);
      } else {
         testPlayer3State2(g, playerNumber);
      }
      playerNumber++;
   }
   printf("Test Game State 2 passed!\n");
}

void testPlayer1State2 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 34);
   assert(getARCs(g, playerNumber) == 2);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 3);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   } 
   printf("test player 1 state 2 passed!\n");

}

void testPlayer2State2 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 34);
   assert(getARCs(g, playerNumber) == 2);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 3);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 2);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   } 
   printf("test player 2 state 2 passed!\n");

}

void testPlayer3State2 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 36);
   assert(getARCs(g, playerNumber) == 3);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 2);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   } 
   printf("test player 3 state 2 passed!\n");

}

void testGameState3(Game g){

   assert(getMostARCs(g) == UNI_C);   
   assert(getWhoseTurn(g) == UNI_A);
   
   int count = 0;
   char tempPath1[91] = {'\0'};
   char workingPath1[90] = WORKING_PATH;
   while(count<90){
      tempPath1[count] = workingPath1[count];
      if(count == 26 || count == 51 || count == 53){
         assert(getCampus(g, tempPath1) == CAMPUS_A);
         printf("testing campusA\n");
      } else if(count == 17 || count == 44 || count == 42){
         assert(getCampus(g, tempPath1) == CAMPUS_B);
         printf("testing campusB\n");
      } else if(count == 8 || count == 35){
         assert(getCampus(g, tempPath1) == CAMPUS_C);
         printf("testing campus C\n");
      } else {
         assert(getCampus(g, tempPath1) == VACANT_VERTEX);
         printf("testing vertex %d\n", count);
      } 
      count++;
   }
   
   count = 0;
   char tempPath2[91] = {'\0'};
   char workingPath2[90] = WORKING_PATH;
   while(count<90){
      tempPath2[count] = workingPath2[count];
      if(count == 51 || count == 52 || count == 53){
         assert(getARC(g, tempPath2) == ARC_A);
         printf("testing arc A\n");
      } else if(count == 44 || count == 43 || count == 42){
         assert(getARC(g, tempPath2) == ARC_B);
         printf("testing arc B\n");
      } else if(count == 8 || count == 6 || count == 7 || count == 58){
         assert(getARC(g, tempPath2) == ARC_C);
         printf("testing arc C\n");
      } else {
         assert(getARC(g, tempPath2) == VACANT_ARC);
         printf("testing arc %d\n", count);
      } 
      assert(getARC(g, tempPath2) == VACANT_ARC);
      count++;
   }
   
   assert(getMostPublications(g) == NO_ONE);
   assert(getTurnNumber(g) == 9);

   int playerNumber = 1;
   while (playerNumber <= 3){
      if(playerNumber ==1){
         testPlayer1State3(g, playerNumber);
      } else if(playerNumber == 2){
         testPlayer2State3(g, playerNumber);
      } else {
         testPlayer3State3(g, playerNumber);
      }
      playerNumber++;
   }
   printf("Test Game State 3 passed!\n");
}

void testPlayer1State3 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 34);
   assert(getARCs(g, playerNumber) == 2);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 3);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   } 
   printf("test player 1 state 3 passed!\n");

}

void testPlayer2State3 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 34);
   assert(getARCs(g, playerNumber) == 2);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 3);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 2);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }   
   printf("test player 2 state 3 passed!\n");

}

void testPlayer3State3 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 26);
   assert(getARCs(g, playerNumber) == 3);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 2);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 0);
   numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 3);
   numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         assert((getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)) == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }   
   printf("test player 3 state 3 passed!\n");

}
