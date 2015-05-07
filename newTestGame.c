//testGame.c

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

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

void testGameState0 (Game g);
void testPlayerState0 (Game g, int playerNumber);
int rollDice(int request);

int main (int argc, char *argv[]) {

   int disciplines[] = {DEFAULT_DISCIPLINES};
   int dice[] = {DEFAULT_DICE};

   Game g = newGame(disciplines, dice);

   /*int diceScore = 0;
   int request = 4;
   diceScore = rollDice(request);*/
   
   action a;

   testGameState0(g);
   throwDice(g, diceScore); //can just enter a number between 2-12, so if u want to test if the first dice roll was 5
                            // type in 5 instead of diceScore
   makeAction(g,a);         
   
   printf("All tests passed!\n You are awesome!!\n");

   return EXIT_SUCCESS;
}

//tests the state of the game at Terra Nullis
void testGameState0(Game g){

   int mostARCs = 0;
   mostARCs = getMostARCs(g);
   assert(mostARCs == NO_ONE);   
   
   int whoseTurn = 0;
   whoseTurn = getWhoseTurn(g);
   assert(whoseTurn == NO_ONE);
   
   int campus = 0;
   campus = getCampus(g);
   assert(campus == 2);
   
   int arc = 0;
   arc = getArc(g);
   assert(arc == VACANT_ARC);
   
   int mostPub = 0;
   mostPub = getMostPublications(g);
   assert(mostPub == NO_ONE);

   int currentTurn = 0;
   currentTurn = getTurnNumber(g);
   assert (currentTurn == TERRA_NULLIUS);

   while (playerNumber <= 3){
      testPlayerState(g, playerNumber);
      playerNumber++;
   }
   printf("Test Game State 0 passed!\n");
}

//test state of the player at Terra Nullis
void testPlayerState0 (Game g, int playerNumber){

   int KPIpoints = 0;
   KPIpoints = getKPIpoints(g, playerNumber);
   assert(KPIpoints == 20);
   
   int ARCS = 0;
   ARCs = getARCs(g, playerNumber);
   assert(ARCs == 0);
  
   int GO8s = 0;
   GO8s = getGO8s(g, playerNumber);
   assert(GO8s == 0);
   
   int campuses = 0;
   campuses = getCampuses(g, playerNumber);
   assert(campuses == 2);
  
   int IPs = 0;
   IPs = getIPs(g, playerNumber);
   assert(IPs == 0);
   
   int pub = 0;
   pub = getPublications(g, playerNumber);
   assert(pub == 0);
   
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
   int disciplineFrom = STUDENT_THD;
   int disciplineTo = STUDENT_THD;
   while (disciplineFrom <= STUDENT_MMONEY){
      while(disciplineTo <= STUDENT_MMONEY){
         exchangeRate = getExchangeRate(g, playerNumber, disciplineFrom, disciplineTo)
         assert(exchangeRate == 3);
         disciplineTo++;
      }
   disciplineTo = STUDENT_THD;
   disciplineFrom++;
   }   
   printf("test player state 0 passed!\n");

}

int rollDice(int request){
   int value = 0;
   int diceOutcomes[12]={1,2,3,4,5,6,7,8,9,10,11,12}
   value = diceOutcomes[request-1];
   return value;
}
