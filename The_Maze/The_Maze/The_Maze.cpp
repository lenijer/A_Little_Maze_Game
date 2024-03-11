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
#include "Object_Classes/Object.h"

const int imagesize = 16; //fine on even numbers

int P_x = 0; //player x
int P_y = 11; //player y

HDC someHDC;
Input input;

std::vector <Object*> Objects;
std::vector <images*> Image;

int screen_x;
int screen_y;
int total_image_size;
int game_timer{ 0 };
bool run{ true };
bool fullscreen{ false };
bool redraw_nessesary{ false };

images* blend_images(images* i1, images* i2) {
    std::vector <pixel*> pix_arr;
    int r1, g1, b1, r2, b2, g2, a;
    float r, g, b;
    for (int k = 0; k < i1->Vector_Length(); k++) {
        r1 = i1->GetPixel(k).GetColour().GetRed();
        g1 = i1->GetPixel(k).GetColour().GetGreen();
        b1 = i1->GetPixel(k).GetColour().GetBlue();
        a = i1->GetPixel(k).GetColour().GetAlpha();

        r2 = i2->GetPixel(i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y()).GetColour().GetRed();
        g2 = i2->GetPixel(i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y()).GetColour().GetGreen();
        b2 = i2->GetPixel(i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y()).GetColour().GetBlue();

        r = r1 * ((float)a / 255) + r2 * ((255 - (float)a) / 255);
        g = g1 * ((float)a / 255) + g2 * ((255 - (float)a) / 255);
        b = b1 * ((float)a / 255) + b2 * ((255 - (float)a) / 255);

        colour c = colour((int)r, (int)g, (int)b, 255);
        pixel* p = new pixel(c, i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y());
        pix_arr.push_back(p);
    }
    return new images(pix_arr);
}

void Draw() {
    Object* tmp;
    std::vector <Object*> O;
    bool weird = false;

    for (int i = 0; i < Objects.size(); i++) {
        tmp = Objects[i];
        if (O.size() > 0) {
            for (int j = 0; j < O.size(); j++) {
                if (tmp->x() == O[j]->x() && tmp->y() == O[j]->y()) {
                    weird = true;
                    if (tmp->layer > O[j]->layer) {
                        if (tmp->image()->HasTransparentPixels()) {
                            tmp->add_temp_image(blend_images(tmp->image(), O[j]->image()));
                        }
                        O[j] = tmp;
                    }
                    else
                    {
                        if (O[j]->image()->HasTransparentPixels()) {
                            O[j]->add_temp_image(blend_images(O[j]->image(), tmp->image()));
                        }
                    }
                }
            }
        }
        if (!weird) {
            O.push_back(tmp);
        }
        weird = false;
    }
    for (int i = 0; i < O.size(); i++) {
        O[i]->draw_Object(someHDC);
    }
}

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
        Draw();

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
            //std::string h = "Hello There";
            if ((Objects[i]->right_collider() > movement_change_x && Objects[i]->left_collider() < movement_change_x) &&
                (Objects[i]->bottom_collider() > movement_change_y && Objects[i]->top_collider() < movement_change_y)) {
                //std::string h1 = "General Kenobi";
                if (Objects[i]->Name == "End") {
                    run = false;
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

    Floor fl = Floor("Assets/Floors/Floor1.txt");

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

    images* im = { nullptr };
    Image.push_back(im = new images("Assets/Images/Player.bmp"));
    Image.push_back(im = new images("Assets/Images/End.bmp"));
    Image.push_back(im = new images("Assets/Images/Start.bmp"));
    Image.push_back(im = new images("Assets/Images/Floor.bmp"));
    Image.push_back(im = new images("Assets/Images/Wall.bmp"));
    im = new images();
    delete im;

    total_image_size = imagesize;

    Object* ny = { nullptr };
    Objects.push_back(ny = new Object(Image[0], (P_y * total_image_size) + (total_image_size / 2), (P_x * total_image_size) + (total_image_size / 2)));
    ny->layer = 2;
    ny->Name = "Player";
    int x = total_image_size / 2;
    int y = total_image_size / 2;
    for (int i = 0; i < fl.x(); i++) {
        for (int j = 0; j < fl.y(); j++) {
            if (fl.readlocation(i, j) == 'W') {
                Objects.push_back(ny = new Object(Image[4], x, y));
                ny->Name = "Wall";
                ny->collideableobject = true;
            }
            if (fl.readlocation(i, j) == 'E') {
                Objects.push_back(ny = new Object(Image[1], x, y)); //End Object
                ny->Name = "End";
                ny->layer = 1;
                ny->collideableobject = true;
                Objects.push_back(ny = new Object(Image[3], x, y)); //Floor
            }
            if (fl.readlocation(i, j) == 'S') {
                Objects.push_back(ny = new Object(Image[2], x, y)); //Start Object
                ny->collideableobject = true;
                ny->Name = "Start";
                ny->layer = 1;
                Objects.push_back(ny = new Object(Image[3], x, y)); //Floor
            }
            if (fl.readlocation(i, j) == ' ') {
                Objects.push_back(ny = new Object(Image[3], x, y));
            }
            x += total_image_size;
        }
        x = total_image_size / 2;
        y += total_image_size;
    }
    ny = new Object();
    delete ny;

    while (run) {
        game_timer++;
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
    }

    DestroyWindow(windowHandle);

    ReleaseDC(windowHandle, someHDC);
    DeleteObject(windowHandle);
    return messages.wParam;
}