# MajkLib

![Language](https://img.shields.io/badge/language-C-A8B9CC)
![Platform](https://img.shields.io/badge/platform-Windows-blue)
![Graphics](https://img.shields.io/badge/graphics-GDI-orange)
![Dependencies](https://img.shields.io/badge/dependencies-Minimal-success)
![Status](https://img.shields.io/badge/status-In%20Development-yellow)

### Overview

**MajkLib** is a lightweight utility and framework library written entirely in **C**, designed to simplify low-level application development while exposing the underlying concepts of system programming.

The library provides abstractions over native operating system APIs and offers essential functionality such as **window management, rendering, input processing, timing utilities, file operations, and memory-related helpers**.

Originally created as a personal learning project, MajkLib focuses on understanding how frameworks work internally while remaining simple, reusable, and easy to extend.

---

### Features

### Window Management

* Native window creation
* Window lifecycle management
* Window event processing
* Main application loop helpers

### Rendering Support

* Basic rendering functionality
* Integration with Windows GDI
* Foundation for future graphics backends

### Input Handling

* Keyboard input processing
* Mouse input support
* Real-time input state tracking

### Utility Modules

* Timing and delta time utilities
* File handling helpers
* Memory-related utilities
* General-purpose helper functions

### Lightweight Design

* Minimal dependencies
* Small and straightforward API
* Easy integration into existing projects
* Written entirely in standard C

---

### How It Works

MajkLib wraps low-level system functionality into a simplified API while still keeping the underlying mechanisms transparent.

### Core workflow

1. **Initialize the Window**

   * Create a native operating system window.

2. **Start the Application Loop**

   * Process system events and user input.

3. **Execute Application Logic**

   * Update program state.
   * Handle rendering operations.

4. **Shutdown**

   * Release allocated resources.
   * Close the application cleanly.

---

### Example

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

### Architecture

```text
Application
      │
      ▼
   MajkLib
      │
 ┌────┼─────────────┐
 │    │      │      │
 ▼    ▼      ▼      ▼
Window Input Timing Utilities
      │
      ▼
 Windows API / GDI
      │
      ▼
 Operating System
```

---

### Project Goals

MajkLib was created to:

* learn low-level systems programming,
* understand framework architecture,
* explore how operating systems interact with applications,
* build reusable software components,
* experiment with rendering systems,
* maintain a lightweight and approachable codebase.

---

### Planned Features

Future development may include:

* 2D renderer,
* OpenGL rendering backend,
* texture loading,
* font rendering,
* event dispatching system,
* UI components,
* audio support,
* networking utilities,
* cross-platform compatibility.

---

### Building

### GCC (Windows)

```bash
gcc main.c MajkLib.c -o app.exe -lgdi32
```

### Requirements

* Windows
* GCC or another compatible C compiler
* Windows GDI libraries

---

### Technologies Used

* **C**
* **Windows API**
* **Windows GDI**
* Native event handling
* Low-level systems programming concepts

---

### Use Cases

MajkLib is suitable for:

* learning how frameworks are built internally,
* experimenting with low-level programming,
* creating simple desktop applications,
* prototyping graphics systems,
* educational projects focused on system APIs,
* serving as a foundation for a custom game or application framework.

---

### Notes

MajkLib prioritizes simplicity, readability, and learning value over feature completeness. The project serves both as a practical utility library and as an exploration of how higher-level frameworks abstract operating system functionality.

---

### License

MIT License

---

### Author: Michal Švrček

Developed as a personal project focused on low-level programming, framework architecture, and understanding how software works behind the scenes.
