#ifndef PXSYSTEM
#define PXSYSTEM

//draws the game to screen by modifying the pixel buffer
class PxSystem{

    public :

        PxSystem(unsigned int* pxStart,int pxW,int pxH); //takes reference to pixel buffer and size of pixel space as input
        ~PxSystem();
        void drawBackground();
        void drawSprite(int x, int y, int bSize, unsigned int c1, unsigned int c2); //all sprites follow the same bordered square pattern

    private :

        unsigned int** px; //2D representation of pixel buffer
        int w; //width of pixel space
        int h; //height of pixel space

};


#endif
