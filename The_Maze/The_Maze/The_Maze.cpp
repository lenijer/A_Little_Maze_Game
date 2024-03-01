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
#include "Basic/colour.h"
#include "Basic/pixel.h"
#include "Basic/images.h"
#include "Basic/Input.h"
#include "Object_Classes/Floor.h"

const int imagesize = 16; //fine on even numbers
//const int x = 20;
//const int y = 20;

int P_x = 0; //player x
int P_y = 11; //player y

HDC someHDC;
Input input;

images Player_image;
std::vector <images*> Objects;

int screen_x;
int screen_y;
int total_image_size;
int game_timer{ 0 };
bool run{ true };
bool fullscreen{ true };

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message)
    {
    case WM_KEYDOWN:
        if (wparam == 0x41/*A key https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes */) {
            input.A = true;
        }
        if (wparam == 0x44/*D key*/) {
            input.D = true;
        }
        if (wparam == 0x53/*S key*/) {
            input.S = true;
        }
        if (wparam == 0x57/*W key*/) {
            input.W = true;
        }
        return 0L;
        break;
    case WM_KEYUP:
        if (wparam == 0x41) {
            input.A = false;
        }
        if (wparam == 0x44) {
            input.D = false;
        }
        if (wparam == 0x53) {
            input.S = false;
        }
        if (wparam == 0x57) {
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
        
        //TextOut(hdc, 0, 0, "Hello, Windows!", 15);
        for (int i = 0; i < Objects.size(); i++ /*int i = Objects.size() - 1; i > 0; i--*/) {
            if (Player_image.get_x() == Objects[i]->get_x() && Player_image.get_y() == Objects[i]->get_y()) {
                if (Player_image.HasTransparentPixels()) {
                    int r1, g1, b1, r2, b2, g2, a; 
                    float r, g, b;
                    for (int j = 0; j < Player_image.Vector_Length(); j++) {
                        r1 = Player_image.GetPixel(j).GetColour().GetRed();
                        g1 = Player_image.GetPixel(j).GetColour().GetGreen();
                        b1 = Player_image.GetPixel(j).GetColour().GetBlue();
                        a = Player_image.GetPixel(j).GetColour().GetAlpha();

                        r2 = Objects[i]->GetPixel(Player_image.GetPixel(j).get_x(), Player_image.GetPixel(j).get_y()).GetColour().GetRed();
                        g2 = Objects[i]->GetPixel(Player_image.GetPixel(j).get_x(), Player_image.GetPixel(j).get_y()).GetColour().GetGreen();
                        b2 = Objects[i]->GetPixel(Player_image.GetPixel(j).get_x(), Player_image.GetPixel(j).get_y()).GetColour().GetBlue();

                        r = r1 * ((float)a / 255) + r2 * ((255 - (float)a) / 255);
                        g = g1 * ((float)a / 255) + g2 * ((255 - (float)a) / 255);
                        b = b1 * ((float)a / 255) + b2 * ((255 - (float)a) / 255);

                        colour c = colour((int)r, (int)g, (int)b, 255);
                        pixel p = pixel(c, Player_image.GetPixel(j).get_x(), Player_image.GetPixel(j).get_y());
                        p.drawpixel(someHDC);
                    }
                }
                else {
                    Player_image.draw(someHDC);
                }
            }
            else {
                Objects[i]->draw(someHDC);
            }
        }
        EndPaint(hwnd, &ps);
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

    Floor fl = Floor("Assets/Floors/Floor1.txt");
    //screen_x = imagesize * fl.x();
    //screen_y = imagesize * fl.y();

    if (fullscreen) {
        screen_x = GetSystemMetrics(SM_CXSCREEN); //Gets the computers screen dimentions for X
        screen_y = GetSystemMetrics(SM_CYSCREEN); //Gets the computers screen dimentions for Y
    }
    else {
        screen_x = imagesize * fl.x();
        screen_y = imagesize * fl.y();
    }

    HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_POPUP/*Don't Allow size change*/, (GetSystemMetrics(SM_CXSCREEN) / 2) - (screen_x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (screen_y / 2), screen_x, screen_y, NULL, NULL, NULL, NULL);
    //HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_OVERLAPPEDWINDOW/*allow size change*//*, (GetSystemMetrics(SM_CXSCREEN) / 2) - (x * 10 / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (y * 10 / 2), x * 10 + 100, y * 10 + 100, NULL, NULL, NULL, NULL);*/
    ShowWindow(windowHandle, SW_RESTORE);

    someHDC = GetDC(windowHandle);

    MSG messages;

    total_image_size = imagesize;
    Player_image = images("Assets/Images/Player.bmp", (P_y * total_image_size) + (total_image_size / 2), (P_x * total_image_size) + (total_image_size / 2), total_image_size);
    Player_image.layer = 1;

    images* ny = { nullptr };
    int x = total_image_size / 2;
    int y = total_image_size / 2;
    for (int i = 0; i < fl.x(); i++) {
        for (int j = 0; j < fl.y(); j++) {
            if (fl.readlocation(i, j) == 'W') {
                Objects.push_back(ny = new images("Assets/Images/Wall.bmp", x, y, total_image_size));
            }
            if (fl.readlocation(i, j) == 'E') {
                Objects.push_back(ny = new images("Assets/Images/End.bmp", x, y, total_image_size));
            }
            if (fl.readlocation(i, j) == 'S') {
                Objects.push_back(ny = new images("Assets/Images/Start.bmp", x, y, total_image_size));
            }
            if (fl.readlocation(i, j) == ' ') {
                Objects.push_back(ny = new images("Assets/Images/Floor.bmp", x, y, total_image_size));
            }
            x += total_image_size;
        }
        x = total_image_size / 2;
        y += total_image_size;
    }
    ny = new images();
    delete ny;

    while (run) {
        game_timer++;
        GetMessage(&messages, NULL, 0, 0);

        TranslateMessage(&messages);
        DispatchMessage(&messages);

        if (input.A) {
            if (fl.readlocation(P_x, P_y - 1) != 'W') {
                P_y--;
            }
        }
        if (input.D) {
            if (fl.readlocation(P_x, P_y + 1) != 'W') {
                P_y++;
            }
        }
        if (input.W) {
            if (fl.readlocation(P_x - 1, P_y) != 'W' && fl.readlocation(P_x, P_y) != 'S') {
                P_x--;
            }
        }
        if (input.S) {
            if (fl.readlocation(P_x + 1, P_y) != 'W'){
                P_x++;
            }
        }
        Player_image.move(P_y* total_image_size + total_image_size / 2, P_x* total_image_size + total_image_size / 2);
        RedrawWindow(windowHandle, NULL, NULL, RDW_INVALIDATE);
        GetMessage(&messages, NULL, 0, 0);

        TranslateMessage(&messages);
        DispatchMessage(&messages);

        if (fl.readlocation(P_x, P_y) == 'E') {
            DestroyWindow(windowHandle);
            run = false;
        }
    }

    ReleaseDC(windowHandle, someHDC);
    DeleteObject(windowHandle);
    return messages.wParam;
}