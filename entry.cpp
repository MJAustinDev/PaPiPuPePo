
#include <windows.h>
#include <ctime>
#include "string.h"
using namespace std;

#include "ObjSystem.h" //includes PxSystem.h as well as all of the game entity headers
#include "Resources.h" //used for game's icon

//globally scoped vars
bool running = true;
unsigned int* pxPure; //pure pixel buffer 1D
const int pxW = 480,pxH = 320; //game rendered px size
int scrW = 640, scrH = 480; //screen px size

//callback function
LRESULT CALLBACK winCall(HWND hand, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_CLOSE : {running=false; return 0;} //return 0 so the pop up appears before the window dies
        case WM_DESTROY : {running=false; break;}
        case WM_SIZE : {
            RECT rect;
            GetClientRect(hand,&rect);
            scrW = rect.right - rect.left;
            scrH = rect.bottom - rect.top;
            break;}
        case WM_PAINT : {
            PAINTSTRUCT canvas;
            HDC hdc = BeginPaint(hand,&canvas);
            HBITMAP pxBmp = CreateBitmap(pxW,pxH,1,32,pxPure);
            HDC srcHdc = CreateCompatibleDC(hdc);
            SelectObject(srcHdc,pxBmp);
            StretchBlt(hdc,0,0,scrW,scrH,srcHdc,0,0,pxW,pxH,SRCCOPY); //copy pixel buffer to screen
            DeleteDC(srcHdc);
            EndPaint(hand,&canvas);
            break;}
    }
    return DefWindowProc (hand, msg, wParam, lParam);
}


//entry point and creation of window
int WinMain (HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nCmdShow){

    //seed random
    srand(time(NULL));

    //define window class
    WNDCLASS winClass = {};
    winClass.style = CS_HREDRAW | CS_VREDRAW;
    winClass.lpszClassName = "Window Class";
    winClass.lpfnWndProc = winCall;
    winClass.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(gameiconID)); //set games icon

    //register class
    RegisterClass(&winClass);

    //create window
    HWND window = CreateWindow(winClass.lpszClassName,"PaPiPuPePo",WS_OVERLAPPEDWINDOW | WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,scrW,scrH,0,0,hInst,0);

    //vars for user input control
    bool keys[4] = {false, false, false, false};
    bool* keyPtr = nullptr;

    //vars for game config
    pxPure = new unsigned int[pxW*pxH]; //define pixel space in memory
    PxSystem ctrlPx(pxPure, pxW, pxH); //pixel control system
    ObjSystem ctrlObj(&keys[0]); //object control system (game manager)

    //timer to refresh the screen and slow down game speed
    SYSTEMTIME timer;
    GetSystemTime(&timer);
    WORD release = timer.wMilliseconds;
    WORD hold;

    //main game loop
    while (running){

        //handle user key input
        MSG message;
        while (PeekMessage(&message, window, 0,0,PM_REMOVE)){
            int ascii = -1;
            int action = -1;
            switch(message.message){
                case WM_KEYDOWN : {
                    ascii = message.wParam;
                    action = 1; //1 for pressed (true)
                    break;
                }
                case WM_KEYUP : {
                    ascii = message.wParam;
                    action = 0; //0 for release (false)
                    break;
                }
            }
            switch (ascii){
                case 65 : {keyPtr = &keys[0]; break;} //A is pressed
                case 68 : {keyPtr = &keys[1]; break;} //D is pressed
                case 83 : {keyPtr = &keys[2]; break;} //S is pressed
                case 87 : {keyPtr = &keys[3]; break;} //W is pressed
                default : {keyPtr = nullptr;} //non of the above have been pressed
            }
            if (keyPtr!=nullptr){
                *keyPtr = (bool)action; //set key as either pressed(1) or released(0)
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        //process game timer
        GetSystemTime(&timer);
        hold = timer.wMilliseconds;
        //handle timer overflow
        if (hold < release){
            hold = hold + 999;
        }
        //60 fps give or take
        if (hold > release + 17){
            //run game events
            running = running && ctrlObj.run(); //need to && so that killing the window kills the game loop too
            //draw game world to pixel buffer
            ctrlObj.draw(&ctrlPx);
            //update screen with newly modified pixel buffer
            InvalidateRect(window,0,true);
            //reset timer for next game cycle
            GetSystemTime(&timer);
            release = timer.wMilliseconds;
        }

    }

    //display score in message box
    string text = "Score: " + to_string(ctrlObj.getScore()) + "\nPress OK to exit!";
    MessageBox(nullptr, text.c_str(), "PaPiPuPePo", MB_OK);

    //destroy window
    DestroyWindow(window);

    //clean up
    delete[] pxPure;

    return 0;
}
