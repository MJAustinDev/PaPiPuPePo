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

#ifndef BAD_H
#define BAD_H

#include <iostream> //needed for random

#include "Player.h"

//bad guy entity, kills player on contact and contains memory reference to the next bad guy
class Bad{

public:

    Bad(int startX,int startY); //takes spawn position as constructor input
    ~Bad();

    //getters
    int getX(){return x;};
    int getY(){return y;};
    int getTX(){return targX;};
    int getTY(){return targY;};
    Bad* getNext(){return nextBad;};

    bool run(Player* player); //runs game events for the bad guy
    void spawn(int nextX, int nextY); //spawns in a new bad guy and attaches it to the linked list

private:

    void decidePath(); //plan movement
    void catchTarget(); //prevent bad guy from going off screen

    //current position of the bad guy
    int x;
    int y;
    int* pos = &x;

    //target position of the bad guy
    int targX;
    int targY;
    int* target = &targX;

    //movement vars
    int steps = 0; //how many squares the current path is in length
    int sleep = 70; //wait time from spawning/planning path
    int speed = 2; //distance travelled
    int dir = 1; //either -1 or 1 depending on direction travelled

    Bad* nextBad = nullptr; //points to the next bad guy in the linked list

};

#endif
