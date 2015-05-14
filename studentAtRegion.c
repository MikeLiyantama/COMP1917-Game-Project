
void studentAtRegion(game g, int regionID){
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
   while ( count <= 20){
   
   }
//define new function above main
//returns studentNumber with that discipline
//Do the stuff you want with that discipline in this function, can't return an array!
