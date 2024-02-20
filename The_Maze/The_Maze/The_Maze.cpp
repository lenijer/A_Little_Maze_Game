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

const int imagesize = 16; //fine on even numbers
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

int P_x = 0; //player x
int P_y = 11; //player y

HDC someHDC;

//pixel Player_pixel;
images Player_image;
std::vector <images*> Objects;

int screen_x;
int screen_y;
int total_image_size;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message)
    {
    case WM_KEYDOWN:
        if (wparam == 0x41/*A key https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes */) {
            if (Floor[P_x][P_y - 1] != "W")
            {
                P_y--;
            }
        }
        if (wparam == 0x44/*D key*/) {
            if (Floor[P_x][P_y + 1] != "W")
            {
                P_y++;
            }
        }
        if (wparam == 0x53/*S key*/) {
            if (Floor[P_x + 1][P_y] != "W")
            {
                P_x++;
            }
        }
        if (wparam == 0x57/*W key*/) {
            if (Floor[P_x - 1][P_y] != "W")
            {
                P_x--;
            }
        }
        //Player_pixel.move(P_y * pixelsize, P_x * pixelsize);
        Player_image.move(P_y * total_image_size + total_image_size / 2, P_x * total_image_size + total_image_size / 2);
        //SendMessage(hwnd, WM_PAINT, wparam, lparam);
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

    screen_x = imagesize * x;
    screen_y = imagesize * y;
    HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_POPUP/*Don't Allow size change*/, (GetSystemMetrics(SM_CXSCREEN) / 2) - (screen_x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (screen_y / 2), screen_x, screen_y, NULL, NULL, NULL, NULL);
    //HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_OVERLAPPEDWINDOW/*allow size change*//*, (GetSystemMetrics(SM_CXSCREEN) / 2) - (x * 10 / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (y * 10 / 2), x * 10 + 100, y * 10 + 100, NULL, NULL, NULL, NULL);*/
    ShowWindow(windowHandle, SW_RESTORE);

    someHDC = GetDC(windowHandle);

    MSG messages;

    total_image_size = imagesize;
    //Player_pixel = pixel(colour(0, 0, 255), P_y * pixelsize, P_x * pixelsize, pixelsize);
    //Player_image = images(P_y * total_image_size + total_image_size / 2, P_x * total_image_size + total_image_size / 2, colour(0, 0, 255), total_image_size);
    Player_image = images("Assets/Images/HalfTransparent.bmp", P_y * total_image_size + total_image_size / 2, P_x * total_image_size + total_image_size / 2, total_image_size);
    Player_image.layer = 1;

    images* ny = { nullptr };
    for (int lx = 0; lx < screen_x; lx += total_image_size) {
        for (int ly = 0; ly < screen_y; ly += total_image_size) {
            if (Floor[(ly) / (total_image_size)][(lx) / (total_image_size)] == "W") {
                //Objects.push_back(ny = new pixel(colour(0, 0, 0), lx, ly, pixelsize));
                Objects.push_back(ny = new images("Assets/Images/Wall.bmp", lx + total_image_size / 2, ly + total_image_size / 2, total_image_size));
            }
            if (Floor[(ly) / (total_image_size)][(lx) / (total_image_size)] == "E") {
                //Objects.push_back(ny = new pixel(colour(0, 255, 0), lx, ly, pixelsize));
                Objects.push_back(ny = new images("Assets/Images/End.bmp", lx + total_image_size / 2, ly + total_image_size / 2, total_image_size));
            }
            if (Floor[(ly) / (total_image_size)][(lx) / (total_image_size)] == "S") {
                //Objects.push_back(ny = new pixel(colour(255, 200, 0), lx, ly, pixelsize));
                Objects.push_back(ny = new images("Assets/Images/Start.bmp", lx + total_image_size / 2, ly + total_image_size / 2, total_image_size));
            }
            if (Floor[(ly) / (total_image_size)][(lx) / (total_image_size)] == " ") {
                //Objects.push_back(ny = new pixel(colour(255, 255, 255), lx, ly, pixelsize));
                Objects.push_back(ny = new images("Assets/Images/Floor.bmp", lx + total_image_size / 2, ly + total_image_size / 2, total_image_size));
            }
        }
    }
    ny = new images();
    delete ny;

    while (GetMessage(&messages, NULL, 0, 0) > 0) {

        TranslateMessage(&messages);
        DispatchMessage(&messages);

        RedrawWindow(windowHandle, NULL, NULL, RDW_INVALIDATE);

        if (Floor[P_x][P_y] == "E") {
            DestroyWindow(windowHandle);
        }
    }

    ReleaseDC(windowHandle, someHDC);
    DeleteObject(windowHandle);
    return messages.wParam;
}