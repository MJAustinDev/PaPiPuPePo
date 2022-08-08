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
