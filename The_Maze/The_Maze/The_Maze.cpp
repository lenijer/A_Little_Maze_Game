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
#include <Windows.h>

#include "olcConsoleGameEngine.h"

class Demo : public olcConsoleGameEngine {//turtorial used: https://www.youtube.com/watch?v=cWc0hgYwZyc&list=LL&index=1
public:
    Demo() {};
};

std::vector<std::string> Menu_Options = {
    "Play Game",
    "Quit"
};

const int x = 20;
const int y = 20;

std::string Floor[x][y] = { 
                    {"W","W","W","W","W","W","W","W","W","W","W","S","W","W","W","W","W","W","W","W"},
                    {"W"," ","W"," "," "," "," "," "," "," ","W"," ","W"," "," "," ","W"," "," ","W"},
                    {"W"," "," "," ","W","W","W","W","W","W","W"," ","W"," ","W"," "," "," ","W","W"},
                    {"W"," ","W","W","W"," "," "," "," "," ","W"," ","W","W","W","W","W"," ","W","W"},
                    {"W"," "," "," "," "," ","W"," ","W"," ","W"," "," "," "," "," "," "," "," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," ","W","W","W","W","W","W"," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," ","W"," ","W"," "," "," "," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," ","W"," ","W","W","W","W"," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W"," ","W"," "," "," ","W"," "," "," "," ","W"," ","W"},
                    {"W"," ","W"," ","W"," ","W","W","W","W"," ","W","W","W","W","W"," ","W"," ","W"},
                    {"W"," ","W"," ","W"," "," "," ","W"," "," "," "," "," "," "," "," ","W"," ","W"},
                    {"W"," ","W"," ","W","W","W","W","W","W","W","W","W","W","W","W","W","W"," ","W"},
                    {"W"," ","W"," ","W"," "," "," "," "," "," "," "," ","W"," "," "," ","W","W","W"},
                    {"W"," ","W"," ","W","W","W","W","W","W","W","W"," ","W","W"," "," "," "," ","W"},
                    {"W"," ","W"," ","W"," "," "," "," "," "," "," "," "," "," "," ","W","W","W","W"},
                    {"W"," ","W","W","W"," ","W","W","W","W","W","W","W","W","W"," "," ","W"," ","W"},
                    {"W"," "," "," "," "," "," "," "," "," "," "," "," "," ","W","W"," ","W"," ","W"},
                    {"W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"," "," ","W"," ","W"},
                    {"W"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","W"},
                    {"W","E","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"}};

const char Player = 'P';
int P_x = 0; //player x
int P_y = 11; //player y

void menu();
void RunMaze();

int main()
{
    Demo game;
    game.ConstructConsole(15, 20, 8, 8);
    game.Start();
    //menu();
}

void menu() {
    const std::string Selector = "->";

    std::string DisplayText = "";
    char key;
    int Option_Select = 0;

    while (true) {
        system("cls");
        RunMaze();
        DisplayText = "Main Menu\n";

        for (int i = 0; i < Menu_Options.size(); i++) {
            if (i == Option_Select) {
                DisplayText += Selector;
            }
            DisplayText += Menu_Options[i] + "\n";
        }

        DisplayText += "W/S to move up or down, enter to select option";
        std::cout << DisplayText;
        //std::cout << "Menu size " << Menu_Options.size() << ", Current option " << Option_Select;
        key = _getch();

        if (key == 'W' || key == 'w') {
            Option_Select--;
        }
        if (key == 'S' || key == 's') {
            Option_Select++;
        }


        if (Option_Select == Menu_Options.size()) {
            Option_Select = 0;
        }

        if (Option_Select == -1) {
            Option_Select = Menu_Options.size() - 1;
        }


        if (key == '\r'/*\r = enter*/) {
            switch (Option_Select) {
            case 0:
                RunMaze();
                break;
            case 1:
                exit(0);
                break;
            default:
                break;
            }
        }
    }
}

void RunMaze() {
    char key;
    std::string Map[x][y];

    while (true) {
        system("cls");

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                Map[i][j] = Floor[i][j];
                if (i == P_x && j == P_y) {
                    Map[i][j] = Player;
                }
            }
        }

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                std::cout << Map[i][j] << " ";
            }
            std::cout << "\n";
        }


        std::cout << "\n\nGOAL: Reach E\nMove with wasd";

        key = _getch();

        if (key == 'S' || key == 's') {
            if (Map[P_x + 1][P_y] != "W") {
                P_x++;
            }
        }
        if (key == 'W' || key == 'w') {
            if ((Map[P_x - 1][P_y] != "W") && (Floor[P_x][P_y] != "S")) {
                P_x--;
            }
        }
        if (key == 'D' || key == 'd') {
            if (Map[P_x][P_y + 1] != "W") {
                P_y++;
            }
        }
        if (key == 'A' || key == 'a') {
            if (Map[P_x][P_y - 1] != "W") {
                P_y--;
            }
        }

        if (Map[P_x][P_y] == "E") {
            exit(0);
        }

        if (key == '\r' || key == '\b'/*\r = enter*/) { /*\" gives qoutes in print, \? is questionmark https://en.cppreference.com/w/cpp/language/escape*/
            break;
        }
        if ((int)key == 27) { /*https://theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html*/
            exit(0);
        }
    }
}