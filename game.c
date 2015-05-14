//Created by Josfer, Michael, Lachlan and Inura
//For COMP1917 Knowledge Island board game 2015 edition
//To simulate a board game with instructions included
//B? has been changed to BQN to prevent the special property of ? from happening
//Similarly M$ has been changed to MMONEY
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

//NOTE: I have altered the #define to mirrors the ones in game.h

#define CAMPUS 1
#define GO8 2
#define START_TURN_NUMBER -1
#define RETRAIN_COST 3
#define NUM_DISCIPLINES 6
#define ARCco 'A'
#define DIVISION 2
#define NUMBER_OF_DIRECTIONS 6

#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                            STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                            STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                            STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                            STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}

typedef char path[PATH_LIMIT];

typedef struct _action {
    int actionCode;  // see #defines above
    path destination; // if the action operates on a vertex or ARC this
    // specifies *which* vertex or path.  unused
    // otherwise
    int disciplineFrom;  // used for the retrain students action
    int disciplineTo;    // used for the retrain students action
} action;

typedef unsigned long long numberof;
typedef struct _game {
    //int playerTurn = NO_ONE;
    player playerone;
    player playertwo;
    player playerthree;
    gameboard[53] = {0};
    playercampus[53] = {NO_ONE}
    playercampustype[53] = {0}
    numberof GOE = 0;
    unsigned char mostArc = NO_ONE;
    unsigned char mostPub = NO_ONE;
    int currentTurn = START_TURN_NUMBER;
    
    int dice[] = DEFAULT_DICE;
    int disciplines[] = DEFAULT_DISCIPLINES;
    
    int pubsCreated = 0; // To count pubs created for getMostPublications
    int ARCsCreated = 0; // same as above but for ARCs.
} Game;
typedef struct _player {
    numberof KPI = 0;
    numberof Arc = 2;
    numberof pubs = 0;
    numberof campuses = 2;
    numberof GOEs = 0;
    numberof ips = 0;
    numberof students[6] = {0};
    numberof retrain_BPS = RETRAIN_COST;
    numberof retrain_BQN = RETRAIN_COST;
    numberof retrain_MJ = RETRAIN_COST;
    numberof retrain_MTV = RETRAIN_COST;
    numberof retrain_MMONEY = RETRAIN_COST;
} player;

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
      temp->student[studentCount] == temp->student[studentCount] + addStudent[studentCount];
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
   temp->KPI = temp->KPI + KPI;
    
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
   g.gameboard[point.row][point.column] = building;
}

co_ordinate movedecoder (char* directions,char type) {
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

co_ordinate movement (co_ordinate position, char route){
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
int islegalmovement ( co_ordinate position) {
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
    if (getWhoseTurn(g) == UNI_A){
        temp = g.playerone;
    } else if (getWhoseTurn(g) == UNI_B){
        temp = g.playertwo;
    } else if (getWhoseTurn(g) == UNI_C){
        temp = g.playerthree;
    }

    if(isLegalAction(g,a) == TRUE){
       if(temp==g.playerone){
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
              g.ARCsCreated++;
          } else if (a.Actioncode == START_SPINOFF) {
              //DO Nothing as this is an unexpected output
          } else if (a.Actioncode == OBTAIN_PUBLICATION) {
              changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
              g.pubsCreated++;
          } else if (a.Actioncode == OBTAIN_IP_PATENT) {
              changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
              changeKPI(g, 10);
          } else if (a.Actioncode == RETRAIN_STUDENTS) {
              grandExchange(g, a);
          }
       }else if(temp==g.playertwo){
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
               g.ARCsCreated++;
           } else if (a.Actioncode == START_SPINOFF) {
               //DO Nothing as this is an unexpected output
           } else if (a.Actioncode == OBTAIN_PUBLICATION) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               g.pubsCreated++;
           } else if (a.Actioncode == OBTAIN_IP_PATENT) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               changeKPI(g, 10);
           } else if (a.Actioncode == RETRAIN_STUDENTS) {
               grandExchange(g, a);
           }
       }else if(temp==g.playerthree){
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
               g.ARCsCreated++;
           } else if (a.Actioncode == START_SPINOFF) {
               //DO Nothing as this is an unexpected output
           } else if (a.Actioncode == OBTAIN_PUBLICATION) {
               changeStudents(g, 0, 0, 0, 0, -1, -1, -1);
               g.pubsCreated++;
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
    int discipline = g.disciplines[regionID];
    return discipline;
}

int getDiceValue (Game g, int regionID){
    int defaultDice = g.dice[regionID];
    return defaultDice;
}

int getMostARCs(Game g){
    int ID = NO_ONE;
    if(g.ARCsCreated>0){
        if((g.playerone.Arc > g.playertwo.Arc) && (g.playerone.Arc > g.playerthree.Arc)){
            ID = UNI_A;
        }
        else if((g.playertwo.Arc > g.playerone.Arc) && (g.playertwo.Arc > g.playerthree.Arc)){
            ID = UNI_B;
        }
        else if((g.playerone.Arc > g.playertwo.Arc) && (g.playerone.Arc > g.playerthree.Arc)){
            ID = UNI_C;
        }
    }
    return ID;

}

int getMostPublications(Game g){
    int ID = NO_ONE;
    if(g.pubsCreated>0){
        if((g.playerone.pubs > g.playertwo.pubs) && (g.playerone.pubs > g.playerthree.pubs)){
            ID = UNI_A;
        }
        else if((g.playertwo.pubs > g.playerone.pubs) && (g.playertwo.pubs > g.playerthree.pubs)){
            ID = UNI_B;
        }
        else if((g.playerone.pubs > g.playertwo.pubs) && (g.playerone.pubs > g.playerthree.pubs)){
            ID = UNI_C;
        }
    }
    return ID;
}

int getTurnNumber (Game g){
    int turnNumber = 0;
    turnNumber = g.currentTurn;
    return turnNumber;
}

int getWhoseTurn (Game g){
    int ID = NO_ONE;
    if (g.currentTurn % 3 == 0){
        ID = UNI_A;
    }
    else if (g.currentTurn % 3 == 1){
        ID = UNI_B;
    }
    else if (g.currentTurn % 3 == 2){
        ID = UNI_C;
    }
    return ID;
}

int getCampus (Game g, path pathToVortex){
    int campus = pathToVortex;
    return campus;
}

int getARC (Game g, path pathToEdge){
    int arc = pathToEdge;
    return arc;
}

int isLegalAction (Game g, action a){
    int bool = TRUE;
    if(g.currentTurn == -1){
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
            temp = g.playerone;
        }else if(getWhoseTurn == UNI_B){
            temp = g.playertwo;
        }else if(getWhoseTurn == UNI_C){
            temp = g.playerthree;
        }
        
        if(temp.BPS >= 1 && temp.BQN >= 1 && temp.MJ >= 1 && temp.MTV >=1){
            bool == TRUE;
        }
    }
    
    if(a.Actioncode == BUILD_GO8){
        int temp = 0;
        if(getWhoseTurn == UNI_A){
            temp = g.playerone;
        }else if(getWhoseTurn == UNI_B){
            temp = g.playertwo;
        }else if(getWhoseTurn == UNI_C){
            temp = g.playerthree;
        }
        
        if(temp.MJ >= 2 && temp.MS >=3){
            bool == TRUE;
        }
    }
    if(a.Actioncode == OBTAIN_PUBLICATION || a.Actioncode == OBTAIN_IP_PATENT){
        int temp = 0;
        if(getWhoseTurn == UNI_A){
            temp = g.playerone;
        }else if(getWhoseTurn == UNI_B){
            temp = g.playertwo;
        }else if(getWhoseTurn == UNI_C){
            temp = g.playerthree;
        }
        
        if(temp.MJ >= 1 && temp.MTV >=1 && temp.MMONEY >= 1){
            bool == TRUE;
        }
    }
}

int getKPIpoints(Game g, int player){
    int KPI = 0;
    if (player == 1) {
        KPI = g.playerone.KPI;
    } else if (player == 2) {
        KPI = g.playertwo.KPI;    
    } else if (player == 3) {
        KPI = g.playerthree.KPI;    
    }    
    return KPI;
}

int getARCs (Game g, int player){
    int Arcs = 0;
    if (player == 1) {
        Arcs = g.playerone.Arc;
    } else if (player == 2) {
        Arcs = g.playertwo.Arc;    
    } else if (player == 3) {
        Arcs = g.playerthree.Arc;    
    }    
    return Arcs;
}

int getGO8s (Game g, int player){
    int GOE = 0;
    if (player == 1) {
        GOE = g.playerone.GOEs;
    } else if (player == 2) {
        GOE = g.playertwo.GOEs;    
    } else if (player == 3) {
        GOE = g.playerthree.GOEs;    
    }    
    return GOE;
}

int getCampuses (Game g, int player){
    int campus = 0;
    if (player == 1) {
        campus = g.playerone.campuses;
    } else if (player == 2) {
        campus = g.playertwo.campuses;    
    } else if (player == 3) { 
        campus = g.playerthree.campuses;    
    }    
    return campus;
}

int getIPs (Game g, int player){
    int IP = 0;
    if (player == 1) {
        IP = g.playerone.ips;
    } else if (player == 2) {
        IP = g.playertwo.ips;    
    } else if (player == 3) {
        IP = g.playerthree.ips;    
    }
    return IP;
}

int getPublications (Game g, int player){
    int pubs = 0;
    if (player == 1) {
        pubs = g.playerone.pubs;
    } else if (player == 2) {
        pubs = g.playertwo.pubs;    
    } else if (player == 3) {
        pubs = g.playerthree.pubs;    
    }
    return pubs;    
}

int getStudents (Game g, int player, int discipline){
    int studentnum = 0;
    if (player == 1){
        if (discipline == STUDENT_THD) {
            studentnum = g.playerone.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g.playerone.BPS;
        } else if (discipline == STUDENT_BQN) {
            studentnum = g.playerone.BQN;
        } else if (discipline == STUDENT_MJ) {
            studentnum = g.playerone.MJ;
        } else if (discipline == STUDENT_MTV) {
            studentnum = g.playerone.MTV;
        } else if (discipline == STUDENT_MMONEY) {
            studentnum = g.playerone.MMONEY;
        }
    } else if (player == 2){
        if (discipline == STUDENT_THD) {
            studentnum = g.playertwo.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g.playertwo.BPS;
        } else if (discipline == STUDENT_BQN) {
            studentnum = g.playertwo.BQN;
        } else if (discipline == STUDENT_MJ) {
            studentnum = g.playertwo.MJ;
        } else if (discipline == STUDENT_MTV) {
            studentnum = g.playertwo.MTV;
        } else if (discipline == STUDENT_MMONEY) {
            studentnum = g.playertwo.MMONEY;
        }
    } else if (player == 3){
        if (discipline == STUDENT_THD) {
            studentnum = g.playerthree.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g.playerthree.BPS;
        } else if (discipline == STUDENT_BQN) {
            studentnum = g.playerthree.BQN;
        } else if (discipline == STUDENT_MJ) {
            studentnum = g.playerthree.MJ;
        } else if (discipline == STUDENT_MTV) {
            studentnum = g.playerthree.MTV;
        } else if (discipline == STUDENT_MMONEY) {
            studentnum = g.playerthree.MMONEY;
        }
    }    
    return studentnum;
}

int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo){
    int exchangeRate = 0;
    if (player == 1){
        if (disciplineFrom == STUDENT_BPS){
            exchangeRate = g.playerone.retrain_BPS;
        } else if (disciplineFrom == STUDENT_BQN) {
            exchangeRate = g.playerone.retrain_BQN;
        } else if (disciplineFrom == STUDENT_MJ) {
            exchangeRate = g.playerone.retrain_MJ;
        } else if (disciplineFrom == STUDENT_MTV) {
            exchangeRate = g.playerone.retrain_MTV;
        } else if (disciplineFrom == STUDENT_MMONEY) {
            exchangeRate = g.playerone.retrain_MMONEY;
        }
    } else if (player == 2) {
        if (disciplineFrom == STUDENT_BPS){
            exchangeRate = g.playertwo.retrain_BPS;
        } else if (disciplineFrom == STUDENT_BQN) {
            exchangeRate = g.playertwo.retrain_BQN;
        } else if (disciplineFrom == STUDENT_MJ) {
            exchangeRate = g.playertwo.retrain_MJ;
        } else if (disciplineFrom == STUDENT_MTV) {
            exchangeRate = g.playertwo.retrain_MTV;
        } else if (disciplineFrom == STUDENT_MMONEY) {
            exchangeRate = g.playertwo.retrain_MMONEY;
        }
    } else if (player == 3) {
        if (disciplineFrom == STUDENT_BPS){
           exchangeRate =  g.playerthree.retrain_BPS;
        } else if (disciplineFrom == STUDENT_BQN) {
            exchangeRate = g.playerthree.retrain_BQN;
        } else if (disciplineFrom == STUDENT_MJ) {
            exchangeRate = g.playerthree.retrain_MJ;
        } else if (disciplineFrom == STUDENT_MTV) {
            exchangeRate = g.playerthree.retrain_MTV;
        } else if (disciplineFrom == STUDENT_MMONEY) {
            exchangeRate = g.playerthree.retrain_MMONEY;
        }
    }
    return exchangeRate;
}
