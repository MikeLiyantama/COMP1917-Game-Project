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
#define START_TURN_NUMBER -1

typedef struct _game {
    player one;
    player two;
    player three;
    unsigned char mostArc = NO_PLAYER;
    unsigned char mostPub = NO_PLAYER;
    long long currentTurn = START_TURN_NUMBER;

} Game;
typedef struct _player {
    unsigned int KPI = 0;
    unsigned char Arc = 2;
    unsigned char pubs = 0;
    unsigned char campuses = 2;
    unsigned char g08s = 0;
    unsigned int ips = 0;
    unsigned long long int THD = 0;
    unsigned int ThD = 0;
    unsigned int BPS = 0;	
    unsigned int B? = 0;
    unsigned int MJ = 0;
    unsigned int MTV = 0;	
    unsigned int M$ = 0;
} player;

