#ifndef COIN
#define COIN

#include "Bad.h" //includes player.h

//objective for the player to collect
class Coin{

public:

    Coin();
    ~Coin();

    //getters
    int getX(){return x;};
    int getY(){return y;};
    int getScore(){return score;};

    //run game events for the coin object
    void run(Player* playPtr, Bad** bad);

private:

    //coin's position
    int x;
    int y;
    int score = 0; //players score

};


#endif
