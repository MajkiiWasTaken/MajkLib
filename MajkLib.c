#include "MajkLib.h"

static HWND hWnd;
static UInt8 running = 1;
static Int32 mouseWheelDelta = 0;

// Window methods

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg) {
        case WM_MOUSEWHEEL:
            mouseWheelDelta += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            return 0;
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
    wc.lpszClassName = "LibWindowClass";

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

void SetWindowBackgroundColor(Color color){
    ClearBackground(color);
}

UInt8 IsKeyDown(Int32 key){
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

UInt8 IsKeyPressed(Int32 key){
    static UInt8 keyStates[256] = {0};
    UInt8 isPressed = IsKeyDown(key);

    if (isPressed && !keyStates[key]) {
        keyStates[key] = 1;
        return 1;
    } else if (!isPressed) {
        keyStates[key] = 0;
    }

    return 0;
}

UInt8 IsMouseButtonDown(Int32 button){
    return (GetAsyncKeyState(VK_LBUTTON + button) & 0x8000) != 0;
}

Int32 GetMouseX(){
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(hWnd, &point);
    return point.x;
}

Int32 GetMouseY(){
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(hWnd, &point);
    return point.y;
}

UInt16 GetWindowWidth(){
    RECT rect;
    GetClientRect(hWnd, &rect);
    return rect.right - rect.left;
}

UInt16 GetWindowHeight(){
    RECT rect;
    GetClientRect(hWnd, &rect);
    return rect.bottom - rect.top;
}

void SetWindowIcon(const Char* path){
    HICON hIcon = (HICON)LoadImage(NULL, path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    if (hIcon) {
        SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }
}

void SetWindowPosition(Int32 x, Int32 y){
    SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void ToggleFullscreen(){
    static UInt8 isFullscreen = 0;
    static RECT windowRect;

    if (!isFullscreen) {
        GetWindowRect(hWnd, &windowRect);
        SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
    } else {
        SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowPos(hWnd, HWND_TOP, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_FRAMECHANGED);
    }

    isFullscreen = !isFullscreen;
}

void MaximizeWindow(){
    ShowWindow(hWnd, SW_MAXIMIZE);
}

void MinimizeWindow(){
    ShowWindow(hWnd, SW_MINIMIZE);
}

void RestoreWindow(){
    ShowWindow(hWnd, SW_RESTORE);
}

Bool IsWindowFocused(){
    return GetForegroundWindow() == hWnd;
}

Bool IsWindowFullscreen(){
    return (GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0;
}

// Events
Bool IsKeyReleased(Int32 key){
    static UInt8 keyStates[256] = {0};
    UInt8 isDown = IsKeyDown(key);

    if (!isDown && keyStates[key]) {
        keyStates[key] = 0;
        return 1;
    } else if (isDown) {
        keyStates[key] = 1;
    }

    return 0;
}

Bool IsKeyUp(Int32 key){
    return !IsKeyDown(key);
}

Int32 GetKeyPressed(){
    for (Int32 key = 0; key < 256; key++){
        if (IsKeyPressed(key)){
            return key;
        }
    }
    return -1;
}

Char GetCharPressed(){
    for (Int32 key = 0; key < 256; key++){
        if (IsKeyPressed(key)){
            return (Char)key;
        }
    }
    return '\0';
}

// Mouse events
Bool IsMouseButtonPressed(Int32 button){
    static UInt8 buttonStates[3] = {0};
    UInt8 isDown = IsMouseButtonDown(button);

    if (isDown && !buttonStates[button]) {
        buttonStates[button] = 1;
        return 1;
    } else if (!isDown) {
        buttonStates[button] = 0;
    }

    return 0;
}

Bool IsMouseButtonReleased(Int32 button){
    static UInt8 buttonStates[3] = {0};
    UInt8 isDown = IsMouseButtonDown(button);

    if (!isDown && buttonStates[button]) {
        buttonStates[button] = 0;
        return 1;
    } else if (isDown) {
        buttonStates[button] = 1;
    }

    return 0;
}

Int32 GetMouseWheelMove(){
    Int32 delta = mouseWheelDelta;
    mouseWheelDelta = 0;
    return delta;
}

Vec2 GetMousePosition(){
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(hWnd, &point);
    return Vec2Create((Float32)point.x, (Float32)point.y);
}

void SetMousePosition(Int32 x, Int32 y){
    POINT point = {x, y};
    ClientToScreen(hWnd, &point);
    SetCursorPos(point.x, point.y);
}

void MajkShowCursor(){
    ShowCursor(TRUE);
}

void MajkHideCursor(){
    ShowCursor(FALSE);
}

// Text
UInt8 FileExists(const Char* path){
    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

UInt8 WriteTextToFile(const Char* path, const Char* text){
    FILE* file = fopen(path, "w");
    if (file == NULL){
        return 0;
    }
    if (fputs(text, file) == EOF){
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

UInt8 AppendTextToFile(const Char* path, const Char* text){
    FILE* file = fopen(path, "a");
    if (file == NULL){
        return 0;
    }
    if (fputs(text, file) == EOF){
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}


// Utility methods


Int32 ClampInt32(Int32 value, Int32 min, Int32 max) {
    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }
    return value;
}


Char* ReadTextToBuffer(const Char* path, UInt64* outSize) {
    FILE* file;
    long fileSize;
    Char* buffer;
    size_t bytes;

    if (outSize != NULL){
        *outSize = 0;
    }

    if (path == NULL){
        return NULL;
    }

    file = fopen(path, "rb");

    if (file == NULL){
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0){
        fclose(file);
        return NULL;
    }

    fileSize = ftell(file);
    if (fileSize < 0){
        fclose(file);
        return NULL;
    }

    if (fseek(file, 0, SEEK_SET) != 0){
        fclose(file);
        return NULL;
    }

    buffer = (Char*)malloc(fileSize + 1);
    if (buffer == NULL){
        fclose(file);
        return NULL;
    }

    bytes = fread(buffer, 1, fileSize, file);
    if (bytes != fileSize){
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[fileSize] = '\0';

    if (outSize != NULL){
        *outSize = fileSize;
    }

    fclose(file);
    return buffer;
}

// Time / fps
Float32 GetDeltaTime(){
    static UInt64 lastTime = 0;
    UInt64 currentTime = GetTickCount64();

    if (lastTime == 0){
        lastTime = currentTime;
        return 0.0f;
    }

    Float32 deltaTime = (currentTime - lastTime) / 1000.0f;

    lastTime = currentTime;
    
    return deltaTime;
}

Float64 GetTime(){
    return GetTickCount64() / 1000.0;
}

void SetTargetFPS(UInt32 fps){
    static UInt64 frameStartTime = 0;
    UInt64 currentTime = GetTickCount64();

    if (fps == 0){
        frameStartTime = currentTime;
        return;
    }

    UInt64 targetFrameTime = 1000 / fps;

    if (frameStartTime == 0){
        frameStartTime = currentTime;
        return;
    }

    UInt64 elapsedTime = currentTime - frameStartTime;

    if (elapsedTime < targetFrameTime){
        Sleep(targetFrameTime - elapsedTime);
    }

    frameStartTime = GetTickCount64();
}

UInt32 GetFPS(){
    static UInt64 lastTime = 0;
    static UInt32 frameCount = 0;
    static UInt32 fps = 0;

    UInt64 currentTime = GetTickCount64();

    if (lastTime == 0){
        lastTime = currentTime;
        return 0;
    }

    frameCount++;

    if (currentTime - lastTime >= 1000){
        fps = frameCount;
        frameCount = 0;
        lastTime = currentTime;
    }

    return fps;
}


// Drawing 
void ClearBackground(Color color){
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
    RECT rect;

    GetClientRect(hWnd, &rect);
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}

void DrawPixel(Int32 x, Int32 y, Color color){
    HDC hdc = GetDC(hWnd);

    SetPixel(hdc, x, y, RGB(color.r, color.g, color.b));
    ReleaseDC(hWnd, hdc);
}

void DrawLine(Int32 x1, Int32 y1, Int32 x2, Int32 y2, Color color){
    HDC hdc = GetDC(hWnd);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
    HGDIOBJ oldPen = SelectObject(hdc, pen);

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(hWnd, hdc);
}

void DrawRectangle(Int32 x, Int32 y, Int32 width, Int32 height, Color color){
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
    RECT rect = {x, y, x + width, y + height};

    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}

void DrawCircle(Int32 x, Int32 y, Int32 radius, Color color){
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
    HGDIOBJ oldBrush = SelectObject(hdc, brush);

    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}

void MajkDrawText(const char* text, Int32 x, Int32 y, UInt16 size, Color color){
    HDC hdc = GetDC(hWnd);
    HFONT font = CreateFont(size, 
        0, 
        0, 
        0, 
        FW_NORMAL, 
        FALSE, 
        FALSE, 
        FALSE, 
        DEFAULT_CHARSET, 
        OUT_DEFAULT_PRECIS, 
        CLIP_DEFAULT_PRECIS, 
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
        "Arial");
    HGDIOBJ oldFont = SelectObject(hdc, font);

    SetTextColor(hdc, RGB(color.r, color.g, color.b));
    SetBkMode(hdc, TRANSPARENT);

    TextOut(hdc, x, y, text, (int)strlen(text));

    SelectObject(hdc, oldFont);
    DeleteObject(font);
    ReleaseDC(hWnd, hdc);
}

void DrawRectangleLines(Int32 x, Int32 y, Int32 width, Int32 height, Color color){
    HDC hdc = GetDC(hWnd);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    Rectangle(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(hWnd, hdc);
}

void DrawCircleLines(Int32 x, Int32 y, Int32 radius, Color color){
    HDC hdc = GetDC(hWnd);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(hWnd, hdc);
}

void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color){
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
    HGDIOBJ oldBrush = SelectObject(hdc, brush);

    POINT points[3] = {
        { (LONG)p1.x, (LONG)p1.y },
        { (LONG)p2.x, (LONG)p2.y },
        { (LONG)p3.x, (LONG)p3.y }
    };

    Polygon(hdc, points, 3);

    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}

void DrawTriangleLines(Vec2 p1, Vec2 p2, Vec2 p3, Color color){
    HDC hdc = GetDC(hWnd);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
    HGDIOBJ oldPen = SelectObject(hdc, pen);

    POINT points[3] = {
        { (LONG)p1.x, (LONG)p1.y },
        { (LONG)p2.x, (LONG)p2.y },
        { (LONG)p3.x, (LONG)p3.y }
    };

    Polyline(hdc, points, 3);

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(hWnd, hdc);
}

void DrawEllipse(Int32 x, Int32 y, Int32 radiusX, Int32 radiusY, Color color){
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
    HGDIOBJ oldBrush = SelectObject(hdc, brush);
    Ellipse(hdc, x - radiusX, y - radiusY, x + radiusX, y + radiusY);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}

// Color utils
Color ColorCreate(UInt8 r, UInt8 g, UInt8 b, UInt8 a){
    Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

Color ColorFade(Color color, Float32 alpha){
    color.a = (UInt8)(color.a * alpha);
    return color;
}

Color ColorLerp(Color a, Color b, Float32 t){
    Color result;
    result.r = (UInt8)(a.r + t * (b.r - a.r));
    result.g = (UInt8)(a.g + t * (b.g - a.g));
    result.b = (UInt8)(a.b + t * (b.b - a.b));
    result.a = (UInt8)(a.a + t * (b.a - a.a));
    return result;
}

UInt32 ColorToUInt32(Color color){
    return (color.a << 24) | (color.b << 16) | (color.g << 8) | color.r;
} 

// String methods
Bool StringEquals(const Char* a, const Char* b){
    if (a == NULL || b == NULL){
        return 0;
    }
    return strcmp(a, b) == 0;
}

Bool StringContains(const Char* str, const Char* find){
    if (str == NULL || find == NULL){
        return 0;
    }

    UInt64 strLength = StringLength(str);
    UInt64 findLength = StringLength(find);

    if (findLength > strLength){
        return 0;
    }

    for (UInt64 i = 0; i <= strLength - findLength; i++){
        if (memcmp(&str[i], find, findLength) == 0){
            return 1;
        }
    }

    return 0;
}

Char* StringConcat(const Char* a, const Char* b){
    if (a == NULL || b == NULL){
        return NULL;
    }

    UInt64 lengthA = StringLength(a);
    UInt64 lengthB = StringLength(b);
    UInt64 totalLength = lengthA + lengthB;

    Char* result = (Char*)malloc(totalLength + 1);
    if (result == NULL){
        return NULL;
    }

    memcpy(result, a, lengthA);
    memcpy(result + lengthA, b, lengthB);
    result[totalLength] = '\0';
    return result;
}

Char* StringSubstring(const Char* str, UInt64 start, UInt64 length){
    if (str == NULL){
        return NULL;
    }

    UInt64 strLength = StringLength(str);

    if (start >= strLength){
        return NULL;
    }

    if (start + length > strLength){
        length = strLength - start;
    }

    Char* substring = (Char*)malloc(length + 1);
    if (substring == NULL){
        return NULL;
    }

    memcpy(substring, &str[start], length);
    substring[length] = '\0';
    return substring;
}

void StringToUpper(Char* str){
    if (str == NULL){
        return;
    }

    UInt64 i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'a' && str[i] <= 'z'){
            str[i] = str[i] - ('a' - 'A');
        }
        i++;
    }
}

void StringToLower(Char* str){
    if (str == NULL){
        return;
    }

    UInt64 i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}

void SplitString(const char *str, Char delimiter, Char** output, UInt64 *count) {
    UInt64 i;
    UInt64 parts;
    UInt64 start;
    UInt64 length;
    Char* token;

    if (count != NULL) {
        *count = 0;
    }

    if (str == NULL || output == NULL) {
        return;
    }

    parts = 1;

    for (i = 0; str[i] != '\0'; i++){
        if (str[i] == delimiter) {
            parts++;
        }
    }

    *count = parts;

    start = 0;
    parts = 0;

    for (i = 0;; i++){
        if (str[i] == delimiter || str[i] == '\0'){
            length = i - start;
            token = (Char*)malloc(length + 1);

            if (token == NULL){
                FreeSplitString(output, parts);
                if (count != NULL) {
                    *count = 0;
                }
                return;
            }

            memcpy(token, &str[start], length);
            token[length] = '\0';
            output[parts] = token;
            parts++;
            start = i + 1;
        }
        if (str[i] == '\0') {
            break;
        }
    }
}

void FreeSplitString(Char** output, UInt64 count){
    UInt64 i;

    if (output == NULL){
        return;
    }

    for (i = 0; i < count; i++){
        if (output[i] != NULL){
            free(output[i]);
            output[i] = NULL;
        }
    }
}

Char* StringDuplicate(const Char* str){
    if (str == NULL){
        return NULL;
    }

    UInt64 length = StringLength(str);
    Char* copy = (Char*)malloc(length + 1);

    if (copy == NULL){
        return NULL;
    }

    memcpy(copy, str, length);
    copy[length] = '\0';
    return copy;
}

UInt64 StringLength(const Char* str) {
    if (str == NULL) {
        return 0;
    }
    UInt64 length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
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

Float32 LerpFloat32(Float32 a, Float32 b, Float32 t) {
    return a + t * (b - a);
}

Int32 AbsInt32(Int32 value) {
    return value < 0 ? -value : value;
}

Float32 AbsFloat32(Float32 value) {
    return value < 0 ? -value : value;
}

Int32 MinInt32(Int32 a, Int32 b) {
    return a < b ? a : b;
}

Int32 MaxInt32(Int32 a, Int32 b) {
    return a > b ? a : b;
}

Vec2 Vec2Create(Float32 x, Float32 y) {
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

Vec2 Vec2Add(Vec2 a, Vec2 b) {
    Vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vec2 Vec2Subtract(Vec2 a, Vec2 b) {
    Vec2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Vec2 Vec2Scale(Vec2 v, Float32 scale) {
    Vec2 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    return result;
}

Float32 Vec2Length(Vec2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

Float32 Vec2Distance(Vec2 a, Vec2 b) {
    Vec2 diff = Vec2Subtract(a, b);
    return Vec2Length(diff);
}

Vec2 Vec2Normalize(Vec2 v) {
    Float32 length = Vec2Length(v);
    if (length == 0) {
        return Vec2Create(0, 0);
    }
    return Vec2Scale(v, 1.0f / length);
}

Float32 Vec2Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec3 Vec3Create(Float32 x, Float32 y, Float32 z) {
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vec3 Vec3Add(Vec3 a, Vec3 b) {
    Vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

Vec3 Vec3Subtract(Vec3 a, Vec3 b) {
    Vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

Vec3 Vec3Scale(Vec3 v, Float32 scale) {
    Vec3 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    result.z = v.z * scale;
    return result;
}

Float32 Vec3Length(Vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Float32 Vec3Distance(Vec3 a, Vec3 b) {
    Vec3 diff = Vec3Subtract(a, b);
    return Vec3Length(diff);
}

Vec3 Vec3Normalize(Vec3 v) {
    Float32 length = Vec3Length(v);
    if (length == 0) {
        return Vec3Create(0, 0, 0);
    }
    return Vec3Scale(v, 1.0f / length);
}

Float32 Vec3Dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3Cross(Vec3 a, Vec3 b) {
    Vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

Vec4 Vec4Create(Float32 x, Float32 y, Float32 z, Float32 w) {
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

Vec4 Vec4Add(Vec4 a, Vec4 b){
    Vec4 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

Vec4 Vec4Subtract(Vec4 a, Vec4 b){
    Vec4 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

Vec4 Vec4Scale(Vec4 v, Float32 scale){
    Vec4 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    result.z = v.z * scale;
    result.w = v.w * scale;
    return result;
}

Float32 Vec4Length(Vec4 v){
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Float32 Vec4Distance(Vec4 a, Vec4 b){
    Vec4 diff = Vec4Subtract(a, b);
    return Vec4Length(diff);
}

Vec4 Vec4Normalize(Vec4 v){
    Float32 length = Vec4Length(v);
    if (length == 0) {
        return Vec4Create(0, 0, 0, 0);
    }
    return Vec4Scale(v, 1.0f / length);
}

Float32 Vec4Dot(Vec4 a, Vec4 b){
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vec4 Vec4Cross(Vec4 a, Vec4 b){
    Vec4 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    result.w = 0; // The w component is set to 0 for cross product
    return result;
}

Matrix MatrixIdentity(){
    Matrix m = {0};
    m.m0 = 1.0f;
    m.m5 = 1.0f;
    m.m10 = 1.0f;
    m.m15 = 1.0f;
    return m;
}

Matrix MatrixMultiply(Matrix a, Matrix b){
    Matrix result;

    result.m0 = a.m0 * b.m0 + a.m4 * b.m1 + a.m8 * b.m2 + a.m12 * b.m3;
    result.m1 = a.m1 * b.m0 + a.m5 * b.m1 + a.m9 * b.m2 + a.m13 * b.m3;
    result.m2 = a.m2 * b.m0 + a.m6 * b.m1 + a.m10 * b.m2 + a.m14 * b.m3;
    result.m3 = a.m3 * b.m0 + a.m7 * b.m1 + a.m11 * b.m2 + a.m15 * b.m3;

    result.m4 = a.m0 * b.m4 + a.m4 * b.m5 + a.m8 * b.m6 + a.m12 * b.m7;
    result.m5 = a.m1 * b.m4 + a.m5 * b.m5 + a.m9 * b.m6 + a.m13 * b.m7;
    result.m6 = a.m2 * b.m4 + a.m6 * b.m5 + a.m10 * b.m6 + a.m14 * b.m7;
    result.m7 = a.m3 * b.m4 + a.m7 * b.m5 + a.m11 * b.m6 + a.m15 * b.m7;

    result.m8 = a.m0 * b.m8 + a.m4 * b.m9 + a.m8 * b.m10 + a.m12 * b.m11;
    result.m9 = a.m1 * b.m8 + a.m5 * b.m9 + a.m9 * b.m10 + a.m13 * b.m11;
    result.m10 = a.m2 * b.m8 + a.m6 * b.m9 + a.m10 * b.m10 + a.m14 * b.m11;
    result.m11 = a.m3 * b.m8 + a.m7 * b.m9 + a.m11 * b.m10 + a.m15 * b.m11;

    result.m12 = a.m0 * b.m12 + a.m4 * b.m13 + a.m8 * b.m14 + a.m12 * b.m15;
    result.m13 = a.m1 * b.m12 + a.m5 * b.m13 + a.m9 * b.m14 + a.m13 * b.m15;
    result.m14 = a.m2 * b.m12 + a.m6 * b.m13 + a.m10 * b.m14 + a.m14 * b.m15;
    result.m15 = a.m3 * b.m12 + a.m7 * b.m13 + a.m11 * b.m14 + a.m15 * b.m15;

    return result;
}

Matrix MatrixTranslate(Float32 x, Float32 y, Float32 z){
    Matrix m = MatrixIdentity();
    m.m12 = x;
    m.m13 = y;
    m.m14 = z;
    return m;
}

Matrix MatrixRotateX(Float32 angle){
    Matrix m = MatrixIdentity();
    Float32 c = cosf(angle);
    Float32 s = sinf(angle);

    m.m5 = c;
    m.m6 = s;
    m.m9 = -s;
    m.m10 = c;

    return m;
}

Matrix MatrixRotateY(Float32 angle){
    Matrix m = MatrixIdentity();
    Float32 c = cosf(angle);
    Float32 s = sinf(angle);

    m.m0 = c;
    m.m2 = -s;
    m.m8 = s;
    m.m10 = c;

    return m;
}

Matrix MatrixRotateZ(Float32 angle){
    Matrix m = MatrixIdentity();
    Float32 c = cosf(angle);
    Float32 s = sinf(angle);

    m.m0 = c;
    m.m1 = s;
    m.m4 = -s;
    m.m5 = c;

    return m;
}

Matrix MatrixScale(Float32 x, Float32 y, Float32 z){
    Matrix m = MatrixIdentity();
    m.m0 = x;
    m.m5 = y;
    m.m10 = z;
    return m;
}

Vec4 MatrixTransformVec4(Matrix m, Vec4 v){
    Vec4 result;
    result.x = m.m0 * v.x + m.m4 * v.y + m.m8 * v.z + m.m12 * v.w;
    result.y = m.m1 * v.x + m.m5 * v.y + m.m9 * v.z + m.m13 * v.w;
    result.z = m.m2 * v.x + m.m6 * v.y + m.m10 * v.z + m.m14 * v.w;
    result.w = m.m3 * v.x + m.m7 * v.y + m.m11 * v.z + m.m15 * v.w;
    return result;
}

// Random
Int32 RandomInt(Int32 min, Int32 max){
    return min + rand() % (max - min + 1);
}

Float32 RandomFloat(Float32 min, Float32 max){
    return min + ((Float32)rand() / (Float32)RAND_MAX) * (max - min);
}

// Memory management
void* MajkAlloc(UInt64 size){
    return malloc(size);
}

void* MajkCalloc(UInt64 count, UInt64 size){
    return calloc(count, size);
}

void* MajkRealloc(void* ptr, UInt64 newSize){
    return realloc(ptr, newSize);
}

void MajkFree(void* ptr){
    free(ptr);
}

// Logging
void LogInfo(const Char* format, ...){
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void LogWarning(const Char* format, ...){
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void LogError(const Char* format, ...){
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}