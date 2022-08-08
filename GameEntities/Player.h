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
