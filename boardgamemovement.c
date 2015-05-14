// Game board representation using method though up by our group
#define ARCco 'A'
#define DIVISION 2
#define NUMBER_OF_DIRECTIONS 6
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

//Prototypes 
int islegalmovement ( co_ordinate position);
co_ordinate movedecoder (char* directions,char type);
co_ordinate movement (co_ordinate position, char route);
void studentgenerator (int regionID);

void studentgenerator (int regionID) {
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
        
    } else if (regionID == 17) {
        
    } else if (regionID == 18) {
        
    }
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
