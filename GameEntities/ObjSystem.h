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
