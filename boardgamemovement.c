// Game board representation using method though up by our group

#define LEFT 1
#define RIGHT 2
#define ARCco 'A'
#define DIVISION 2
#define NUMBER_OF_DIRECTIONS 6
typedef int columntype;
typedef struct _board {
  columntype gameboard [21] [11] = {0};
} board;

typdef struct co-ordinate {
  int column;
  int row;
  int orientation;
  int valid;
} co-ordinate;

co-ordinate movedecoder (char* directions[],char type) {
   int counter = 0;
   int route;
   co-ordinate point = {0,4,0};
   if (type == ARCco){
      point.column = 1;
      point.row = 5;
   }
   while ( (directions[counter] != 0) && (point.valid == TRUE)) {
      route = direction[counter];
      point.valid = islegalmovement (point);
      counter++;      
   }
   return point;
}


co-ordinate movement (co-ordinate position, int route){
  unsigned long long direction = (PATH_LIMIT * NUMBER_OF_DIRECTIONS);
  int turning;
  if (route == RIGHT) {
    turning = -2;
  } else if ( route == LEFT) {
    turning = 2;
  } else {
    turning = 0;
  }
  int move = direction + turning + position.orientation;
  int travel = (move % 6);

  if (travel == 0){
    position.row -= 2;
  } else if (travel == 1) {
    position.column -= DIVISION;
  } else if (travel == 2) {
    position.row += DIVISION;       
  } else if (travel == 3) {
    position.row += DIVISION;
  } else if (travel == 4) {
    position.column += DIVISION;
  } else if (travel == 5) {
    position.row -= DIVISION;
  }
  position.orientation = ((travel + (NUMBER_OF_DIRECTIONS/2)) % NUMBER_OF_DIRECTIONS); 
  return position;
}
  
//movement is legal test
//FOr each row it means that if the number is greater than 
//the elements in the row or less than zero then the action is illegal
int islegalmovement ( co-ordinate position) {
  int move = FALSE;
  if((postion.column == 0) || (position.column == 10)){
    if((position.row > -1) && (postion.row < 13) {
    move = TRUE;
    }
  }
  if((position.column == 
  if((position.column > 4) && (position.column < 6)){
    if((position.row > -1) && (position.row < 21)){
    move = TRUE;
    }
  }
  return move;
