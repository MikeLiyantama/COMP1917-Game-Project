// cross.c
// 1917 final exam 2014s1
// part P Q1
// 15 Marks
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#include "cross.h"

// you can assume size is an odd positive value
// this function is to print on the screen a cross
// made of asterisks which fits inside a square of
// side length "size"

void drawCross (int size);

int main (void){
    drawCross(1);
    printf("\n");
    drawCross(3);
    printf("\n");
    drawCross(5);
    printf("\n");
    return 0;
}
/*
compile and test your code as follows

$ gcc -Wall -Werror -std=c99 -O -o partP1 cross.c testCross.c

examples

$ ./partP1 3
* *
 *
* *

$ ./partP1 5
*   *
 * *
  *
 * *
*   *

$ ./partP1 7
*     *
 *   *
  * *
   *
  * *
 *   *
*     *

$ ./partP1 1
*

submit with this command
$ submit partP1 cross.c
*/

void drawCross (int size) {
   int counter = 0;
   int hcounter = 0;
   while (counter < size ){
        hcounter = 0;
        while(hcounter < size){
            if((hcounter == counter)||(hcounter==(size-counter-1))){
                printf("*");
            }else {
                printf(" ");
            }
            hcounter++;
        }
        printf("\n");
        counter++;
   }
}
