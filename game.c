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
} player;
typedef struct _game {
    //int playerTurn = NO_ONE;
    player playerone;
    player playertwo;
    player playerthree;
    board gameboard;
    numberof GOE;
    unsigned char mostArc;
    unsigned char mostPub;
    int currentTurn;
    
    int dice[19];
    int disciplines[19];
    
    int pubsCreated; // To count pubs created for getMostPublications
    int ARCsCreated; // same as above but for ARCs.
} Game;

// Here are the movement functions written by Inura
// Game board representation using method though up by our group

//Prototypes 
int islegalmovement ( co_ordinate position);
co_ordinate movedecoder (char* directions,char type);
co_ordinate movement (co_ordinate position, char route);
void studentgenerator (int regionID);

static void studentgenerator (Game g, int regionID, int studentType) {
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

static co_ordinate movedecoder (char* directions,char type) {
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
      point.valid = islegalmovement (point);
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
static int islegalmovement ( co_ordinate position) {
  int move = FALSE;
  if((position.column == 0) || (position.column == 10)){
    if((position.row >= 5) && (postion.row <= 8)) {
    move = TRUE;
    }
  }
  if((postion.column == 1) || (position.column == 9)){
    if((position.row >= 5 ) && (postion.row <= 8)) {
    move = TRUE;
    }
  }
  if((postion.column == 2) || (position.column == 8)){
    if((position.row >= 2) && (postion.row < 10)) {
    move = TRUE;
    }
  }
  if((postion.column == 3) || (position.column == 7)){
    if((position.row >= 2) && (postion.row < 10)) {
    move = TRUE;
    }
  }
  if((postion.column == 4) || (position.column == 8)){
    if((position.row >= 2) && (postion.row < 10)) {
    move = TRUE;
    }
  }
  if((postion.column == 5) || (position.column == 9)){
    if((position.row >= 2) && (postion.row < 13)) {
    move = TRUE;
    }
  }
  if((postion.column == 6) || (position.column == 8)){
    if((position.row > 0) && (postion.row <= 13)) {
    move = TRUE;
    }
  }
  if((postion.column == 7)){
    if((position.row >= 0) && (postion.row <= 13)) {
    move = TRUE;
    }
  }
  return move;
}

// Here is the function Lachlan wrote
void studentAtRegion(Game g){
   int students[19] = {0};
   int tempCount = 0;
   int count = 0;
   while (count < 19) {
      if(g->dice[count] == diceValue) {
         students[tempCount] = discipline[count];
         tempCount++;
      }
      
      count++;
   }
   count = 0;
   int studentType; 
   while ( count <= 19){
      studentType = students[counter];
      studentgenerator (g, count, studentType);
      counter++;
   }
}
//These are the prototypes for the functions that we have made for the project
static void changeStudents (Game g, player playerNumber, int ThD, int BPS, int BQN, int MJ, int MTV, int MMONEY){
   player *temp = {0};

   if(playerNumber == NO_ONE){
      if (g->playerTurn == UNI_A){
         playerNumber = UNI_A;
      } else if (g->playerTurn == UNI_B){
         playerNumber = UNI_B;
      } else if (g->playerTurn == UNI_C){
         playerNuber = UNI_C;
      }
   } 
   if (playerNumber == UNI_A){
      temp = g->playerone;
   } else if (playerNumber == UNI_B){
      temp = g->playertwo;
   } else if (playerNumber == UNI_C){
      temp = g->playerthree;
   }

   int studentCount = 0;
   int addStudent[NUM_DISCIPLINES] = {ThD,BPS,BQN,MJ,MTV,MMONEY};
   while(studentCount <= NUM_DISCIPLINES){
      temp.student[studentCount] == temp.student[studentCount] + addStudent[studentCount];
      studentCount++;
   }
}
    
   /* Alternative form:
    
    if(getWhoseTurn == UNI_A){
       g.playerone.ThD = g.playerone.ThD + ThD;
       g.playerone.BPS = g.playerone.BPS + BPS;
       g.playerone.MJ = g.playerone.MJ + MJ;
       g.playerone.MTV = g.playerone.MTV + MTV;
       g.playerone.MMONEY = g.playerone.MMONEY + MMONEY;
    } else if(getWhoseTurn == UNI_B){
       g.playertwo.ThD = g.playertwo.ThD + ThD;
       g.playertwo.BPS = g.playertwo.BPS + BPS;
       g.playertwo.MJ = g.playertwo.MJ + MJ;
       g.playertwo.MTV = g.playertwo.MTV + MTV;
       g.playertwo.MMONEY = g.playertwo.MMONEY + MMONEY;
    }else if(getWhoseTurn == UNI_C){
       g.playerthree.ThD = g.playerthree.ThD + ThD;
       g.playerthree.BPS = g.playerthree.BPS + BPS;
       g.playerthree.MJ = g.playerthree.MJ + MJ;
       g.playerthree.MTV = g.playerthree.MTV + MTV;
       g.playerthree.MMONEY = g.playerthree.MMONEY + MMONEY;
    
    
}*/
static void changeKPI (Game g, int KPI){
   player *temp = {0};
   if (getWhoseTurn(g) == UNI_A){
      temp = g->playerone;
   } else if (getWhoseTurn(g) == UNI_B){
      temp = g->playertwo;
   } else if (getWhoseTurn(g) == UNI_C){
      temp = g->playerthree;
   }
   temp.KPI = temp.KPI + KPI;
    
   /* Alternative Form:
    
    if(getWhoseTurn == UNI_A){
       g.playerone.KPI = g.playerone.KPI + KPI;
    } else if(getWhoseTurn == UNI_B){
       g.playertwo.KPI = g.playertwo.KPI + KPI;
    } else if(getWhoseTurn == UNI_C){
       g.playerthree.KPI = g.playerthree.KPI + KPI;
    }
    
    */
}

static void grandExchange(Game g, action a){
    
   int disciplineFrom = a.disciplineFrom;
   int disciplineTo = a.disciplineTo;
   int rate = getExchangeRate(g,temp,disciplineFrom,disciplineTo);
   
   if (disciplineFrom = STUDENT_BPS){
      changeStudents(g,0,0,rate,0,0,0,0);
   }else if (disciplineFrom = STUDENT_BQN){
      changeStudents(g,0,0,0,rate,0,0,0);
   }else if (disciplineFrom = STUDENT_MJ){
      changeStudents(g,0,0,0,0,rate,0,0);
   }else if (disciplineFrom = STUDENT_MTV){
      changeStudents(g,0,0,0,0,0,rate,0);
   }else if (disciplineFrom = STUDENT_MMONEY){
      changeStudents(g,0,0,0,0,0,0,rate);
   }
   
   if (disciplineTo = STUDENT_BPS){
      changeStudents(g,0,0,1,0,0,0,0);
   }else if (disciplineTo = STUDENT_BQN){
      changeStudents(g,0,0,0,1,0,0,0);
   }else if (disciplineTo = STUDENT_MJ){
      changeStudents(g,0,0,0,0,1,0,0);
   }else if (disciplineTo = STUDENT_MTV){
      changeStudents(g,0,0,0,0,0,1,0);
   }else if (disciplineTo = STUDENT_MMONEY){
      changeStudents(g,0,0,0,0,0,0,1);
   }
}

//These are functions that are part of the prototype provided in game.h
//They are need to have the same inputs and outputs

static void writeToBoard (Game g, path destination, int building){
   co_ordinate point = movedecoder(destination, type);
   g->gameboard[point.row][point.column] = building;
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
    while(counter < (start + 4){
        campus = g->gameboard[counter][column];
        if(campus > 0) {
            if(campus == CAMPUS_A){
                changeStudents( g, PLAYER_A, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == CAMPUS_B){
                changeStudents( g, PLAYER_B, THD, BPS, BQN, MJ,  MTV, MMONEY)
            } else if ( campus == CAMPUS_C){
                changeStudents( g, PLAYER_C, THD, BPS, BQN, MJ,  MTV, MMONEY)
            } else if ( campus == GO8_A){
                changeStudents( g, PLAYER_A, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            } else if ( campus == GO8_B){
                changeStudents( g, PLAYER_B, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }else if ( campus == GO8_C){
                changeStudents( g, PLAYER_C, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }
        }
        counter += 2;
    }
    counter = 0;
    while(counter < (start + 4){
        campus = g->gameboard[counter][column+2];
        if(campus > 0) {
            if(campus == CAMPUS_A){
                changeStudents( g, PLAYER_A, THD, BPS, BQN, MJ,  MTV, MMONEY);
            } else if ( campus == CAMPUS_B){
                changeStudents( g, PLAYER_B, THD, BPS, BQN, MJ,  MTV, MMONEY)
            } else if ( campus == CAMPUS_C){
                changeStudents( g, PLAYER_C, THD, BPS, BQN, MJ,  MTV, MMONEY)
            } else if ( campus == GO8_A){
                changeStudents( g, PLAYER_A, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            } else if ( campus == GO8_B){
                changeStudents( g, PLAYER_B, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }else if ( campus == GO8_C){
                changeStudents( g, PLAYER_C, 2*THD, 2*BPS, 2*BQN, 2*MJ, 2*MTV, 2*MMONEY);
            }
        }
        counter += 2;
    }
}

  
Game newGame (int discipline[], int dice[]){ // ??
    
    Game *g = NULL;
    while ( g != NULL){
        g = (Game) malloc (sizeof Game);
    }
    return g;
}

void disposeGame (Game g){
    free (g);
    assert(g == NULL);
}

void makeAction (Game g, action a){
    player *temp = {0};
    int turn = getWhoseturn(g);
    if (turn == UNI_A){
        temp = g->playerone;
    } else if (turn == UNI_B){
        temp = g->playertwo;
    } else if (turn == UNI_C){
        temp = g->playerthree;
    }

    if(isLegalAction(g,a) == TRUE){
       if(turn == UNI_A){
          if ( a.Actioncode == PASS){
              //DO nothing as they have passed their turn
          } else if (a.Actioncode == BUILD_CAMPUS){
              //This builds a campus at the price of
              // 1 BPS, 1 B?, 1 MJ , 1 MTV
              changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
              changeKPI(g, 10);
              writeToBoard(g,a.destination,CAMPUS_A);
          } else if (a.Actioncode == BUILD_GO8) {
              //USE up two MJ and 3 MS
              changeStudents(g, 0, 0, 0, 0, -2, 0, -3);
              changeKPI(g, 10);
              writeToBoard(g,a.destination,GO8_A);
          } else if (a.Actioncode == OBTAIN_ARC) {
              changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
              changeKPI(g, 10);
              writeToBoard(g,a.destination,ARC_A);
              g->ARCsCreated++;
          } else if (a.Actioncode == START_SPINOFF) {
              //DO Nothing as this is an unexpected output
          } else if (a.Actioncode == OBTAIN_PUBLICATION) {
              changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
              g->pubsCreated++;
          } else if (a.Actioncode == OBTAIN_IP_PATENT) {
              changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
              changeKPI(g, 10);
          } else if (a.Actioncode == RETRAIN_STUDENTS) {
              grandExchange(g, a);
          }
       }else if(turn == UNI_B){
           if ( a.Actioncode == PASS){
               //DO nothing as they have passed their turn
           } else if (a.Actioncode == BUILD_CAMPUS){
               //This builds a campus at the price of
               // 1 BPS, 1 B?, 1 MJ , 1 MTV
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,CAMPUS_B);
           } else if (a.Actioncode == BUILD_GO8) {
               //USE up two MJ and 3 MS
               changeStudents(g, 0, 0, 0, 0, -2, 0, -3);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,GO8_B);
           } else if (a.Actioncode == OBTAIN_ARC) {
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,ARC_B);
               g->ARCsCreated++;
           } else if (a.Actioncode == START_SPINOFF) {
               //DO Nothing as this is an unexpected output
           } else if (a.Actioncode == OBTAIN_PUBLICATION) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               g->pubsCreated++;
           } else if (a.Actioncode == OBTAIN_IP_PATENT) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               changeKPI(g, 10);
           } else if (a.Actioncode == RETRAIN_STUDENTS) {
               grandExchange(g, a);
           }
       }else if(turn == UNI_C){
           if ( a.Actioncode == PASS){
               //DO nothing as they have passed their turn
           } else if (a.Actioncode == BUILD_CAMPUS){
               //This builds a campus at the price of
               // 1 BPS, 1 B?, 1 MJ , 1 MTV
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,CAMPUS_C);
           } else if (a.Actioncode == BUILD_GO8) {
               //USE up two MJ and 3 MS
               changeStudents(g, 0, 0, 0, 0, -2, 0, -3);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,GO8_C);
           } else if (a.Actioncode == OBTAIN_ARC) {
               changeStudents(g, 0, 0, -1, -1, -1, -1, 0);
               changeKPI(g, 10);
               writeToBoard(g,a.destination,ARC_C);
               g->ARCsCreated++;
           } else if (a.Actioncode == START_SPINOFF) {
               //DO Nothing as this is an unexpected output
           } else if (a.Actioncode == OBTAIN_PUBLICATION) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               g->pubsCreated++;
           } else if (a.Actioncode == OBTAIN_IP_PATENT) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               changeKPI(g, 10);
           } else if (a.Actioncode == RETRAIN_STUDENTS) {
               grandExchange(g, a);
           }
       }
        
}

void throwDice (Game g, int diceScore){

   int students[19] = {-1};
   int RegionID = 0;
   int count = 0;
   
   while (regionID < 19) {
      if(g->dice[regionID] == diceValue) {
         students[count] = regionID;
         count++;
      }
      regionID++;
   }

   count = 0;
   IDcounter = 0
   while (students[count] != -1){
      while(IDcounter < 19);
         if(student[count] == IDcounter){
            //give co-ordinates around regionID[IDcounter] -> meaning in each region
            //using 2D array to store co-ordinates in each region or linked lists
            //check if theres duplicate co-ordinates and any campuses or GO8 in them
            //give students discipline[student[count]] if theres a campus
            //give 2 instead of 1 if GO8
         }
         IDcounter++;
      }
      count++;
   }
   if (g->playerTurn == UNI_C){
      g->playerTurn == UNI_A;
   } else {
      g->playerTurn++;
   }
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
    if(g->ARCsCreated>0){
        if((g->playerone.Arc > g->playertwo.Arc) && (g->playerone.Arc > g->playerthree.Arc)){
            ID = UNI_A;
        }
        else if((g->playertwo.Arc > g->playerone.Arc) && (g->playertwo.Arc > g->playerthree.Arc)){
            ID = UNI_B;
        }
        else if((g->playerone.Arc > g->playertwo.Arc) && (g->playerone.Arc > g->playerthree.Arc)){
            ID = UNI_C;
        }
    }
    return ID;

}

int getMostPublications(Game g){
    int ID = NO_ONE;
    if(g.pubsCreated>0){
        if((g->playerone.pubs > g->playertwo.pubs) && (g->playerone.pubs > g->playerthree.pubs)){
            ID = UNI_A;
        }
        else if((g->playertwo.pubs > g->playerone.pubs) && (g->playertwo.pubs > g->playerthree.pubs)){
            ID = UNI_B;
        }
        else if((g->playerone.pubs > g->playertwo.pubs) && (g->playerone.pubs > g->playerthree.pubs)){
            ID = UNI_C;
        }
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
    }
    else if (g->currentTurn % 3 == 1){
        ID = UNI_B;
    }
    else if (g->currentTurn % 3 == 2){
        ID = UNI_C;
    }
    return ID;
}

int getCampus (Game g, path pathToVortex){
    co_ordinate point;
    point = movedecoder (pathToVortex, 7);
    int campus = g->gameboard[point.row][point.column];
    return campus;
}

int getARC (Game g, path pathToEdge){
    co_ordinate point;
    point = movedecoder (pathToEdge, 7);
    int arc = g->gameboard[point.row][point.column];
    return arc;
}

int isLegalAction (Game g, action a){
    int bool = TRUE;
    if(g->currentTurn == -1){
        bool == FALSE;
    }
    if(a.Actioncode == OBTAIN_PUBLICATION || a.Actioncode == OBTAIN_IP_PATENT){
        bool == FALSE
    }
    //if(/* Anything related to vertex/movement here*/){
    //}
    
    // Check for sufficient students to do action(s)
    
    if(a.Actioncode == BUILD_CAMPUS || a.Actioncode == OBTAIN_ARC){
        int temp = 0;
        if(getWhoseTurn == UNI_A){
            temp = g->playerone;
        }else if(getWhoseTurn == UNI_B){
            temp = g->playertwo;
        }else if(getWhoseTurn == UNI_C){
            temp = g->playerthree;
        }
        
        if(temp.BPS >= 1 && temp.BQN >= 1 && temp.MJ >= 1 && temp.MTV >=1){
            bool == TRUE;
        }
    }
    
    if(a.Actioncode == BUILD_GO8){
        int temp = 0;
        if(getWhoseTurn == UNI_A){
            temp = g->playerone;
        }else if(getWhoseTurn == UNI_B){
            temp = g->playertwo;
        }else if(getWhoseTurn == UNI_C){
            temp = g->playerthree;
        }
        
        if(temp.MJ >= 2 && temp.MS >=3){
            bool == TRUE;
        }
    }
    if(a.Actioncode == OBTAIN_PUBLICATION || a.Actioncode == OBTAIN_IP_PATENT){
        int temp = 0;
        if(getWhoseTurn == UNI_A){
            temp = g->playerone;
        }else if(getWhoseTurn == UNI_B){
            temp = g->playertwo;
        }else if(getWhoseTurn == UNI_C){
            temp = g->playerthree;
        }
        
        if(temp.MJ >= 1 && temp.MTV >=1 && temp.MMONEY >= 1){
            bool == TRUE;
        }
    }
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
    int studentnum = 0;
    if (player == UNI_A){
        if (discipline == STUDENT_THD) {
            studentnum = g->playerone.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g->playerone.BPS;
        } else if (discipline == STUDENT_BQN) {
            studentnum = g->playerone.BQN;
        } else if (discipline == STUDENT_MJ) {
            studentnum = g->playerone.MJ;
        } else if (discipline == STUDENT_MTV) {
            studentnum = g->playerone.MTV;
        } else if (discipline == STUDENT_MMONEY) {
            studentnum = g->playerone.MMONEY;
        }
    } else if (player == UNI_B){
        if (discipline == STUDENT_THD) {
            studentnum = g->playertwo.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g->playertwo.BPS;
        } else if (discipline == STUDENT_BQN) {
            studentnum = g->playertwo.BQN;
        } else if (discipline == STUDENT_MJ) {
            studentnum = g->playertwo.MJ;
        } else if (discipline == STUDENT_MTV) {
            studentnum = g->playertwo.MTV;
        } else if (discipline == STUDENT_MMONEY) {
            studentnum = g->playertwo.MMONEY;
        }
    } else if (player == UNI_C){
        if (discipline == STUDENT_THD) {
            studentnum = g->playerthree.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g->playerthree.BPS;
        } else if (discipline == STUDENT_BQN) {
            studentnum = g->playerthree.BQN;
        } else if (discipline == STUDENT_MJ) {
            studentnum = g->playerthree.MJ;
        } else if (discipline == STUDENT_MTV) {
            studentnum = g->playerthree.MTV;
        } else if (discipline == STUDENT_MMONEY) {
            studentnum = g->playerthree.MMONEY;
        }
    }    
    return studentnum;
}

int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo){
    int exchangeRate = 0;
    if (player == UNI_A){
        if (disciplineFrom == STUDENT_BPS){
            exchangeRate = g->playerone.retrain_BPS;
        } else if (disciplineFrom == STUDENT_BQN) {
            exchangeRate = g->playerone.retrain_BQN;
        } else if (disciplineFrom == STUDENT_MJ) {
            exchangeRate = g->playerone.retrain_MJ;
        } else if (disciplineFrom == STUDENT_MTV) {
            exchangeRate = g->playerone.retrain_MTV;
        } else if (disciplineFrom == STUDENT_MMONEY) {
            exchangeRate = g->playerone.retrain_MMONEY;
        }
    } else if (player == UNI_B) {
        if (disciplineFrom == STUDENT_BPS){
            exchangeRate = g->playertwo.retrain_BPS;
        } else if (disciplineFrom == STUDENT_BQN) {
            exchangeRate = g->playertwo.retrain_BQN;
        } else if (disciplineFrom == STUDENT_MJ) {
            exchangeRate = g->playertwo.retrain_MJ;
        } else if (disciplineFrom == STUDENT_MTV) {
            exchangeRate = g->playertwo.retrain_MTV;
        } else if (disciplineFrom == STUDENT_MMONEY) {
            exchangeRate = g->playertwo.retrain_MMONEY;
        }
    } else if (player == UNI_C) {
        if (disciplineFrom == STUDENT_BPS){
           exchangeRate =  g->playerthree.retrain_BPS;
        } else if (disciplineFrom == STUDENT_BQN) {
            exchangeRate = g->playerthree.retrain_BQN;
        } else if (disciplineFrom == STUDENT_MJ) {
            exchangeRate = g->playerthree.retrain_MJ;
        } else if (disciplineFrom == STUDENT_MTV) {
            exchangeRate = g->playerthree.retrain_MTV;
        } else if (disciplineFrom == STUDENT_MMONEY) {
            exchangeRate = g->playerthree.retrain_MMONEY;
        }
    }
    return exchangeRate;
}
