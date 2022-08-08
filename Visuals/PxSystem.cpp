#include "PxSystem.h"

//sets local knowledge of pixel space and creates a 2D representation of the pixel buffer
PxSystem::PxSystem(unsigned int* pxStart,int pxW, int pxH){
    //store width and height of pixel canvas locally
    w = pxW;
    h = pxH;
    //define pointer system for pixels
    px = new unsigned int*[pxH];
    for (int i=0;i<pxH;i++){
        px[i] = &pxStart[i*pxW];
    }
}

//must deallocate local pointers, but not the pixel buffer itself
PxSystem::~PxSystem(){
    //pixel memory is freed at the end of the entry point cpp file
    for (int i=0;i<h;i++){
        px[i] = nullptr;
    }
    delete[] px; //have to deallocate 2D pixel pointers though
    px = nullptr;
}

//clears the pixel buffer to a background of light grey squares
void PxSystem :: drawBackground(){
    for (int j=0;j<(h/16);j++){
        for (int i=0;i<(w/16);i++){
            drawSprite(i*16, j*16, 1, 0x00aaaaaa, 0x00333333);
        }
    }
}

//draws a square bordered sprite at a given pixel position
void PxSystem :: drawSprite(int x, int y, int bSize, unsigned int c1, unsigned int c2){
    unsigned int c;
    for (int j=0; j<16; j++){
        for (int i=0;i<16;i++){
            if (j<bSize || j>=16-bSize || i<bSize  || i>=16-bSize){
                c = c2; //set to border colour
            } else {
                c = c1; //set to fill colour
            }
            px[j+y][i+x] = c; //set pixel buffer pixel to the correct colour
        }
    }
}
