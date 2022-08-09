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
