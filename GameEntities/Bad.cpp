/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
*/

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
