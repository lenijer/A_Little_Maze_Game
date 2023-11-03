/*
*       Made by: Lenita Nj�rheim
*           Created On: 12/10-2023
*           Completed: 02/11-2023
*       Project Name: The Maze
*           File: Window.cpp
*           turtoral used https://cplusplus.com/forum/windows/219154/
*			turtorial written(by, when): Troaat, 18/07-2017
*/
#include "Window.h"
#include "Input.h"

Window::Window(int sizeX, int sizeY, int SpawnLocX, int SpawnLocY) {
	Xsize = sizeX;
	Ysize = sizeY;
    ScreenLocX = SpawnLocX;
    ScreenLocY = SpawnLocY;
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
    case WM_PAINT: //https://learn.microsoft.com/en-us/windows/win32/learnwin32/painting-the-window
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Pixel P(100, 100, 50, 50, new Color(0, 0, 255));

        RECT A = P.GetPixel();

        FillRect(hdc, &A, (HBRUSH)CreateSolidBrush(P.PixelColor->HexColor()));

        Pixel K(100, 100, 300, 300, new Color(0, 255, 0));

        RECT L = K.GetPixel();

        FillRect(hdc, &L, (HBRUSH)CreateSolidBrush(K.PixelColor->HexColor()));

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CHAR:
        if (wparam == 0x1B) {
            DestroyWindow(hwnd);
        }
        if (wparam == 0x41/*A key https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes*/) {
            //Input.A = true;
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
    HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_POPUP, ScreenLocX, ScreenLocY, Xsize, Ysize, NULL, NULL, NULL, NULL);
    ShowWindow(windowHandle, SW_RESTORE);

    MSG messages;
    while (GetMessage(&messages, NULL, 0, 0) > 0) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    DeleteObject(windowHandle);
    return messages.wParam;
}