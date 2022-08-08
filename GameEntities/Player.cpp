#include "Player.h"

//sets position and target position, also sets access to global key control vars
Player::Player(int startX, int startY, bool* keyPtr){
    x = startX;
    y = startY;
    targX = startX;
    targY = startY;
    //get local access to global key pressed vars
    for (int i=0;i<4;i++){
        keys[i] = keyPtr++;
    }
}

Player::~Player(){} //nothing to deallocate

//if not on target, moves player towards target
void Player :: walk(){
    if ( *target != * pos){
        *pos += (speed * dir);
    }
}

//runs the game events for the player
void Player :: run(){

    //check if at target position or not
    if ( *target == *pos) {
        mobile = false; //at target so not moving
    }

    if (mobile){
        walk(); //update x and y
    } else {
        //handle user input
        int movement = -1;
        for (int i=0;i<4;i++){
            if (*keys[i]){
                movement = i;
            }
        }
        mobile = true;
        dir = 1;
        switch (movement) {
            case 0 : {dir = -1;}//A pressed
            case 1 : {target = &targX; pos = &x; break;}//D pressed
            case 3 : {dir = -1;}//W pressed
            case 2 : {target = &targY; pos = &y; break;}//S pressed
            default : {mobile = false;}
        }
        if (mobile){
            *target += (16 * dir);
            catchTarget(); //catch target position
        }
    }
}

//prevent player from moving off grid
void Player :: catchTarget(){
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

