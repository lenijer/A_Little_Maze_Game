/*
*       Made by: Lenita Njærheim
*           Created On: 12/10-2023
*           Completed: 02/11-2023
*       Project Name: The Maze
*           File: Window.cpp
*/
#include "Window.h"
#include <thread>

Player* PL;
bool change{ true };
std::vector<Object> Objects;

Window::Window(int sizeX, int sizeY, int SpawnLocX, int SpawnLocY) {
	Xsize = sizeX;
	Ysize = sizeY;
    ScreenLocX = SpawnLocX;
    ScreenLocY = SpawnLocY;

    std::string temp;

    Color Wall = Color(255, 0, 0);
    Color Start = Color(255, 200, 0);
    Color End = Color(0, 255, 0);
    Color Path = Color(255, 255, 255);

    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            temp = Stage[y][x];
            Object* ny = new Object();
            ny->SetX(x);
            ny->SetY(y);

            if (temp == "W") {
                ny->SetPixel(Pixel(10, 10, x * 10 + 5, y * 10 + 5, Wall));
                ny->SetName("Wall");
            }
            if (temp == " ") {
                ny->SetPixel(Pixel(10, 10, x * 10 + 5, y * 10 + 5, Path));
                ny->SetName("Path");
            }
            if (temp == "S") {
                ny->SetPixel(Pixel(10, 10, x * 10 + 5, y * 10 + 5, Start));
                ny->SetName("Start");
            }
            if (temp == "E") {
                ny->SetPixel(Pixel(10, 10, x * 10 + 5, y * 10 + 5, End));
                ny->SetName("Finish");
            }
            Objects.push_back(*ny);
            delete ny;
        }
    }

    PL = new Player();
    PL->SetName("Player");

    for (int i = 0; i < Objects.size(); i++) {
        if (Objects[i].GetName() == "Start") {
            PL->SetX(Objects[i].GetX());
            PL->SetY(Objects[i].GetY());
            PL->SetPixel(Pixel(10, 10, Objects[i].GetX() * 10 + 5, Objects[i].GetY() * 10 + 5, Color(0, 0, 255)));
        }
    }
}

Window::~Window()
{

}

void OnSize(HWND hwnd, UINT flag, int width, int height)
{
    // Handle resizing
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message)
    {
    case WM_SIZE:
    {
        int width = LOWORD(lparam);  // Macro to get the low-order word.
        int height = HIWORD(lparam); // Macro to get the high-order word.

        // Respond to the message:
        OnSize(hwnd, (UINT)wparam, width, height);
    }
    break;
    case WM_KEYDOWN:
        if (!change) {
            if (wparam == VK_DOWN) {
                //PL->Move(0, 1);
                //change = true;
                //wparam = WM_PAINT;
            }
            if (wparam == VK_UP) {
                //PL->Move(0, -1);
                //change = true;
            }
            if (wparam == VK_LEFT) {
                //PL->Move(-1, 0);
                //change = true;

            }
            if (wparam == VK_RIGHT) {
                //PL->Move(1, 0);
                //change = true;
            }
            if (wparam == 0x41/*A key https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes*/) {
                PL->Move(-1, 0);
                change = true;
                //Input.A = true;
            }
            if (wparam == 0x44/*D key*/) {
                PL->Move(1, 0);
                change = true;
            }
            if (wparam == 0x53/*S key*/) {
                PL->Move(0, 1);
                change = true;
            }
            if (wparam == 0x57/*W key*/) {
                PL->Move(0, -1);
                change = true;
            }
        }
        break;
    case WM_PAINT: //https://learn.microsoft.com/en-us/windows/win32/learnwin32/painting-the-window
    {

    }
    break;
    case WM_CHAR:
        if (wparam == VK_ESCAPE) {
            DestroyWindow(hwnd);
        }
        /**if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }*/
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
    }
    return 0;
}

void Draw(HWND window) {
    HDC someHDC = GetDC(window);

    PAINTSTRUCT ps;
    //HDC hdc = 
    BeginPaint(window, &ps);

    for (int i = 0; i < Objects.size(); i++) {
        if (PL->GetX() == Objects[i].GetX() && PL->GetY() == Objects[i].GetY()) {
            Pixel P = PL->ReturnPixel();
            RECT A = P.GetPixel();
            FillRect(someHDC, &A, (HBRUSH)CreateSolidBrush(P.PixelColor.HexColor()));
        }
        else {
            Pixel P = Objects[i].ReturnPixel();
            RECT A = P.GetPixel();
            FillRect(someHDC, &A, (HBRUSH)CreateSolidBrush(P.PixelColor.HexColor()));
        }
    }

    EndPaint(window, &ps);

    ReleaseDC(window, someHDC);
}

bool Window::RunWindow() {
    WNDCLASS windowClass = { 0 };
    windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = NULL;
    windowClass.lpfnWndProc = WndProc;
    windowClass.lpszClassName = L"Window in Console"; //"Window in Console"
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&windowClass)) {
        MessageBox(NULL, L"Could not register class", L"Error", MB_OK);
    }
    HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_POPUP/*Don't Allow size change*/, ScreenLocX - (Xsize / 2), ScreenLocY - (Ysize / 2), Xsize, Ysize, NULL, NULL, NULL, NULL);
    ShowWindow(windowHandle, SW_RESTORE);

    MSG messages;
    HWND hwndDlgModeless = NULL;
    HACCEL haccel = NULL;

    //std::thread T_Draw(Draw, windowHandle);
    Draw(windowHandle);

    while (GetMessage(&messages, windowHandle, WM_KEYFIRST, WM_KEYLAST) > 0) {

        if (hwndDlgModeless == (HWND)NULL ||
            !IsDialogMessage(hwndDlgModeless, &messages) &&
            !TranslateAccelerator(windowHandle, haccel,
                &messages))
        {
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }

        //drawing whithout WM_PAINT: https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-without-the-wm-paint-message
        if (change){
            //T_Draw.join();
            Draw(windowHandle);
            //InvalidateRect(windowHandle, &Inv, true);
            change = false;
            //ValidateRect(windowHandle, &Inv);
        }
    }
    DeleteObject(windowHandle);
    return messages.wParam;
    //return true;
}