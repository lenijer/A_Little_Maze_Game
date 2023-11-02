/*
*       Made by: Lenita Njærheim
*           Created On: 28/08-2023
*           Completed: 
*       Project Name: The Maze
*/
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Window.h"

int main()
{
    FreeConsole();
    /*
    GetSystemMetrics(SM_CXSCREEN), //width of window; this function
    //retrieves the screen resolution.
    GetSystemMetrics(SM_CYSCREEN), //height of the window
    */
    Window* window = new Window(1400, 700, GetSystemMetrics(SM_CXSCREEN)/8, GetSystemMetrics(SM_CYSCREEN)/8);
    window->RunWindow();
    delete window;
}