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

std::vector<std::string> Menu_Options = {
    "Play Game",
    "Quit"
};

void menu();

int main()
{
    menu();
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
        key = _getch();

        if (key == 'W' || key == 'w') {
            Option_Select++;
        }
        if (key == 'S' || key == 's') {
            Option_Select--;
        }


        if (Option_Select > Menu_Options.size() - 1) {
            Option_Select = 0;
        }
        if (Option_Select < 0) {
            Option_Select = Menu_Options.size() - 1;
        }

        if (key == '\r'/*\r = enter*/) {
            break;
        }
    }
}
