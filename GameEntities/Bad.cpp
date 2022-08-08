#include "Bad.h"

//sets position and target position
Bad::Bad(int startX,int startY){
    x = startX;
    y = startY;
    targX = startX;
    targY = startY;
}

//delete the next dynamically allocated bad guy if it exists
Bad::~Bad(){
    if (nextBad!=nullptr){
        delete nextBad;
    }
}

//randomly sets the direction, axis, range of travel
void Bad :: decidePath(){
    dir = 1; //assume in positive direction, but change if case 0 or 2
    switch(rand()%4){
        case 0 : {dir = -1;} //left
        case 1 : {target = &targX; pos = &x; break;} //right
        case 2 : {dir = -1;} //up
        case 3 : {target = &targY; pos = &y; break;} //down
    }
    steps = (rand()%4)+1; //range between 1 and 4 squares
    sleep = 6 * steps; //entity sleeps for longer if planing to move  further
}

//runs bad guy game events, takes reference to the player and returns true if in contact
bool Bad :: run(Player* player){

    //wait will awakened
    if(sleep > 0){
        sleep --;
    } else {
        //if at target position
        if ( *target == *pos){
            if (steps==0){ //end of current path
                decidePath();
            } else { //just at grid point
                *target += (16*dir);
                catchTarget();
                steps --;
            }
        } else {
            (*pos) += (speed * dir); //move towards target position
        }
    }

    bool caught = ((targX == player->getTX()) && (targY == player->getTY())); //if in contact with player

    //run next bad guy's game events
    if (nextBad!=nullptr) {
        return nextBad->run(player) || caught; //return if subsequent or current bad guys caught the player
    } else {
        return caught; //base case for recursive function, return if this bad guy caught the player or not
    }
}

//spawns in a new bad guy via its linked list pointer
void Bad::spawn(int nextX, int nextY){
    nextBad = new Bad(nextX, nextY);
}

//prevent bad guys from moving off screen
void Bad :: catchTarget(){
    if (*target < 0){
        *target = 0;
        return; //save wasting time processing the below
    }
    int limit;
    if (target == &targX){
        limit = 464; //480 - 16
    } else {
        limit = 304; //320 -16
    }
    if (*target > limit){
        *target = limit;
    }
}
