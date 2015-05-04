//Created by Josfer, Micheal, Lachlan and Inura
//For COMP1917 Knowledge Island board game 2015 edition
//To simulate a board game with instructions included
//B? has been changed to Bq to prevent the special property of ? from happening
//Similarly M$ has been changed to MS
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
    player playerone;
    player playertwo;
    player playerthree;
    gameboard[53] = {0};
    playercampus[53] = {NO_PLAYER}
    playercampustype[53] = {0}
    unsigned char mostArc = NO_PLAYER;
    unsigned char mostPub = NO_PLAYER;
    long long currentTurn = START_TURN_NUMBER;
} Game;
typedef struct _player {
    numberof KPI = 0;
    numberof Arc = 2;
    numberof pubs = 0;
    numberof campuses = 2;
    numberof g08s = 0;
    numberof ips = 0;
    numberof ThD = 0;
    numberof BPS = 0;	
    numberof Bq = 0;
    numberof MJ = 0;
    numberof MTV = 0;	
    numberof MS = 0;
    numberof retrain_BPS = RETRAIN_COST;
    numberof retrain_Bq = RETRAIN_COST;
    numberof retrain_MJ = RETRAIN_COST;
    numberof retrain_MTV = RETRAIN_COST;
    numberof retrain_MS = RETRAIN_COST;
} player;

//These are the prototypes for the functions that we have made for the project
void changeStudents (Game g, int ThD , int BPS , int Bq ,int MJ,int MTV,int MS);
void changeKPI

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
        
    } else if (a.Actioncode == OBTAIN_ARC) {
        
    } else if (a.Actioncode == START_SPINOFF) {
        //DO Nothing as this is an unexpected output
    } else if (a.Actioncode == OBTAIN_PUBLICATION) {
        
    } else if (a.Actioncode == OBTAIN_IP_PATENT) {
        
    } else if (a.Actioncode == RETRAIN_STUDENTS) {
        
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
    
}

int getARCs (Game g, int player){
    
}

int getGO8s (Game g, int player){
    
}

int getCampuses (Game g, int player){
    
}

int getIPs (Game g, int player){
    
}

int getPublications (Game g, int player){
    
}

int getStudents (Game g, int player, int discipline){
    
}

int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo){
    
}
