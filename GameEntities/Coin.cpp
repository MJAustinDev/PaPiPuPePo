#include "Coin.h"

//sets x and y vars to a random position on the board excluding a small area around the player
void getRandomPos(int* x, int* y, int playX, int playY){ //x and y values passed via pointer
    do {
        *x = (rand()%(30)) * 16; //480/16 = 30
        *y = (rand()%(20)) * 16; //320/16 = 20
    } while (((*x-32<=playX)&&(*x+48>playX)&&(*y-32<=playY)&&(*y+48>playY)));
}

//constructor sets it's position randomly outside of the players range
Coin::Coin(){
    getRandomPos(&x, &y, 160, 160); //160, 160 is the players starting coordinates
}

Coin::~Coin(){} //nothing to deallocate

/* runs game events for the coin,
checks if it has been collected,
if so it moves, increases the score and a new bad guy is spawned */
void Coin::run(Player* playPtr, Bad** bad){
    int playX = playPtr->getX();
    int playY = playPtr->getY();
    //has been collected
    if (playX==x && playY==y){
        score++; //increase score
        getRandomPos(&x, &y, playX, playY); //change own location
        //spawn in new bad guy
        int badX;
        int badY;
        getRandomPos(&badX, &badY, playX, playY);
        (*bad)->spawn(badX, badY);
        (*bad) = (*bad)->getNext();
    }
}
