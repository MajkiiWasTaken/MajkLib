#include "MajkLib.h"

static HWND hWnd;
static UInt8 running = 1;

// Window methods

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg) {
        case WM_DESTROY:
            running = 0;
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void OpenWindow(UInt16 width, UInt16 height, const char* title){
    WNDCLASS wc = {0};
    
    wc.lpfnWndProc = WindowProc;
    wc.lpszClassName = "MajkLibWindowClass";

    RegisterClass(&wc);

    hWnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        NULL, 
        NULL, 
        GetModuleHandle(NULL),
        NULL
    );

    ShowWindow(hWnd, SW_SHOW);
}

void ProcessWindow(){
    MSG msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

UInt8 WindowShouldClose(){
    return !running;
}

void MajkCloseWindow(){
    DestroyWindow(hWnd);
}




// Utility methods
void SplitString(const char *str, char delimiter, char** output, UInt64 *count) {

}

Int32 ClampInt32(Int32 *value, Int32 min, Int32 max) {
    if (*value < min) {
        *value = min;
    } else if (*value > max) {
        *value = max;
    }
    return *value;
}


Char* ReadTextToBuffer(const Char* path, UInt64* outSize) {
    
}

// Math methods

Int32 Sum(Int32 a, Int32 b) {
    return a + b;
}

Int32 Subtract(Int32 a, Int32 b) {
    return a - b;
}

Int32 Multiply(Int32 a, Int32 b) {
    return a * b;
}

Int32 Divide(Int32 a, Int32 b) {
    return a / b;
}



