//Created by Josfer, Micheal, Lachlan and Inura
//For COMP1917 Knowledge Island board game 2015 edition
//To simulate a board game with instructions included
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
    player one;
    player two;
    player three;
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
    numberof B? = 0;
    numberof MJ = 0;
    numberof MTV = 0;	
    numberof M$ = 0;
    numberof retrain_BPS = RETRAIN_COST;
    numberof retrain_B? = RETRAIN_COST;
    numberof retrain_MJ = RETRAIN_COST;
    numberof retrain_MTV = RETRAIN_COST;
    numberof retrain_M$ = RETRAIN_COST;
} player;

