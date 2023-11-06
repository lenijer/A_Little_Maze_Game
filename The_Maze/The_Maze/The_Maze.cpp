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
    //menu();
    FreeConsole();
    /*
    GetSystemMetrics(SM_CXSCREEN), //width of window; this function
    //retrieves the screen resolution.
    GetSystemMetrics(SM_CYSCREEN), //height of the window
    */
    Window* window = new Window(200, 200, GetSystemMetrics(SM_CXSCREEN)/2, GetSystemMetrics(SM_CYSCREEN)/2);
    window->RunWindow();
    delete window;
}