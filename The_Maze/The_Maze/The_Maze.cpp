/*
*       Made by: Lenita Njærheim
*           Created On: 28/08-2023
*           Completed: 
*       Project Name: The Maze
*/
//Basic includes
#include <string>
#include <Windows.h>
#include <vector>

//Selfmade classes
#include "zone.h"
#include "Basic/colour.h"
#include "Basic/pixel.h"
#include "Basic/images.h"
#include "Basic/Input.h"
#include "Object_Classes/Floor.h"
#include "Object_Classes/Object.h"

const int imagesize = 16; //fine on even numbers
const int Objects_Per_Zone = 100;

HDC someHDC;
Input input;

std::vector <Object*> Objects;
std::vector <images*> Image;
std::vector <Floor> fl;
std::vector <zone*> zones;
zone* textzone;

int screen_x;
int screen_y;
int total_image_size;
//int game_timer{ 0 };
bool run{ true };
bool fullscreen{ false };
bool redraw_nessesary{ false };
int floor_index{ 0 };
bool first_draw{ true };
bool Player_changedZone{ false };
int player_prev_Zone{ 0 };
int player_current_zone{ 0 };
bool textchange{ true };
std::wstring TextOutput_WS = L"";

void Draw() {
    if (first_draw)
    {
        for (int i = 0; i < zones.size(); i++) {
            if (first_draw && zones[i]->Objects_size() > 0) {
                zones[i]->Draw(someHDC);
            }
        }
        first_draw = false;
        return;
    }
    zones[player_current_zone]->Draw(someHDC);

    if (Player_changedZone) {
        zones[player_prev_Zone]->Draw(someHDC);
        Player_changedZone = false;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message)
    {
    case WM_KEYDOWN:
        if (wparam == 0x41/*A key https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes */ || wparam == 0x25 /*left arrow key*/) {
            input.A = true;
        }
        if (wparam == 0x44/*D key*/ || wparam == 0x27 /*right arrow key*/) {
            input.D = true;
        }
        if (wparam == 0x53/*S key*/ || wparam == 0x28 /*down arrow key*/) {
            input.S = true;
        }
        if (wparam == 0x57/*W key*/ || wparam == 0x26 /*up arrow key*/) {
            input.W = true;
        }
        return 0L;
        break;
    case WM_KEYUP:
        if (wparam == 0x41 || wparam == 0x25) {
            input.A = false;
        }
        if (wparam == 0x44 || wparam == 0x27) {
            input.D = false;
        }
        if (wparam == 0x53 || wparam == 0x28) {
            input.S = false;
        }
        if (wparam == 0x57 || wparam == 0x26) {
            input.W = false;
        }
        return 0L;
        break;
    case  WM_ERASEBKGND:
        return 0L;
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
        ps.fErase = true;
        BeginPaint(hwnd, &ps);
        
        Draw();

        if (textchange) {
            textzone->Background_Draw(Image[6], someHDC); //background is white untill i figure out how to change it
            textzone->WriteText(TextOutput_WS, someHDC);
            textchange = false;
        }

        EndPaint(hwnd, &ps);
        redraw_nessesary = false;
        return 0L;
        break; 
    case WM_CHAR:
        if (wparam == VK_ESCAPE) {
            DestroyWindow(hwnd);
            run = false;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
        break;
    }
    return 0L;
}

int index_count = { 0 };
void zoneGen(int index,/**/ int y_0, int y_1, int x_0, int x_1) {
    int height = y_1 - y_0;
    int width = x_1 - x_0;
    zones.push_back(new zone(y_0, y_1, x_1, x_0));
    for (int i = 1; i < Objects.size(); i++) {
        if (zones[index]->Is_in_zone(Objects[i])) {
            zones[index]->addObject(Objects[i]);
        }
    }
    if (zones[index]->Has_Max_Objects(Objects_Per_Zone)) {
        index_count++;
        zoneGen(index_count,/**/ y_0, y_0 + height / 2, x_0, x_0 + width / 2);
        index_count++;
        zoneGen(index_count,/**/ y_0 + height / 2, y_1, x_0, x_0 + width / 2);
        index_count++;
        zoneGen(index_count,/**/ y_0, y_0 + height / 2, x_0 + width / 2, x_1);
        index_count++;
        zoneGen(index_count,/**/ y_0 + height / 2, y_1, x_0 + width / 2, x_1);
        zones[index]->Delete();
    }
}

void floorsetup(int floor_num) {
    first_draw = true;
    index_count = 0;
    for (int i = 0; i < zones.size(); i++) {
        zones[i]->Delete();
        delete zones[i];
    }
    zones.clear();
    for (int i = 0; i < Objects.size(); i++) {
        delete Objects[i];
    }
    Objects.clear();

    char c = floor_num + 49;
    std::string simplestring = "  ";
    simplestring[1] = c;
    //https://stackoverflow.com/questions/10737644/convert-const-char-to-wstring
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &simplestring[0], (int)simplestring.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &simplestring[0], (int)simplestring.size(), &wstrTo[0], size_needed);
    TextOutput_WS = L"Current Floor:" + wstrTo;
    textchange = true;

    Object* ny = { nullptr };
    Objects.push_back(ny = new Object(Image[0], 0, 0, imagesize, imagesize));
    ny->layer = 2;
    ny->Name = "Player";
    int x = total_image_size / 2;
    int y = total_image_size / 2;
    for (int i = 0; i < fl[floor_num].x(); i++) {
        for (int j = 0; j < fl[floor_num].y(); j++) {
            if (fl[floor_num].readlocation(i, j) == 'W') {
                Objects.push_back(ny = new Object(Image[4], x, y, imagesize, imagesize));
                ny->Name = "Wall";
                ny->collideableobject = true;
            }
            if (fl[floor_num].readlocation(i, j) == 'E') {
                if (floor_num < fl.size() - 1) {
                    Objects.push_back(ny = new Object(Image[5], x, y, imagesize, imagesize)); //Stair Object
                    ny->Name = "Stair";
                }
                else {
                    Objects.push_back(ny = new Object(Image[1], x, y, imagesize, imagesize)); //End Object
                    ny->Name = "End";
                }
                ny->layer = 1;
                ny->collideableobject = true;
                Objects.push_back(ny = new Object(Image[3], x, y, imagesize, imagesize)); //Floor
            }
            if (fl[floor_num].readlocation(i, j) == 'S') {
                Objects.push_back(ny = new Object(Image[2], x, y, imagesize, imagesize)); //Start Object
                ny->collideableobject = true;
                ny->Name = "Start";
                ny->layer = 1;
                Objects.push_back(ny = new Object(Image[3], x, y, imagesize, imagesize)); //Floor
                Objects[0]->move(x, y);
            }
            if (fl[floor_num].readlocation(i, j) == ' ') {
                Objects.push_back(ny = new Object(Image[3], x, y, imagesize, imagesize));
            }
            x += total_image_size;
        }
        x = total_image_size / 2;
        y += total_image_size;
    }
    ny = new Object();
    delete ny;

    textzone = new zone(imagesize * fl[0].y(), screen_y, screen_x, 0);

    zoneGen(0,/**/ 0, screen_y - 100, 0, screen_x);
    for (int i = 0; i < zones.size(); i++) {
        if (zones[i]->Is_in_zone(Objects[0]) && zones[i]->Objects_size() > 0) {
            player_current_zone = i;
            break;
        }
    }
    zones[player_current_zone]->addPlayer(Objects[0]);
}

void Collision() {
    int movement_change_x = Objects[0]->x(); //Object[0] is the player
    int movement_change_y = Objects[0]->y();
    bool hit{ false };
    if (input.A) {
        movement_change_x -= total_image_size;
    }
    if (input.D) {
        movement_change_x += total_image_size;
    }
    if (input.W) {
        movement_change_y -= total_image_size;
    }
    if (input.S) {
        movement_change_y += total_image_size;
    }
    //check for collision
    for (int i = 0; i < Objects.size(); i++) {
        if (Objects[i]->collideableobject) {
            if ((Objects[i]->right_collider() > movement_change_x && Objects[i]->left_collider() < movement_change_x) &&
                (Objects[i]->bottom_collider() > movement_change_y && Objects[i]->top_collider() < movement_change_y)) {
                if (Objects[i]->Name == "End") {
                    run = false;
                }
                if (Objects[i]->Name == "Stair") {
                    floor_index++;
                    floorsetup(floor_index);
                    redraw_nessesary = true;
                    return;
                }
                else {
                    hit = true;
                }
                break;
            }
        }
    }
    //Collision Event
    if (!hit) {
        Objects[0]->move(movement_change_x, movement_change_y);
        for (int i = 0; i < zones.size(); i++) {
            if (zones[i]->find_Player(Objects[0]) && (!zones[i]->Is_in_zone(Objects[0]))) {
                player_prev_Zone = i;
                for (int j = 0; j < zones.size(); j++) {
                    if (zones[j]->Is_in_zone(Objects[0]) && zones[i]->Objects_size() > 0) {
                        player_current_zone = j;
                        Player_changedZone = true;
                    }
                }
            }
        }
        if (Player_changedZone) {
            zones[player_prev_Zone]->Remove_Player();
            zones[player_current_zone]->addPlayer(Objects[0]);
        }
        redraw_nessesary = true;
    }
}

int main()
{
    FreeConsole();

    WNDCLASS windowClass = {0};
    windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = NULL;
    windowClass.lpfnWndProc = WndProc;
    windowClass.lpszClassName = L"Window in Console"; //"Window in Console"
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&windowClass)) {
        MessageBox(NULL, L"Could not register class", L"Error", MB_OK);
    }

    fl.push_back(Floor("Assets/Floors/Floor1.txt"));
    fl.push_back(Floor("Assets/Floors/Floor2.bmp"));

    if (fullscreen) {
        screen_x = GetSystemMetrics(SM_CXSCREEN); //Gets the computers screen dimentions for X
        screen_y = GetSystemMetrics(SM_CYSCREEN); //Gets the computers screen dimentions for Y
    }
    else {
        screen_x = imagesize * fl[0].x();
        screen_y = imagesize * fl[0].y() + 100;
    }

    HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_POPUP/*Don't Allow size change*/, (GetSystemMetrics(SM_CXSCREEN) / 2) - (screen_x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (screen_y / 2), screen_x, screen_y, NULL, NULL, NULL, NULL);
    //HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_OVERLAPPEDWINDOW/*allow size change*//*, (GetSystemMetrics(SM_CXSCREEN) / 2) - (x * 10 / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (y * 10 / 2), x * 10 + 100, y * 10 + 100, NULL, NULL, NULL, NULL);*/
    ShowWindow(windowHandle, SW_RESTORE);

    someHDC = GetDC(windowHandle);

    MSG messages;

    images* im = { nullptr };
    Image.push_back(im = new images("Assets/Images/Player.bmp"));
    Image.push_back(im = new images("Assets/Images/End.bmp"));
    Image.push_back(im = new images("Assets/Images/Start.bmp"));
    Image.push_back(im = new images("Assets/Images/Floor.bmp"));
    Image.push_back(im = new images("Assets/Images/Wall.bmp"));
    Image.push_back(im = new images("Assets/Images/Stair.bmp"));
    Image.push_back(im = new images("Assets/Images/DefaultBackground.bmp"));
    im = new images();
    delete im;

    total_image_size = imagesize;

    floorsetup(floor_index/**/);

    while (run) {
        GetMessage(&messages, NULL, 0, 0);

        TranslateMessage(&messages);
        DispatchMessage(&messages);

        Collision();

        if (redraw_nessesary)
        {
            RedrawWindow(windowHandle, NULL, NULL, RDW_INVALIDATE);
            GetMessage(&messages, NULL, 0, 0);

            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
        //game_timer++;
    }

    DestroyWindow(windowHandle);

    ReleaseDC(windowHandle, someHDC);
    DeleteObject(windowHandle);
    return messages.wParam;
}