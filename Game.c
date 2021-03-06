//Created by Josfer, Michael, Lachlan and Inura
//For COMP1917 Knowledge Island board game 2015 edition
//To simulate a board game with instructions included
//B? has been changed to BQN to prevent the special property of ? from happening
//Similarly M$ has been changed to MMONEY
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"

//NOTE: I have altered the #define to mirrors the ones in game.h

#define START_TURN_NUMBER -1
#define RETRAIN_COST 3
#define NUM_DISCIPLINES 6
#define ARCco 'A'
#define DIVISION 2
#define NUMBER_OF_DIRECTIONS 6

typedef unsigned long long numberof;
typedef int columntype;
typedef struct _board {
  columntype gameboard[21][11];
} board;
typedef struct _co_ordinate {
  int column;
  int row;
  int orientation;
  int valid;
  int isARC;
} co_ordinate;
typedef struct _player {
    numberof KPI;
    numberof Arc;
    numberof pubs;
    numberof campuses;
    numberof GOEs;
    numberof ips;
    numberof students[6];
    numberof retrain_BPS;
    numberof retrain_BQN;
    numberof retrain_MJ;
    numberof retrain_MTV;
    numberof retrain_MMONEY;
} Player;
typedef struct _game {
    int playerTurn;
    Player playerone;
    Player playertwo;
    Player playerthree;
    board gameboard;
    numberof GOE;
    unsigned char mostArc;
    unsigned char mostPub;
    int currentTurn;
    int dice[19];
    int disciplines[19];
    int ARCsCreated;
    int pubsCreated;

} game;

// Here are the movement functions written by Inura
// Game board representation using method though up by our group

//Prototypes
static int isLegalMovement ( co_ordinate position);
static co_ordinate moveDecoder (char* directions,char type);
static co_ordinate movement (co_ordinate position, char route);
static void studentGenerator (Game g, int regionID, int studentType);
static void studentAtRegion(Game g, int diceValue);
static void changeStudents (Game g, int playerNumber, int ThD, int BPS, int BQN, int MJ, int MTV, int MMONEY);
static void changeKPI (Game g, int KPI);
static void grandExchange(Game g, action a);
static void writeToBoard (Game g, path destination, int building, int type);
static void generateStudents (Game g, int start, int column, int studentType);





static void studentGenerator (Game g, int regionID, int studentType) {
    int start;
    int column;
    if(regionID == 0) {
        column = 0;
        start = 4;
    } else if (regionID == 1) {
        column = 0;
        start  = 8;
    } else if (regionID == 2) {
        column = 0;
        start = 12;
    } else if (regionID == 3) {
        column = 2;
        start = 2;
    } else if (regionID == 4) {
        column = 2;
        start = 6;
    } else if (regionID == 5) {
        column = 2;
        start = 10;
    } else if (regionID == 6) {
        column = 2;
        start = 14;
    } else if (regionID == 7) {
        column = 4;
        start = 0;
    } else if (regionID == 8) {
        column = 4;
        start = 4;
    } else if (regionID == 9) {
        column = 4;
        start = 8;
    } else if (regionID == 10) {
        column = 4;
        start = 12;
    } else if (regionID == 11) {
        column = 4;
        start = 16;
    } else if (regionID == 12) {
        column = 6;
        start = 2;
    } else if (regionID == 13) {
        column = 6;
        start = 6;
    } else if (regionID == 14) {
        column = 6;
        start = 10;
    } else if (regionID == 15) {
        column = 6;
        start = 14;
    } else if (regionID == 16) {
        column = 8;
        start = 4;
    } else if (regionID == 17) {
        column = 8;
        start = 8;
    } else if (regionID == 18) {
        column = 8;
        start = 12;
    }
    generateStudents (g, start, column, studentType);
}

static co_ordinate moveDecoder (char* directions,char type) {
   int counter = 0;
   char route;
   co_ordinate point = {0,4,0,TRUE,FALSE};
   if (type == ARCco){
      point.column = 5;
      point.row = 1;
      point.isARC = TRUE;
   }
   while ( (directions[counter] != 0) && (point.valid == TRUE)) {
      route = directions[counter];
      point = movement(point, route);
      point.valid = isLegalMovement (point);
      counter++;
   }
   return point;
}


static co_ordinate movement (co_ordinate position, char route){
  unsigned long long direction = (PATH_LIMIT * NUMBER_OF_DIRECTIONS);
  int turning;
  if (route == 'R') {
    turning = -2;
  } else if ( route == 'L') {
    turning = 2;
  } else {
    turning = 0;
  }
  int move = direction + turning + position.orientation;
  int travel = (move % 6);
  int rowMove = 0;
  int columnMove = 0;
  if (travel == 0){
    rowMove = -DIVISION;
  } else if (travel == 1) {
    columnMove = -DIVISION;
  } else if (travel == 2) {
    rowMove = DIVISION;
  } else if (travel == 3) {
    rowMove = DIVISION;
  } else if (travel == 4) {
    columnMove = DIVISION;
  } else if (travel == 5) {
    rowMove = -DIVISION;
  }
  /*
  if (position.isARC == FALSE){
    rowMove = 2*rowMove;
    columnMove = 2*columnMove;
  }
  */
  position.row += rowMove;
  position.column += columnMove;

  position.orientation = ((travel + (NUMBER_OF_DIRECTIONS/2)) % NUMBER_OF_DIRECTIONS);
  return position;
}

//movement is legal test
//FOr each row it means that if the number is greater than
//the elements in the row or less than zero then the action is illegal
static int isLegalMovement ( co_ordinate position) {
  int move = FALSE;
  if((position.column == 0) || (position.column == 10)){
    if((position.row >= 5) && (position.row <= 8)) {
    move = TRUE;
    }
  }
  if((position.column == 1) || (position.column == 9)){
    if((position.row >= 5 ) && (position.row <= 8)) {
    move = TRUE;
    }
  }
  if((position.column == 2) || (position.column == 8)){
    if((position.row >= 2) && (position.row < 10)) {
    move = TRUE;
    }
  }
  if((position.column == 3) || (position.column == 7)){
    if((position.row >= 2) && (position.row < 10)) {
    move = TRUE;
    }
  }
  if((position.column == 4) || (position.column == 8)){
    if((position.row >= 2) && (position.row < 10)) {
    move = TRUE;
    }
  }
  if((position.column == 5) || (position.column == 9)){
    if((position.row >= 2) && (position.row < 13)) {
    move = TRUE;
    }
  }
  if((position.column == 6) || (position.column == 8)){
    if((position.row > 0) && (position.row <= 13)) {
    move = TRUE;
    }
  }
  if((position.column == 7)){
    if((position.row >= 0) && (position.row <= 13)) {
    move = TRUE;
    }
  }
  return move;
}

// Here is the function Lachlan wrote
static void studentAtRegion(Game g, int diceValue){
   int students[19] = {0};
   int tempCount = 0;
   int count = 0;
   while (count < 19) {
      if(g->dice[count] == diceValue) {
         students[tempCount] = g->disciplines[count];
         tempCount++;
      }

      count++;
   }
   count = 0;
   int studentType;
   while ( count <= 19){
      studentType = students[count];
      studentGenerator (g, count, studentType);
      count++;
   }
}
//These are the prototypes for the functions that we have made for the project
static void changeStudents (Game g, int playerNumber, int ThD, int BPS, int BQN, int MJ, int MTV, int MMONEY){
   Player *temp;
   int gamer = getWhoseTurn(g);

   /* NOTE: We can use getWhoseTurn Function to determine whose turn [Michael] (commented IFs below)

   // enter 0 for playerNumber if this function is used during a player's turn
   // enter UNI_A, UNI_B, or UNI_C if used to update students when it is not their turn
   // ie. during throwDice
   if (playerNumber == NO_ONE){
      if ((g->currentTurn%3) == UNI_A){
         gamer = UNI_A;
      } else if ((g->currentTurn%3) == UNI_B){
         gamer = UNI_B;
      } else if ((g->currentTurn%3) == UNI_C){
         gamer = UNI_C;
      }
   }*/

   if (gamer == UNI_A){
      temp = &(g->playerone);
   } else if (gamer == UNI_B){
      temp = &(g->playertwo);
   } else if (gamer == UNI_C){
      temp = &(g->playerthree);
   }

   int studentCount = 0;
   int addStudent[NUM_DISCIPLINES] = {ThD,BPS,BQN,MJ,MTV,MMONEY};
   while(studentCount <= NUM_DISCIPLINES){
      temp->students[studentCount] = temp->students[studentCount] + addStudent[studentCount];
      studentCount++;
   }
}


static void changeKPI (Game g, int KPI){
   Player *temp;
   if (getWhoseTurn(g) == UNI_A){
      temp = &(g->playerone);
   } else if (getWhoseTurn(g) == UNI_B){
      temp = &(g->playertwo);
   } else if (getWhoseTurn(g) == UNI_C){
      temp = &(g->playerthree);
   }
   temp->KPI = temp->KPI + KPI;
}


static void grandExchange(Game g, action a){

   int disciplineFrom = a.disciplineFrom;
   int disciplineTo = a.disciplineTo;
   int rate = getExchangeRate(g,((g->currentTurn%3)),disciplineFrom,disciplineTo);

   if (disciplineFrom == STUDENT_BPS){
      changeStudents(g,0,0,rate,0,0,0,0);
   }else if (disciplineFrom == STUDENT_BQN){
      changeStudents(g,0,0,0,rate,0,0,0);
   }else if (disciplineFrom == STUDENT_MJ){
      changeStudents(g,0,0,0,0,rate,0,0);
   }else if (disciplineFrom == STUDENT_MTV){
      changeStudents(g,0,0,0,0,0,rate,0);
   }else if (disciplineFrom == STUDENT_MMONEY){
      changeStudents(g,0,0,0,0,0,0,rate);
   }

   if (disciplineTo == STUDENT_BPS){
      changeStudents(g,0,0,1,0,0,0,0);
   }else if (disciplineTo == STUDENT_BQN){
      changeStudents(g,0,0,0,1,0,0,0);
   }else if (disciplineTo == STUDENT_MJ){
      changeStudents(g,0,0,0,0,1,0,0);
   }else if (disciplineTo == STUDENT_MTV){
      changeStudents(g,0,0,0,0,0,1,0);
   }else if (disciplineTo == STUDENT_MMONEY){
      changeStudents(g,0,0,0,0,0,0,1);
   }
}

//These are functions that are part of the prototype provided in game.h
//They are need to have the same inputs and outputs

static void writeToBoard (Game g, path destination, int building, int type){
   co_ordinate point;
   point = moveDecoder(destination, type);
   g->gameboard.gameboard[point.row][point.column] = building;
}

static void generateStudents (Game g, int start, int column, int studentType){
    int campus;
    int counter = start;
    int THD = 0;
    int BPS = 0;
    int BQN = 0;
    int MJ  = 0;
    int MTV = 0;
    int MMONEY = 0;
    if (studentType == STUDENT_THD) {
        THD = 1;
    } else if (studentType == STUDENT_BPS){
        BPS = 1;
    } else if (studentType == STUDENT_BQN){
        BQN = 1;
    } else if (studentType == STUDENT_MJ){
        MJ = 1;
    } else if (studentType == STUDENT_MTV){
        MTV = 1;
    } else if (studentType == STUDENT_MMONEY){
        MMONEY = 1;
    }
    while(counter < (start + 4)){
        campus = g->gameboard.gameboard[counter][column];
        if(campus > 0) {
            if(campus == CAMPUS_A){
                changeStudents( g, UNI_A, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == CAMPUS_B){
                changeStudents( g, UNI_B, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == CAMPUS_C){
                changeStudents( g, UNI_C, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == GO8_A){
                changeStudents( g, UNI_A, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            } else if ( campus == GO8_B){
                changeStudents( g, UNI_B, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }else if ( campus == GO8_C){
                changeStudents( g, UNI_C, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }
        }
        counter += 2;
    }
    counter = 0;
    while(counter < (start + 4)){
        campus = g->gameboard.gameboard[counter][column+2];
        if(campus > 0) {
            if(campus == CAMPUS_A){
                changeStudents( g, UNI_A, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == CAMPUS_B){
                changeStudents( g, UNI_B, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == CAMPUS_C){
                changeStudents( g, UNI_C, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == GO8_A){
                changeStudents( g, UNI_A, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            } else if ( campus == GO8_B){
                changeStudents( g, UNI_B, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }else if ( campus == GO8_C){
                changeStudents( g, UNI_C, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }
        }
        counter += 2;
    }
}


Game newGame (int discipline[], int dice[]){
    Game g = (Game) malloc(sizeof(Game));
    int counter = 0;
    if( g != NULL){
        g->playerTurn = NO_ONE;
        g->GOE = 0;
        g->mostArc = NO_ONE;
        g->mostPub = NO_ONE;
        g->currentTurn = -1;


        while(counter < 3){
            Player* temp;
            if (counter == 0){
                temp = &(g->playerone);
            } else if (counter == 1){
                temp = &(g->playertwo);
            } else if (counter == 2){
            temp = &(g->playerthree);
            }
            temp->KPI = 20;
            temp->Arc=0;
            temp->pubs=0;
            temp->campuses=2;
            temp->GOEs=0;
            temp->ips=0;
            temp->students[0] = 0;
            temp->students[1] = 3;
            temp->students[2] = 3;
            temp->students[3] = 1;
            temp->students[4] = 1;
            temp->students[5] = 1;
            temp->retrain_BPS=3;
            temp->retrain_BQN=3;
            temp->retrain_MJ=3;
            temp->retrain_MTV=3;
            temp->retrain_MMONEY=3;
            counter++;
        }
        counter = 0;
        while ( counter < 19 ){
            g->dice[counter] = dice[counter];
            counter ++;
        }

        counter = 0;
        while (counter < 19){
            g->disciplines[counter] = discipline[counter];
            counter++;
        }
    }
    return g;
}

void disposeGame (Game g){
    free (g);
    assert(g == NULL);
}

void makeAction (Game g, action a){
    /*player *temp = {0}; */
    int turn = getWhoseTurn(g);
    /*
    if (turn == UNI_A){
        temp = &(g->playerone);
    } else if (turn == UNI_B){
        temp = &(g->playertwo);
    } else if (turn == UNI_C){
        temp = &(g->playerthree);
    } */

    if(isLegalAction(g,a) == TRUE){
       if(turn == UNI_A){
          if ( a.actionCode == PASS){
              //DO nothing as they have passed their turn
          } else if (a.actionCode == BUILD_CAMPUS){
              //This builds a campus at the price of
              // 1 BPS, 1 B?, 1 MJ , 1 MTV
              changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
              changeKPI(g, 10);
              writeToBoard(g,a.destination,CAMPUS_A, 0);
          } else if (a.actionCode == BUILD_GO8) {
              //USE up two MJ and 3 MS
              changeStudents(g, 0, 0, 0, 0, -2, 0, -3);
              changeKPI(g, 10);
              writeToBoard(g,a.destination,GO8_A, 0);
          } else if (a.actionCode == OBTAIN_ARC) {
              changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
              changeKPI(g, 10);
              writeToBoard(g,a.destination,ARC_A, 'A');
              g->ARCsCreated++;
          } else if (a.actionCode == START_SPINOFF) {
              //DO Nothing as this is an unexpected output
          } else if (a.actionCode == OBTAIN_PUBLICATION) {
              changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
              g->pubsCreated++;
          } else if (a.actionCode == OBTAIN_IP_PATENT) {
              changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
              changeKPI(g, 10);
          } else if (a.actionCode == RETRAIN_STUDENTS) {
              grandExchange(g, a);
          }
       }else if(turn == UNI_B){
           if ( a.actionCode == PASS){
               //DO nothing as they have passed their turn
           } else if (a.actionCode == BUILD_CAMPUS){
               //This builds a campus at the price of
               // 1 BPS, 1 B?, 1 MJ , 1 MTV
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,CAMPUS_B, 0);
           } else if (a.actionCode == BUILD_GO8) {
               //USE up two MJ and 3 MS
               changeStudents(g, 0, 0, 0, 0, -2, 0, -3);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,GO8_B,0);
           } else if (a.actionCode == OBTAIN_ARC) {
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,ARC_B,'A');
               g->ARCsCreated++;
           } else if (a.actionCode == START_SPINOFF) {
               //DO Nothing as this is an unexpected output
           } else if (a.actionCode == OBTAIN_PUBLICATION) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               g->pubsCreated++;
           } else if (a.actionCode == OBTAIN_IP_PATENT) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               changeKPI(g, 10);
           } else if (a.actionCode == RETRAIN_STUDENTS) {
               grandExchange(g, a);
           }
       }else if(turn == UNI_C){
           if ( a.actionCode == PASS) {
               //DO nothing as they have passed their turn
           } else if (a.actionCode == BUILD_CAMPUS){
               //This builds a campus at the price of
               // 1 BPS, 1 B?, 1 MJ , 1 MTV
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,CAMPUS_C,0);
           } else if (a.actionCode == BUILD_GO8) {
               //USE up two MJ and 3 MS
               changeStudents(g, 0, 0, 0, 0, -2, 0, -3);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,GO8_C,0);
           } else if (a.actionCode == OBTAIN_ARC) {
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,ARC_C,'A');
               g->ARCsCreated++;
           } else if (a.actionCode == START_SPINOFF) {
               //DO Nothing as this is an unexpected output
           } else if (a.actionCode == OBTAIN_PUBLICATION) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               g->pubsCreated++;
           } else if (a.actionCode == OBTAIN_IP_PATENT) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               changeKPI(g, 10);
           } else if (a.actionCode == RETRAIN_STUDENTS) {
               grandExchange(g, a);
           }
       }

}
}

void throwDice (Game g, int diceScore){
    studentAtRegion(g, diceScore);
    //Below lies an attempt to hard code the retraining centres
    /*Player* temp;
    if (player == UNI_A){
        temp = &(g->playerone);
    } else if (player == UNI_B){
        temp = &(g->playertwo);
    } else if (player == UNI_C){
        temp = &(g->playerthree);
    }
    int campus;
    int vertcounter = 0;
    int horicounter = 0;
    while (horicounter < 21){
        while(vertcounter < 11){
            campus = g->gameboard.gameboard[vertcounter][horicounter];
            if((vertcounter == 2)||(vertcounter == 4)){
                if(horicounter == 2){

                }
            }
        }
    }*/
   g->currentTurn++;
}

//part of throwDice by Josfer
/*static int diceToRegionID( Game g, int diceScore){
   int counter = 0;
   while((g->dice[counter]!=diceScore)&&(counter<19)){
      counter++;
   }
   return counter;
}*/

/*static int studentAtRegion(game g, int regionID){

   int students[19] = {0};
   int tempCount = 0;
   int count = 0;
   while (count < 19) {
      if(g->dice[count] == diceValue) {
         students[tempCount] = discipline[count];
         tempCount++;
      }
      count++;
   }*/

//part of throwDice by Josfer
/*static int regionIDToStudent(Game g, int regionID){
   int student= disciplines[regionID];
   return student;
}*/

int getDiscipline (Game g, int regionID){
    int discipline = g->disciplines[regionID];
    return discipline;
}

int getDiceValue (Game g, int regionID){
    int defaultDice = g->dice[regionID];
    return defaultDice;
}

int getMostARCs(Game g){
    int ID = NO_ONE;
        if((g->playerone.Arc > g->playertwo.Arc) && (g->playerone.Arc > g->playerthree.Arc)){
            ID = UNI_A;
        } else if((g->playertwo.Arc > g->playerone.Arc) && (g->playertwo.Arc > g->playerthree.Arc)){
            ID = UNI_B;
        } else if((g->playerone.Arc > g->playertwo.Arc) && (g->playerone.Arc > g->playerthree.Arc)){
            ID = UNI_C;
        }
        printf("The highest arcs is %d",ID);
    return ID;

}

int getMostPublications(Game g){
    int ID = NO_ONE;
        if((g->playerone.pubs > g->playertwo.pubs) && (g->playerone.pubs > g->playerthree.pubs)){
            ID = UNI_A;
        } else if((g->playertwo.pubs > g->playerone.pubs) && (g->playertwo.pubs > g->playerthree.pubs)){
            ID = UNI_B;
        } else if((g->playerone.pubs > g->playertwo.pubs) && (g->playerone.pubs > g->playerthree.pubs)){
            ID = UNI_C;
        }
    return ID;
}

int getTurnNumber (Game g){
    int turnNumber = 0;
    turnNumber = g->currentTurn;
    return turnNumber;
}

int getWhoseTurn (Game g){
    int ID = NO_ONE;
    if (g->currentTurn % 3 == 0){
        ID = UNI_A;
    } else if (g->currentTurn % 3 == 1){
        ID = UNI_B;
    } else if (g->currentTurn % 3 == 2){
        ID = UNI_C;
    }
    return ID;
}

int getCampus (Game g, path pathToVortex){
    co_ordinate point;
    point = moveDecoder (pathToVortex, 7);
    int campus = g->gameboard.gameboard[point.row][point.column];
    return campus;
}

int getARC (Game g, path pathToEdge){
    co_ordinate point;
    point = moveDecoder (pathToEdge, 7);
    int arc = g->gameboard.gameboard[point.row][point.column];
    return arc;
}

int isLegalAction (Game g, action a){
    return FALSE;
}


int getKPIpoints(Game g, int player){
    int KPI = 0;
    if (player == 1) {
        KPI = g->playerone.KPI;
    } else if (player == 2) {
        KPI = g->playertwo.KPI;
    } else if (player == 3) {
        KPI = g->playerthree.KPI;
    }
    return KPI;
}

int getARCs (Game g, int player){
    int Arcs = 0;
    if (player == 1) {
        Arcs = g->playerone.Arc;
    } else if (player == 2) {
        Arcs = g->playertwo.Arc;
    } else if (player == 3) {
        Arcs = g->playerthree.Arc;
    }
    return Arcs;
}

int getGO8s (Game g, int player){
    int GOE = 0;
    if (player == 1) {
        GOE = g->playerone.GOEs;
    } else if (player == 2) {
        GOE = g->playertwo.GOEs;
    } else if (player == 3) {
        GOE = g->playerthree.GOEs;
    }
    return GOE;
}

int getCampuses (Game g, int player){
    int campus = 0;
    if (player == 1) {
        campus = g->playerone.campuses;
    } else if (player == 2) {
        campus = g->playertwo.campuses;
    } else if (player == 3) {
        campus = g->playerthree.campuses;
    }
    return campus;
}

int getIPs (Game g, int player){
    int IP = 0;
    if (player == 1) {
        IP = g->playerone.ips;
    } else if (player == 2) {
        IP = g->playertwo.ips;
    } else if (player == 3) {
        IP = g->playerthree.ips;
    }
    return IP;
}

int getPublications (Game g, int player){
    int pubs = 0;
    if (player == 1) {
        pubs = g->playerone.pubs;
    } else if (player == 2) {
        pubs = g->playertwo.pubs;
    } else if (player == 3) {
        pubs = g->playerthree.pubs;
    }
    return pubs;
}

int getStudents (Game g, int player, int discipline){
    Player* temp;
    int studentnum = 0;
    if (player == UNI_A){
        temp = &(g->playerone);
    } else if (player == UNI_B){
        temp = &(g->playertwo);
    } else if (player == UNI_C){
        temp = &(g->playerthree);
    }
    if (discipline == STUDENT_THD) {
        studentnum = temp->students[0];
    } else if (discipline == STUDENT_BPS){
        studentnum = temp->students[1];
    } else if (discipline == STUDENT_BQN) {
        studentnum = temp->students[2];
    } else if (discipline == STUDENT_MJ) {
        studentnum = temp->students[3];
    } else if (discipline == STUDENT_MTV) {
        studentnum = temp->students[4];
    } else if (discipline == STUDENT_MMONEY) {
        studentnum = temp->students[5];
    }
    return studentnum;
}

int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo){
    int exchangeRate = 0;
    Player * temp = NULL;
    if (player == UNI_A){
        temp = &(g->playerone);
    } else if (player == UNI_B){
        temp = &(g->playertwo);
    } else if (player == UNI_B){
        temp = &(g->playerthree);
    }
    if (disciplineFrom == STUDENT_BPS){
        exchangeRate =  temp->retrain_BPS;
    } else if (disciplineFrom == STUDENT_BQN) {
        exchangeRate = temp->retrain_BQN;
    } else if (disciplineFrom == STUDENT_MJ) {
        exchangeRate = temp->retrain_MJ;
    } else if (disciplineFrom == STUDENT_MTV) {
        exchangeRate = temp->retrain_MTV;
    } else if (disciplineFrom == STUDENT_MMONEY) {
        exchangeRate = temp->retrain_MMONEY;
    }
    return exchangeRate;
}
