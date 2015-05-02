//This is the game struct we use for the AI testing 
//and the creation of the game board
// remeber the struct is in lower case and will act as pointer to the Game struct

typedef _game {
int mostArc;
int mostPub;
int KPI_of_each_player;
int currentTurn;
int whoseTurn;
int currentDice;
int number_of_Arc;
int number_of_pubs;
int number_of_campuses;
int number_of_g08s;
int number_of_ips;
int number_of_students_per_player[];
} game;
