#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_UNIS 3
#define TERRA_NULLIUS -1
 
// player ID of each university
#define NO_ONE 0
#define UNI_A 1
#define UNI_B 2
#define UNI_C 3
 
// contents of an ARC
#define VACANT_ARC 0
#define ARC_A 1
#define ARC_B 2
#define ARC_C 3
 
// contents of a VERTEX
#define VACANT_VERTEX 0  
#define CAMPUS_A 1
#define CAMPUS_B 2
#define CAMPUS_C 3
#define GO8_A 4
#define GO8_B 5
#define GO8_C 6
 
// action codes
#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_PATENT 6
#define RETRAIN_STUDENTS 7

// disciplines
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5
 
#define NUM_REGIONS 19
#define PATH_LIMIT 150
 
#define TRUE 1
#define FALSE 0
#define WORKING_PATH {'L','R','R','1B','R','R','R','2B','R','R','R','R','3B','R','R','R','4B','R','R','R','R','5B','R','R','R','6B','R','R','R','R','7B','R','R','R','8B','R','R','R','R','9B','R','R','R','10B','R','R','R','R','11B','R','R','L','12B','R','R','R','R','13B','R','R','R','R','14B','R','R','R','R','15B','R','R','R','R','16B','R','R','R','R','17B','R','R','R','L','18B','R','R','R','R','R','R','R'}
 
typedef struct _game * Game;
typedef char path[PATH_LIMIT];
typedef struct _action {
   int actionCode;  // see #defines above
   path destination; // if the action operates on a vertex or ARC this
                     // specifies *which* vertex or path.  unused 
                     // otherwise
   int disciplineFrom;  // used for the retrain students action
   int disciplineTo;    // used for the retrain students action
} action;

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

void testGameState0 (Game g);
void testPlayerState0 (Game g, int playerNumber);
void testGameState1 (Game g);
void testPlayer1State1 (Game g, int playerNumber);
void testPlaye2State1 (Game g, int playerNumber);
void testPlayer3State1 (Game g, int playerNumber);
void testGameState2(Game g);
void testPlayer1State2 (Game g, int playerNumber);
void testPlaye2State2 (Game g, int playerNumber);
void testPlayer3State2 (Game g, int playerNumber);

int main (int argc, char *argv[]) {

   int disciplines[] = {DEFAULT_DISCIPLINES};
   int dice[] = {DEFAULT_DICE};

   Game g = newGame(disciplines, dice);
   
   action p1 = {PASS,0,0,0};
   action p2 = {PASS,0,0,0};
   action p3 = {PASS,0,0,0};
   

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
   
   p1={OBTAIN_ARC,[R],0,0};
   makeAction(g, p1);
   p1={OBTAIN_ARC,[RR],0,0};
   makeAction(g, p1);
   p1={BUILD_CAMPUS,[RR],0,0};
   makeAction(g, p1);
   p1={PASS,0,0,0};
   makeAction(g, p1);
   throwDice(g, 9);
   
   p2={OBTAIN_ARC,[RRLRLL],0,0};
   makeAction(g, p2);
   p2={OBTAIN_ARC,[RRLRLLL],0,0};
   makeAction(g, p2);
   p2.actionCode=BUILD_CAMPUS;
   makeAction(g, p2);
   p2.actionCode=PASS;
   makeAction(g, p2);
   throwDICE(g, 7);
   
   p3={OBTAIN_ARC,[LRLRLB],0,0};
   makeAction(g, p3);
   p3.destination=[LRLRR];
   makeAction(g, p3);
   p3.destination=[LRLRRR];
   makeAction(g, p3);
   p3.actionCode=PASS;
   makeAction(g, p3);
   throwDice(g, 8);
   
   testGameState2(g);

   disposeGame(g);        
   
   printf("All tests passed!\n You are awesome!!\n");

   return EXIT_SUCCESS;
}

//tests the state of the game at Terra Nullis
void testGameState0(Game g){

   assert(getMostARCs(g) == NO_ONE);   
   assert(getWhoseTurn(g) == NO_ONE);
   
   int count = 0;
   char tempPath[90] = {'\0'};
   char workingPath[90] = WORKING_PATH;
   while(count<90){
      tempPath[count] == workingPath[count];
      if(count == 27 || count == 54){
         assert(getCampus(g, tempPath) == CAMPUS_A);
      } else if(count == 18 || count == 45){
         assert(getCampus(g, tempPath) == CAMPUS_B);
      } else if(count == 9 || count == 36){
         assert(getCampus(g, tempPath) == CAMPUS_C);
      } else {
         assert(getCampus(g, tempPath) == VACANT_VERTEX);
      } 
      count++;
   }
   
   int count = 0;
   char tempPath[90] = {'\0'};
   char workingPath[90] = WORKING_PATH;
   while(count<90){
      tempPath[count] == workingPath[count];
      assert(getArc(g, tempPath) == VACANT_ARC);
      count++;
   }
   
   assert(getMostPublications(g) == NO_ONE);
   assert(getTurnNumber(g) == TERRA_NULLIUS)

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
   int numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   }
   
   int exchangeRate = 0;
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)
         assert(exchangeRate == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }   
   printf("test player state 0 passed!\n");

}

void testGameState1(Game g){
   
   assert(getMostARCs(g) == NO_ONE);   
   assert(getWhoseTurn(g) == UNI_A);
   
   int count = 0;
   char tempPath[90] = {'\0'};
   char workingPath[90] = WORKING_PATH;
   while(count<90){
      tempPath[count] == workingPath[count];
      if(count == 27 || count == 54){
         assert(getCampus(g, tempPath) == CAMPUS_A);
      } else if(count == 18 || count == 45){
         assert(getCampus(g, tempPath) == CAMPUS_B);
      } else if(count == 9 || count == 36){
         assert(getCampus(g, tempPath) == CAMPUS_C);
      } else {
         assert(getCampus(g, tempPath) == VACANT_VERTEX);
      } 
      count++;
   }
   
   int count = 0;
   char tempPath[90] = {'\0'};
   char workingPath[90] = WORKING_PATH;
   while(count<90){
      tempPath[count] == workingPath[count];
      assert(getArc(g, tempPath) == VACANT_ARC);
      count++;
   }
   
   assert(getMostPublications(g) == NO_ONE);
   assert(getTurnNumber(g) == 3);

   int playerNumber = 1;
   while (playerNumber <= 3){
      if(playerNumber =1){
         testPlayer1State1(g, playerNumber);
      } else if{playerNumber = 2){
         testPlayer2State1(g, playerNumber);
      } else {
         testPlayer3State1(g, playerNumber);
      }
      playerNumber++;
   }
   printf("Test Game State 0 passed!\n");
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
   int numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   }
   
   int exchangeRate = 0;
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo);
         assert(exchangeRate == 3);
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
   int numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 5);
   int numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   }
   
   int exchangeRate = 0;
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo);
         assert(exchangeRate == 3);
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
   int numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 2);
   int numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 2);
   int numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 1);
   }
   
   int exchangeRate = 0;
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo);
         assert(exchangeRate == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }   
   printf("test player 3 state 1 passed!\n");

}

void testGameState2(Game g);

   assert(getMostARCs(g) == UNI_C);   
   assert(getWhoseTurn(g) == UNI_A);
   
   int count = 0;
   char tempPath[90] = {'\0'};
   char workingPath[90] = WORKING_PATH;
   while(count<90){
      tempPath[count] == workingPath[count];
      if(count == 27 || count == 52 || count == 54){
         assert(getCampus(g, tempPath) == CAMPUS_A);
      } else if(count == 18 || count == 45 || count == 43){
         assert(getCampus(g, tempPath) == CAMPUS_B);
      } else if(count == 9 || count == 36){
         assert(getCampus(g, tempPath) == CAMPUS_C);
      } else {
         assert(getCampus(g, tempPath) == VACANT_VERTEX);
      } 
      count++;
   }
   
   int count = 0;
   char tempPath[90] = {'\0'};
   char workingPath[90] = WORKING_PATH;
   while(count<90){
      tempPath[count] == workingPath[count];
      if(count == 52 || count == 53 || count == 54){
         assert(getCampus(g, tempPath) == CAMPUS_A);
      } else if(count == 18 || count == 45 || count == 44 || count == 43){
         assert(getCampus(g, tempPath) == CAMPUS_B);
      } else if(count == 9 || count == 7 || count == 8 || count == 57){
         assert(getCampus(g, tempPath) == CAMPUS_C);
      } else {
         assert(getCampus(g, tempPath) == VACANT_VERTEX);
      } 
      assert(getArc(g, tempPath) == VACANT_ARC);
      count++;
   }
   
   assert(getMostPublications(g) == NO_ONE);
   assert(getTurnNumber(g) == 6)

   int playerNumber = 1;
   while (playerNumber <= 3){
      if(playerNumber =1){
         testPlayer1State1(g, playerNumber);
      } else if{playerNumber = 2){
         testPlayer2State1(g, playerNumber);
      } else {
         testPlayer3State1(g, playerNumber);
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
   int numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 0);
   int numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 0);
   int numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 0);
   int numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 0);
   int numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   }
   
   int exchangeRate = 0;
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo);
         assert(exchangeRate == 3);
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
   int numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 2);
   int numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 0);
   int numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 0);
   int numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   }
   
   int exchangeRate = 0;
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo);
         assert(exchangeRate == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }   
   printf("test player 2 state 2 passed!\n");

}

void testPlayer3State2 (Game g, int playerNumber){

   assert(getKPIpoints(g, playerNumber) == 26);
   assert(getARCs(g, playerNumber) == 3);
   assert(getGO8s(g, playerNumber) == 0);
   assert(getCampuses(g, playerNumber) == 2);
   assert(getIPs(g, playerNumber) == 0);
   assert(getPublications(g, playerNumber) == 0);
   
   int numStudents = getStudents(g, playerNumber, STUDENT_THD);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_BPS);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_BQN);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_MJ);
   assert (numStudents == 3);
   int numStudents = getStudents(g, playerNumber, STUDENT_MTV);
   assert (numStudents == 1);
   int numStudents = getStudents(g, playerNumber, STUDENT_MMONEY);
   assert (numStudents == 0);
   }
   
   int exchangeRate = 0;
   int disciplineFrom = STUDENT_BPS;
   int disciplineTo = STUDENT_BPS;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo);
         assert(exchangeRate == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_BPS;
   disciplineFrom++;
   }   
   printf("test player 3 state 2 passed!\n");

}
