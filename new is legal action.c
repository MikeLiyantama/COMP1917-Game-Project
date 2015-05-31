int isLegalAction (Game g, action a){
    int bool = FALSE;
    //legalmovement(moveDecoder (a.destination,char type),
    //This is making temp equal to the player
    player *temp;
    if(getWhoseTurn(g) == UNI_A){
        temp = &(g->playerone);
    }else if(getWhoseTurn(g) == UNI_B){
        temp = &(g->playertwo);
    }else if(getWhoseTurn(g) == UNI_C){
        temp = &(g->playerthree);
    }

    //This will encode for the spinoffs
    if(a.actionCode == START_SPINOFF){
        if((temp->student[3] > 0)&&(temp->student[4] > 0 )){
            if(temp->student[4] > 0 ){
                bool = TRUE;
            }
        }
    }
    // Check for sufficient students to do action(s)

    if(a.actionCode == BUILD_CAMPUS){
        if((temp->students[1] >= 1) && (temp->students[2] >= 1)){
            if((temp->students[3] >= 1) && (temp->students[4] >=1)){
                if((getCampus (g,a.destination)== VACANT_VERTEX)){
                    bool == TRUE;
                }
            }
        }
    }

    if(a.actionCode == BUILD_GO8){

    }

    if
    return bool;
}
