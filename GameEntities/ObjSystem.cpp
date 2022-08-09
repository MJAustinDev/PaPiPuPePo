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

#include "ObjSystem.h"

//games draw sequence, uses reference to pixel control system to draw the game world
void ObjSystem :: draw(PxSystem* ctrlPx){
    ctrlPx->drawBackground(); //draw the background
    ctrlPx->drawSprite(coin.getX(), coin.getY(), 2, 0x0000FFFF, 0x00000000); //draw coin
    ctrlPx->drawSprite(player.getX(), player.getY(), 2, cPlayer, 0x00000000); //draw player
    //draw bad guys
    Bad* badPtr = &bad;
    while (badPtr!=nullptr){
        ctrlPx->drawSprite(badPtr->getX(), badPtr->getY(), 2, 0x00FF0000, 0x00000000);
        badPtr = badPtr->getNext();
    }
}

//runs the game events
bool ObjSystem :: run(){

    if (!dead){
        player.run();
        coin.run(&player, &badLast);
    } else {
        //lower timer till close
        deathClock --;
        player.walk(); //allows player to halt on target
    }
    //run all bad guys
    if (bad.run(&player)){ //recursive function returns if the player has been caught
        dead = true;
        cPlayer = 0x00000033;
    }

    if (deathClock<=0){
        return false; //end game loop
    } else {
        return true; //carry on processing game events
    }

}
