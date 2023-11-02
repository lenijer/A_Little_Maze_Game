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
#include "Object.h"
#include "Player.h"

std::vector<std::string> Menu_Options = {
    "Play Game",
    "Quit"
};

const int x = 20;
const int y = 20;

void menu();
void RunMaze();
void Floor1(std::string Map[x][y]);

int main()
{
    menu();
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

void menu() {
    const std::string Selector = "->";

    std::string DisplayText = "";
    char key;
    int Option_Select = 0;

    while (true) {
        system("cls");
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
    Player* Pl = new Player();
    Pl->SetCharacter('P');
    Pl->SetX(0);
    Pl->SetY(11);

    while (true) {
        system("cls");

        Floor1(Map);
        Map[Pl->GetX()][Pl->GetY()] = Pl->GetCharacter();

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                std::cout << Map[i][j] << " ";
            }
            std::cout << "\n";
        }


        std::cout << "\n\nGOAL: Reach E\nMove with wasd";

        key = _getch();

        if (key == 'S' || key == 's') {
            if (Map[Pl->GetX() + 1][Pl->GetY()] != "W") {
                Pl->SetX(Pl->GetX() + 1);
            }
        }
        if (key == 'W' || key == 'w') {
            if ((Map[Pl->GetX() - 1][Pl->GetY()] != "W") && (Pl->GetX() != 0)) {
                Pl->SetX(Pl->GetX() - 1);
            }
        }
        if (key == 'D' || key == 'd') {
            if (Map[Pl->GetX()][Pl->GetY() + 1] != "W") {
                Pl->SetY(Pl->GetY() + 1);
            }
        }
        if (key == 'A' || key == 'a') {
            if (Map[Pl->GetX()][Pl->GetY() - 1] != "W") {
                Pl->SetY(Pl->GetY() - 1);
            }
        }

        if (Map[Pl->GetX()][Pl->GetY()] == "E") {
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

void Floor1(std::string Map[x][y]) {
    Object* ny; //used to add new objects
    std::vector <Object*> Items;

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
                    {"W","E","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"} };

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            Items.push_back(ny = new Object());

            if (Floor[i][j] == "W") {
                ny->SetCharacter('W');
            }
            if (Floor[i][j] == " ") {
                ny->SetCharacter(' ');
            }
            if (Floor[i][j] == "S") {
                ny->SetCharacter('S');
            }
            if (Floor[i][j] == "E") {
                ny->SetCharacter('E');
            }

            ny->SetX(i);
            ny->SetY(j);
        }
    }

    for (int i = 0; i < Items.size(); i++) {
        Map[Items[i]->GetX()][Items[i]->GetY()] = Items[i]->GetCharacter();
    }
}