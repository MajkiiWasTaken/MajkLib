#include "MajkLib.h"

int main() {
    OpenWindow(800u, 600u, "MajkLib Window");

    while (!WindowShouldClose()) {
        ProcessWindow();
        // Here you can add rendering code or other logic
    }

    

    MajkCloseWindow();
    return 0;
}