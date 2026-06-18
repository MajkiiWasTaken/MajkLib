# MajkLib 

MajkLib is a lightweight utility and framework library written in C.

It provides a simple abstraction layer over low-level system APIs and includes functionality for window creation, rendering, input handling, timing, file operations, and other general-purpose utilities.

Created as an all-in-one fun project focused on low-level programming, framework architecture, and learning how software works internally.

---

# Features

- Window creation and management
- Basic rendering support
- Keyboard and mouse input handling
- Application loop utilities
- Timing functions
- File utilities
- Memory utilities
- Lightweight API
- Minimal dependencies
- Written entirely in C

---

# Example

```c
#include "MajkLib.h"

int main(void)
{
    OpenWindow(800, 600, "MajkLib Window");

    while (!WindowShouldClose())
    {
        ProcessWindow();
    }

    return 0;
}
```

---

# Project Goals

- Learn low-level systems programming
- Understand framework architecture
- Create reusable modules
- Build abstractions over system APIs
- Keep the library simple and lightweight
- Experiment with graphics and rendering systems

---

# Planned Features

- 2D renderer
- Audio support
- OpenGL backend
- Texture loading
- Font rendering
- Event system
- UI components
- Networking utilities
- Cross-platform support

---

# Project Structure

```txt
MajkLib.h
MajkLib.c
main.c
```

---

# Memory Ownership Notes

- `SplitString()` allocates each token into `output[i]`.
- Caller owns those allocations and must free them after use.
- Use `FreeSplitString(output, count)` to release all token buffers returned by `SplitString()`.

---

# Building

Example using GCC on Windows:

```bash
gcc main.c MajkLib.c -o app.exe -lgdi32
```

---

# License

MIT License

