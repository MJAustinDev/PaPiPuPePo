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
