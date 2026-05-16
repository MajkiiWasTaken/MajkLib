#ifndef MAJKLIB_H
#define MAJKLIB_H

// MajkLib.h - Header file for MajkLib

// includes and definitions
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Redefinition of primitive data types
typedef unsigned char                   Bool;
typedef unsigned char                   *pBool;
typedef const unsigned char             *cpBool;

typedef char                            Char;
typedef uint8_t                         UInt8;
typedef uint16_t                        UInt16;
typedef uint32_t                        UInt32;
typedef uint64_t                        UInt64;
typedef int8_t                          Int8;
typedef int16_t                         Int16;
typedef int32_t                         Int32;
typedef int64_t                         Int64;

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

#ifndef NULL
    #define NULL 0
#endif


void OpenWindow(UInt16 width, UInt16 height, const char* title);
void ProcessWindow();
UInt8 WindowShouldClose();
void MajkCloseWindow();

// Util
void SplitString(const char* str, Char delimiter, Char** output, UInt64* count);
Int32 ClampInt32(Int32* value, Int32 min, Int32 max);
Char* ReadTextToBuffer(const Char* path, UInt64* outSize);

// Math
Int32 Sum(Int32 a, Int32 b);
Int32 Subtract(Int32 a, Int32 b);
Int32 Multiply(Int32 a, Int32 b);
Int32 Divide(Int32 a, Int32 b);


#endif // MAJKLIB_H