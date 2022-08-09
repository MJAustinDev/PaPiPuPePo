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

#ifndef PLAYER_H
#define PLAYER_H

//entity controlled by player, avoids bad guys and collects coins
class Player {

public :
    Player(int startX, int startY, bool* keyPtr); //takes spawn point and reference to key control vars as input
    ~Player();

    //getters
    int getX(){return x;};
    int getY(){return y;};
    int getTX(){return targX;};
    int getTY(){return targY;};

    void run(); //run game events for the player object
    void walk(); //updates x or y position if target is not equal

private :

    void catchTarget(); //prevent target from going off the screen
    bool* keys[4] = {nullptr, nullptr, nullptr, nullptr}; //point to global key press variables

    //current position of player
    int x;
    int y;
    int* pos = &x;

    //target position to move to
    int targX;
    int targY;
    int* target = &targX;

    //mobility vars
    bool mobile = false; //is player currently moving?
    int speed = 2; //how fast the player can move
    int dir = 1; //either 1 or -1 depending on direction of movement

};


#endif
