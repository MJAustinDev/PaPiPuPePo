#ifndef OBJSYSTEM
#define OBJSYSTEM

#include "PxSystem.h"

#include "Coin.h" //includes bad.h which then includes player.h

//controls game play flow and game entity objects
class ObjSystem {

    public :
        ObjSystem(bool* keyPtr) : player(160, 160, keyPtr), bad(320,160) {}; //sets up the game
        ~ObjSystem(){}; //nothing dynamic to deallocate

        bool run(); //run game events for all entities
        void draw(PxSystem* ctrlPx); //draw game to screen
        int getScore(){return coin.getScore();}; //gets the score from the coin object

    private:

        Player player;
        Coin coin;
        Bad bad; //first bad guy declared statically, the rest dynamically
        Bad* badLast = &bad; //points to the last bad guy added to the linked list

        int deathClock = 170; //starts to decrement when the player has died
        bool dead = false; //if player is dead or not
        unsigned int cPlayer = 0x000000FF; //player colour, changes on death

};


#endif
