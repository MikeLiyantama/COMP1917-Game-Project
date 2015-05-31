int isLegalAction (Game g, action a){
    int bool = FALSE;
    int uni = getWhoseTurn(g);
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
        if((temp->students[3] >= 1)&&(temp->students[4] >= 1)){
            if(temp->students[4] >= 1){
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
        if((temp->students[3] >=2 )&&(temp->students[5] >= 3 )){
            if((getCampus (g,a.destination)== uni)){
                bool=TRUE;
            }
        }
    }

    if(a.actionCode == OBTAIN_ARC){
        if((temp->students[1]>= 1)&& (temp->students[2] >=1)){
            if(getARC(g,a.destination))== VACANT_ARC){
                bool = TRUE;
            }

        }
    }

    if(a.actionCode == RETRAIN_STUDENTS){

        if(a.disciplineFrom ==  STUDENT_BPS){
            if(temp->students[1] >= temp->retrain_BPS){
                bool = TRUE;
            }
        }else if(a.disciplineFrom == STUDENT_BQN){
            if(temp->students[2] >= temp->retrain_BQN){
                bool = TRUE;
            }
        }else if(a.disciplineFrom == STUDENT_MJ){
            if(temp->students[3] >= temp->retrain_MJ){
                bool = TRUE;
            }
        }else if(a.disciplineFrom == STUDENT_MTV){
            if(temp->students[4] >= temp->retrain_MTV){
                bool = TRUE;
            }
        }else if(a.disciplineFrom == STUDENT_MMONEY){
            if(temp->students[5] >= temp->retrain_MMONEY){
                bool = TRUE;
            }

        }
    }

    return bool;
}
