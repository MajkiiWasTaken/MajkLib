#ifndef MAJKLIB_H
#define MAJKLIB_H

// MajkLib.h - Header file for MajkLib

// includes and definitions
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <float.h>

// Definitions of math constants
#ifndef PI
    #define PI 3.14159265358979323846
#endif
#ifndef E
    #define E 2.71828182845904523536
#endif
#ifndef GOLDEN_RATIO
    #define GOLDEN_RATIO 1.61803398874989484820
#endif
#ifndef DEG2RAD
    #define DEG2RAD (PI / 180.0)
#endif
#ifndef RAD2DEG
    #define RAD2DEG (180.0 / PI)
#endif


// Redefinition of primitive data types
typedef bool                            Bool;
typedef Bool*                           pBool;
typedef const Bool*                     cpBool;

typedef uint8_t                         UInt8;
typedef uint16_t                        UInt16;
typedef uint32_t                        UInt32;
typedef uint64_t                        UInt64;
typedef int8_t                          Int8;
typedef int16_t                         Int16;
typedef int32_t                         Int32;
typedef int64_t                         Int64;

typedef char                            Char;
typedef char                            *pChar;
typedef unsigned char                   *pUInt8;
typedef signed char                     *pInt8;
typedef unsigned short int              *pUInt16;
typedef signed short int                *pInt16;
typedef unsigned int                    *pUInt32;
typedef signed int                      *pInt32;
typedef unsigned long long              *pUInt64;
typedef signed long long                *pInt64;

typedef const char                      *cpChar;
typedef const unsigned char             *cpUInt8;
typedef const signed char               *cpInt8;
typedef const unsigned short int        *cpUInt16;
typedef const signed short int          *cpInt16;
typedef const unsigned int              *cpUInt32;
typedef const signed int                *cpInt32;
typedef const unsigned long long        *cpUInt64;
typedef const signed long long          *cpInt64;

typedef float       Float32;
typedef double      Float64;

typedef Float32*    pFloat32;
typedef Float64*    pFloat64;

typedef const Float32* cpFloat32;
typedef const Float64* cpFloat64;

#ifndef NULL
    #define NULL 0
#endif
#ifndef TRUE
    #define TRUE true
#endif

#ifndef FALSE
    #define FALSE false
#endif

// =============================
// Structs
// =============================

// RGBA color, 4 components, R8G8B8A8 format (32 bits)
typedef struct {
    UInt8 r;
    UInt8 g;
    UInt8 b;
    UInt8 a;
} Color;

// Vectors

// 2D vector, 2 components
typedef struct {
    float x;
    float y;
} Vec2;

// 3D vector, 3 components
typedef struct {
    float x;
    float y;
    float z;
} Vec3;

// 4D vector, 4 components
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

// 4x4 matrix, 16 components, column-major order, right-handed coordinate system
typedef struct {
    float m0, m4, m8, m12;
    float m1, m5, m9, m13;
    float m2, m6, m10, m14;
    float m3, m7, m11, m15;
} Matrix;

// =============================
// Colors
// =============================
#define COLOR_WHITE (Color){255, 255, 255, 255}
#define COLOR_BLACK (Color){0, 0, 0, 255}
#define COLOR_RED (Color){255, 0, 0, 255}
#define COLOR_GREEN (Color){0, 255, 0, 255}
#define COLOR_BLUE (Color){0, 0, 255, 255}
#define COLOR_YELLOW (Color){255, 255, 0, 255}
#define COLOR_CYAN (Color){0, 255, 255, 255}
#define COLOR_MAGENTA (Color){255, 0, 255, 255}

// =============================
// Window
// =============================
void OpenWindow(UInt16 width, UInt16 height, const char* title); // Opens a window with the specified width, height, and title
void ProcessWindow(); // Processes window messages and events, should be called in the main loop
UInt8 WindowShouldClose(); // Returns 1 if the window should close, 0 otherwise
void MajkCloseWindow(); // Closes the window and cleans up resources
void SetWindowBackgroundColor(Color color); // Sets the background color of the window
UInt8 IsKeyDown(Int32 key);
UInt8 IsKeyPressed(Int32 key);
UInt8 IsMouseButtonDown(Int32 button);
Int32 GetMouseX();
Int32 GetMouseY();
UInt16 GetWindowWidth();
UInt16 GetWindowHeight();
void SetWindowIcon(const Char* path);
void SetWindowPosition(Int32 x, Int32 y);
void ToggleFullscreen();
void MaximizeWindow();
void MinimizeWindow();
void RestoreWindow();
Bool IsWindowFocused();
Bool IsWindowFullscreen();

// =============================
// Events
// =============================
// Keyboard events
Bool IsKeyReleased(Int32 key);
Bool IsKeyUp(Int32 key);
Int32 GetKeyPressed();
Char GetCharPressed();

// Mouse events
Bool IsMouseButtonPressed(Int32 button);
Bool IsMouseButtonReleased(Int32 button);
Int32 GetMouseWheelMove();
Vec2 GetMousePosition();
void SetMousePosition(Int32 x, Int32 y);
void MajkShowCursor();
void MajkHideCursor();

// =============================
// FPS / time
// =============================
Float32 GetDeltaTime();
Float64 GetTime();
void SetTargetFPS(UInt32 fps);
UInt32 GetFPS();

// =============================
// Drawing
// =============================
void ClearBackground(Color color);
void DrawPixel(Int32 x, Int32 y, Color color);
void DrawLine(Int32 x1, Int32 y1, Int32 x2, Int32 y2, Color color);
void DrawRectangle(Int32 x, Int32 y, Int32 width, Int32 height, Color color);
void DrawCircle(Int32 x, Int32 y, Int32 radius, Color color);
void MajkDrawText(const char* text, Int32 x, Int32 y, UInt16 size, Color color);
void DrawRectangleLines(Int32 x, Int32 y, Int32 width, Int32 height, Color color);
void DrawCircleLines(Int32 x, Int32 y, Int32 radius, Color color);
void DrawTriangle(Vec2 p1, Vec2 p2, Vec2 p3, Color color);
void DrawTriangleLines(Vec2 p1, Vec2 p2, Vec2 p3, Color color);
void DrawEllipse(Int32 x, Int32 y, Int32 radiusX, Int32 radiusY, Color color);

// =============================
// Color utils
// =============================
Color ColorCreate(UInt8 r, UInt8 g, UInt8 b, UInt8 a);
Color ColorFade(Color color, Float32 alpha);
Color ColorLerp(Color a, Color b, Float32 t);
UInt32 ColorToUInt32(Color color);

// =============================
// Utils
// =============================
// Clamp
Int32 ClampInt32(Int32 value, Int32 min, Int32 max);

// Text
Char* ReadTextToBuffer(const Char* path, UInt64* outSize);
UInt8 FileExists(const Char* path);
UInt8 WriteTextToFile(const Char* path, const Char* text);
UInt8 AppendTextToFile(const Char* path, const Char* text);

// String
Bool StringEquals(const Char* a, const Char* b);
Bool StringContains(const Char* str, const Char* find);
Char* StringConcat(const Char* a, const Char* b);
Char* StringSubstring(const Char* str, UInt64 start, UInt64 length);
void StringToUpper(Char* str);
void StringToLower(Char* str);
void SplitString(const char* str, Char delimiter, Char** output, UInt64* count);
void FreeSplitString(Char** output, UInt64 count);
Char* StringDuplicate(const Char* str);
UInt64 StringLength(const Char* str);



// =============================
// Math
// =============================
// Basic math operations
Int32 Sum(Int32 a, Int32 b);
Int32 Subtract(Int32 a, Int32 b);
Int32 Multiply(Int32 a, Int32 b);
Int32 Divide(Int32 a, Int32 b);
Float32 LerpFloat32(Float32 a, Float32 b, Float32 t);
Int32 AbsInt32(Int32 value);
Float32 AbsFloat32(Float32 value);
Int32 MinInt32(Int32 a, Int32 b);
Int32 MaxInt32(Int32 a, Int32 b);

// Vec2 math
Vec2 Vec2Create(Float32 x, Float32 y);
Vec2 Vec2Add(Vec2 a, Vec2 b);
Vec2 Vec2Subtract(Vec2 a, Vec2 b);
Vec2 Vec2Scale(Vec2 v, Float32 scale);
Float32 Vec2Length(Vec2 v);
Float32 Vec2Distance(Vec2 a, Vec2 b);
Vec2 Vec2Normalize(Vec2 v);
Float32 Vec2Dot(Vec2 a, Vec2 b);

// Vec3 math
Vec3 Vec3Create(Float32 x, Float32 y, Float32 z);
Vec3 Vec3Add(Vec3 a, Vec3 b);
Vec3 Vec3Subtract(Vec3 a, Vec3 b);
Vec3 Vec3Scale(Vec3 v, Float32 scale);
Float32 Vec3Length(Vec3 v);
Float32 Vec3Distance(Vec3 a, Vec3 b);
Vec3 Vec3Normalize(Vec3 v);
Float32 Vec3Dot(Vec3 a, Vec3 b);
Vec3 Vec3Cross(Vec3 a, Vec3 b);

// Vec4 math
Vec4 Vec4Create(Float32 x, Float32 y, Float32 z, Float32 w);
Vec4 Vec4Add(Vec4 a, Vec4 b);
Vec4 Vec4Subtract(Vec4 a, Vec4 b);
Vec4 Vec4Scale(Vec4 v, Float32 scale);
Float32 Vec4Length(Vec4 v);
Float32 Vec4Distance(Vec4 a, Vec4 b);
Vec4 Vec4Normalize(Vec4 v);
Float32 Vec4Dot(Vec4 a, Vec4 b);
Vec4 Vec4Cross(Vec4 a, Vec4 b);

// Matrix math
Matrix MatrixIdentity();
Matrix MatrixMultiply(Matrix a, Matrix b);
Matrix MatrixTranslate(Float32 x, Float32 y, Float32 z);
Matrix MatrixRotateX(Float32 angle);
Matrix MatrixRotateY(Float32 angle);
Matrix MatrixRotateZ(Float32 angle);
Matrix MatrixScale(Float32 x, Float32 y, Float32 z);
Vec4 MatrixTransformVec4(Matrix m, Vec4 v);

// =============================
// Random
// =============================
Int32 RandomInt(Int32 min, Int32 max);
Float32 RandomFloat(Float32 min, Float32 max);

// =============================
// Custom memory functions
// =============================
void* MajkAlloc(UInt64 size);
void* MajkCalloc(UInt64 count, UInt64 size);
void* MajkRealloc(void* ptr, UInt64 newSize);
void MajkFree(void* ptr);

// =============================
// Logging
// =============================
void LogInfo(const Char* format, ...);
void LogWarning(const Char* format, ...);
void LogError(const Char* format, ...);

#endif // MAJKLIB_H