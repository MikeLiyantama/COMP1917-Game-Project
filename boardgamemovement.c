// Game board representation using method though up by our group

#define NUMBER_OF_DIRECTIONS 6
typedef int columntype;
typedef struct _board {
  columntype columnzero[7] = {0};
  columntype columnzero[9] = {0};
  columntype columnzero[11] = {0};
  columntype columnzero[9] = {0};
  columntype columnzero[7] = {0};
} board;

typdef struct co-ordinate {
  int column;
  int row;
  int orientation;
} co-ordinate;

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
    position.row -= 1;
  } else if (travel == 1) {
    position.column -= 1;
  } else if (travel == 2) {
    position.row += 1;       
  } else if (travel == 3) {
    position.row += 1;
  } else if (travel == 4) {
    position.column += 1;
  } else if (travel == 5) {
    position.row -= 1;
  }
  position.orientation = ((travel + (NUMBER_OF_DIRECTIONS/2)) % NUMBER_OF_DIRECTIONS); 
  return position;
  }
