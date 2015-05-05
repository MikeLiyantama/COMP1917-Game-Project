//Created by Josfer, Micheal, Lachlan and Inura
//For COMP1917 Knowledge Island board game 2015 edition
//To simulate a board game with instructions included
//B? has been changed to BQN to prevent the special property of ? from happening
//Similarly M$ has been changed to MMONEY
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define NO_PLAYER 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define PLAYER_THREE 3
#define NO_CAMPUS 0
#define CAMPUS 1
#define GO8 2
#define START_TURN_NUMBER -1
#define RETRAIN_COST 3

typedef unsigned long long numberof;
typedef struct _game {
    int turnNumber = START_TURN_NUMBER;
    int playerTurn = NO_PLAYER;
    player playerone;
    player playertwo;
    player playerthree;
    gameboard[53] = {0};
    playercampus[53] = {NO_PLAYER}
    playercampustype[53] = {0}
    numberof GOE = 0;
    unsigned char mostArc = NO_PLAYER;
    unsigned char mostPub = NO_PLAYER;
    long long currentTurn = START_TURN_NUMBER;
} Game;
typedef struct _player {
    numberof KPI = 0;
    numberof Arc = 2;
    numberof pubs = 0;
    numberof campuses = 2;
    numberof GOEs = 0;
    numberof ips = 0;
    numberof ThD = 0;
    numberof BPS = 0;	
    numberof BQN = 0;
    numberof MJ = 0;
    numberof MTV = 0;	
    numberof MMONEY = 0;
    numberof retrain_BPS = RETRAIN_COST;
    numberof retrain_BQN = RETRAIN_COST;
    numberof retrain_MJ = RETRAIN_COST;
    numberof retrain_MTV = RETRAIN_COST;
    numberof retrain_MMONEY = RETRAIN_COST;
} player;

//These are the prototypes for the functions that we have made for the project
void changeStudents (Game g, int ThD , int BPS , int BQN ,int MJ,int MTV,int MMONEY);
void changeKPI (Game g, int KPI);
void grandExchange(Game g, action a);

//These are functions that are part of the prototype provided in game.h
//They are need to have the same inputs and out puts
Game newGame (int discipline[], int dice[]){
    Game *g = NULL;
    while ( g == NULL){
        g = (Game) malloc (sizeof Game);
    }
    return g;
}

void disposeGame (Game g){
    free (g);
    assert(g == NULL);
}

void makeAction (Game g, action a){
    if ( a.Actioncode == PASS){
        //DO nothing as they have passed their turn
    } else if (a.Actioncode == BUILD_CAMPUS){
        //This builds a campus at the price of 
        // 1 BPS, 1 B?, 1 MJ , 1 MTV
        changeStudents(g, 0, -1, -1, -1, -1, 0);
        changeKPI(g, 10);
    } else if (a.Actioncode == BUILD_GO8) {
        //USE up two MJ and 3 MS 
        changeStudents(g, 0, 0, 0, -2, 0, -3);
        changeKPI(g, 10);
    } else if (a.Actioncode == OBTAIN_ARC) {
        changeStudents(g, 0, -1, -1, -1, -1, 0);
        changeKPI(g, 10);
    } else if (a.Actioncode == START_SPINOFF) {
        //DO Nothing as this is an unexpected output
    } else if (a.Actioncode == OBTAIN_PUBLICATION) {
        changeStudents(g, 0, 0, 0, -1, -1, -1);
    } else if (a.Actioncode == OBTAIN_IP_PATENT) {
        changeStudents(g, 0, 0, 0, -1, -1, -1);
        changeKPI(g, 10);
    } else if (a.Actioncode == RETRAIN_STUDENTS) {
        grandExchange(g, a);
    }

}

void throwDice (Game g, int diceScore){

}

int getDiscipline (Game g, int regionID){
    
}

int getDiceValue (Game g, int regionID){
    
}

int getMostARCs(Game g){
    
}

int getMostPublications(Game g){
    
}

int getTurnNumber (Game g){
    int turnNumber = 0;
    turnNumber = g.turnNumber;
    return turnNumber;
}

int getWhoseTurn (Game g){
    
}

int getCampus (Game g, path pathToVortex){
   
}

int getARC (Game g, path pathToEdge){
  
}

int isLegalAction (Game g, action a){
    
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
}

int getCampuses (Game g, int player){
    if (player == 1) {
        IP = g.playerone.ips;
    } else if (player == 2) {
        IP = g.playertwo.ips;    
    } else if (player == 3) {
        IP = g.playerthree.ips;    
    }    
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
}

int getPublications (Game g, int player){
    
}

int getStudents (Game g, int player, int discipline){
    int studentnum = 0;
    if (player == 1){
        if (discipline == STUDENT_THD) {
            studentnum = g.playerone.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g.playerone.BPS;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playerone.BQN;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playerone.MJ;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playerone.MTV;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playerone.MMONEY;
        }
    } else if (player == 2){
        if (discipline == STUDENT_THD) {
            studentnum = g.playertwo.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g.playertwo.BPS;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playertwo.BQN;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playertwo.MJ;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playertwo.MTV;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playertwo.MMONEY;
        }
    } else if (player == 3){
        if (discipline == STUDENT_THD) {
            studentnum = g.playerthree.THD;
        } else if (discipline == STUDENT_BPS){
            studentnum = g.playerthree.BPS;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playerthree.BQN;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playerthree.MJ;
        } else if (discipline == STUDENT_BPS) {
            studentnum = g.playerthree.MTV;
        } else if (discipline == STUDENT_BPS) {
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
