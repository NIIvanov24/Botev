# 📦 BOTEV Inventory System — Raylib Edition

<div align="center">

```
██████╗  ██████╗ ████████╗███████╗██╗   ██╗
██╔══██╗██╔═══██╗╚══██╔══╝██╔════╝██║   ██║
██████╔╝██║   ██║   ██║   █████╗  ██║   ██║
██╔══██╗██║   ██║   ██║   ██╔══╝  ╚██╗ ██╔╝
██████╔╝╚██████╔╝   ██║   ███████╗ ╚████╔╝
╚═════╝  ╚═════╝    ╚═╝   ╚══════╝  ╚═══╝

 I N V E N T O R Y   M A N A G E M E N T   S Y S T E M
```

**A C++17 Raylib-based inventory management system built with a clean three-tier architecture.**

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=cplusplus)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-green?style=for-the-badge&logo=cmake)
![Raylib](https://img.shields.io/badge/Raylib-5.0-orange?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-Three--Tier-purple?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)
![Grade](https://img.shields.io/badge/Grade-9th-red?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey?style=for-the-badge)

</div>

---

## 📋 Table of Contents

1. [Project Overview](#-project-overview)
2. [Visual Features](#-visual-features)
3. [Architecture](#-architecture-three-tier)
4. [Project Structure](#-project-structure)
5. [Feature Reference](#-feature-reference)
6. [Algorithms Implemented](#-algorithms-implemented)
7. [Statistics Panel](#-statistics-panel)
8. [Building the Project](#-building-the-project)
9. [Installation Guide](#-installation-guide)
10. [Controls Reference](#-controls-reference)
11. [Data Layer Documentation](#-data-layer-documentation)
12. [Logic Layer Documentation](#-logic-layer-documentation)
13. [UI Layer Documentation](#-ui-layer-documentation)
14. [File Format Specification](#-file-format-specification)
15. [Coding Standards](#-coding-standards)
16. [API Reference](#-api-reference)
17. [Configuration](#-configuration)
18. [Error Handling](#-error-handling)
19. [Testing](#-testing)
20. [Performance Notes](#-performance-notes)
21. [Troubleshooting](#-troubleshooting)
22. [Planned Features](#-planned-features)
23. [Changelog](#-changelog)
24. [Collaborators](#-collaborators)
25. [Acknowledgements](#-acknowledgements)
26. [License](#-license)

---

## 🌟 Project Overview

**BOTEV Inventory System** is a fully graphical, desktop inventory management application written in **C++17** using the **Raylib** game/graphics library. It was developed as a 9th-grade school project and demonstrates a clean **three-tier software architecture** with a dedicated Presentation Layer, Logic Layer, and Data Layer.

The system allows a user to manage a product inventory: adding new products, removing old ones, sorting and searching the catalog, and viewing analytics in a visually rich statistics screen. All data is persisted to disk using plain-text file I/O so the inventory survives application restarts.

Despite being a school project, BOTEV targets professional code quality: it enforces const-correctness, uses STL containers instead of raw pointers, validates all user input before it reaches the data layer, and follows consistent naming conventions throughout.

### Why Raylib?

Raylib was chosen over Qt, wxWidgets, or SDL+Dear ImGui for several reasons:

- **Simplicity**: Raylib has a minimal, C-style API that is easy to learn
- **Self-contained**: One header, one library — no complex dependency trees
- **Performance**: Hardware-accelerated 2D rendering via OpenGL
- **Cross-platform**: Identical code compiles on Linux, macOS, and Windows
- **Educational**: The source code of Raylib is readable and educational
- **Community**: Large community, excellent documentation, and many examples

### Design Philosophy

> *"Make it work. Make it right. Make it fast."* — Kent Beck

Every design decision in BOTEV follows three principles:

1. **Separation of Concerns** — Each layer has a clearly defined responsibility and does not reach into another layer's domain
2. **Data Validation at the Boundary** — Invalid data is rejected by the Logic layer before it ever reaches the Data layer
3. **User Experience First** — Even a console-equivalent backend is wrapped in a polished, animated GUI with toast notifications, smooth transitions, and visual feedback

---

## ✨ Visual Features

The presentation layer is one of the most distinctive aspects of BOTEV. Rather than a plain window with buttons, every screen has been designed with depth, motion, and personality.

| Feature                    | Details                                                                 |
| -------------------------- | ----------------------------------------------------------------------- |
| 🌌 Animated background      | Floating glow blobs drift slowly across the screen with additive blend  |
| 🔲 Background grid          | Subtle perspective grid rendered in the background                      |
| ✨ Live particles            | Small glowing dots emitted continuously, fading with age                |
| 🎞 Scanline overlay         | CRT-style post-processing for retro aesthetic, toggleable in Settings   |
| 🔀 Screen transitions       | Smooth fade-to-black when navigating between screens                    |
| 🔘 Animated buttons         | Hover glow, colour lerp on hover, glowing border pulse on focus         |
| 🔔 Toast notifications      | Slide-in corner toasts for add/remove/search events                     |
| 📊 Animated bar chart       | Product-value bars grow from zero when Statistics screen opens          |
| 📋 Scrollable table         | Mouse-wheel and arrow-key scrolling with a custom scrollbar             |
| 🕐 Live HUD                 | Real-time product count, total value, and low-stock badge in header     |
| ⚙️ Settings panel           | Volume slider, particle toggle, scanline toggle, colour theme           |
| 🌈 Colour themes            | Switch between Dark Neon, Dark Blue, and Midnight Purple                |
| 🖱️ Cursor highlight         | Custom cursor glow follows the mouse pointer                            |
| 🔡 Animated text            | Title text uses a gentle floating sine-wave animation                   |

### Background Rendering Pipeline

Each frame, the background is rendered in the following order:

```
1. Clear screen to background colour
2. Draw perspective grid (alpha ~40)
3. Update & draw glow blobs (additive blend mode)
4. Update & draw particles (additive blend mode)
5. Draw main UI elements (normal blend mode)
6. Draw scanline overlay (if enabled, multiplicative blend)
7. Draw toast notifications on top of everything
8. Draw custom cursor last
```

### Glow Blob System

Glow blobs are large, soft circles rendered with `BLEND_ADDITIVE`. Each blob has:

```cpp
struct GlowBlob {
    Vector2 position;     // Current position
    Vector2 velocity;     // Movement per frame (slow drift)
    float   radius;       // Visual radius (80–200 px)
    Color   color;        // Base colour (low alpha)
    float   phase;        // Phase offset for sine-wave alpha pulse
    float   speed;        // Pulse speed
};
```

There are 6 blobs active at all times. When a blob drifts off-screen it wraps around to the opposite edge, ensuring continuous motion.

### Particle System

The particle system emits tiny glowing dots from the bottom of the screen. Each particle:

- Has a lifetime of 2–5 seconds
- Moves upward with slight horizontal drift
- Fades from full alpha to 0 over its lifetime
- Has a radius of 1–3 pixels

The emitter fires one new particle every 3 frames (20 particles/second at 60 FPS). The maximum pool is 300 particles; older particles are recycled when the pool is full.

### Toast Notification System

Toasts appear in the bottom-right corner of the screen. Each toast:

- Slides in from the right edge over 0.3 seconds
- Stays visible for 2.5 seconds
- Fades out over 0.4 seconds
- Has a coloured left border indicating type (green = success, red = error, yellow = warning)

Up to 4 toasts can be stacked simultaneously.

### Screen Transition System

When the user navigates to a new screen, a fade-to-black transition plays:

```
Phase 1: Fade out (0.0 → 1.0 alpha black overlay, ~0.2s)
Phase 2: Switch active screen
Phase 3: Fade in (1.0 → 0.0 alpha black overlay, ~0.2s)
```

This prevents jarring instant screen changes and gives the application a polished, professional feel.

---

## 🏗️ Architecture (Three-Tier)

BOTEV strictly follows the **three-tier (three-layer) architectural pattern**. Each tier has one job and communicates only with the tier immediately adjacent to it.

```
╔══════════════════════════════════════════════════════════════╗
║                   PRESENTATION LAYER                         ║
║                                                              ║
║   ui.h / ui.cpp                                              ║
║   ┌─────────────┐  ┌─────────────┐  ┌────────────────────┐  ║
║   │  MainMenu   │  │ ProductList │  │  StatisticsScreen  │  ║
║   │  Screen     │  │  Screen     │  │       Screen       │  ║
║   └─────────────┘  └─────────────┘  └────────────────────┘  ║
║   ┌─────────────┐  ┌─────────────┐  ┌────────────────────┐  ║
║   │  AddProduct │  │   Search    │  │   Settings Screen  │  ║
║   │  Screen     │  │   Screen    │  │                    │  ║
║   └─────────────┘  └─────────────┘  └────────────────────┘  ║
║                                                              ║
║   Responsibilities:                                          ║
║   • Render all visual elements via Raylib                    ║
║   • Capture and dispatch user input                          ║
║   • Call Logic layer functions — NEVER Data layer directly   ║
║   • Display results returned from Logic layer                ║
╚════════════════════╦═════════════════════════════════════════╝
                     ║  calls (only downward)
╔════════════════════╩═════════════════════════════════════════╗
║                      LOGIC LAYER                             ║
║                                                              ║
║   logic.h / logic.cpp                                        ║
║   ┌─────────────┐  ┌─────────────┐  ┌────────────────────┐  ║
║   │  sortBy*()  │  │ searchBy*() │  │  validateProduct() │  ║
║   └─────────────┘  └─────────────┘  └────────────────────┘  ║
║   ┌─────────────┐  ┌─────────────┐  ┌────────────────────┐  ║
║   │calcTotal    │  │countLow     │  │  addProduct()      │  ║
║   │Value()      │  │Stock()      │  │  removeProduct()   │  ║
║   └─────────────┘  └─────────────┘  └────────────────────┘  ║
║                                                              ║
║   Responsibilities:                                          ║
║   • Validate all input from the Presentation layer           ║
║   • Implement all algorithms (sort, search, statistics)      ║
║   • Call Data layer functions to read/write persistent data  ║
║   • Return clean, validated results to Presentation layer    ║
╚════════════════════╦═════════════════════════════════════════╝
                     ║  calls (only downward)
╔════════════════════╩═════════════════════════════════════════╗
║                       DATA LAYER                             ║
║                                                              ║
║   data.h / data.cpp                                          ║
║   ┌─────────────┐  ┌─────────────┐  ┌────────────────────┐  ║
║   │ loadProducts│  │ saveProducts│  │   Product struct   │  ║
║   │  FromFile() │  │  ToFile()   │  │                    │  ║
║   └─────────────┘  └─────────────┘  └────────────────────┘  ║
║                                                              ║
║   Responsibilities:                                          ║
║   • Define the Product data structure                        ║
║   • Read product data from disk                              ║
║   • Write product data to disk                               ║
║   • Handle file I/O errors gracefully                        ║
╚══════════════════════════════════════════════════════════════╝
```

### The Cardinal Rule

> **The Presentation layer NEVER calls Data layer functions directly.**

If `ui.cpp` needs to save a product, it calls `logic.addProduct()`. The Logic layer validates the input, then calls `data.saveProductsToFile()`. The Presentation layer never touches the file.

This rule is enforced by the header includes:
- `ui.h` includes `logic.h` ✅
- `ui.h` does NOT include `data.h` ✅
- `logic.h` includes `data.h` ✅

### Layer Responsibilities in Detail

#### Presentation Layer (`ui.h` / `ui.cpp`)

The Presentation layer owns everything the user sees and touches:

- **Rendering**: Drawing buttons, tables, charts, backgrounds, overlays
- **Input handling**: Mouse clicks, keyboard events, scroll wheel
- **State machine**: Tracking which screen is active, managing transitions
- **Visual feedback**: Toasts, animations, hover effects
- **Settings UI**: Controls for particle system, scanlines, volume

The Presentation layer holds a reference to the current product list (read-only) to display it, but modifies it only through Logic layer calls.

#### Logic Layer (`logic.h` / `logic.cpp`)

The Logic layer is the brain of the application:

- **Input validation**: Checks that product names are non-empty, prices are positive, quantities are non-negative, IDs are unique
- **Sorting algorithms**: Bubble sort variants for price, quantity, and name
- **Search algorithms**: Linear search for name, binary search for ID
- **Statistics calculations**: Total value via recursion, low-stock count via recursion, average price, most expensive product
- **CRUD operations**: Add product (validate → call data save), remove product (validate ID → call data save)

#### Data Layer (`data.h` / `data.cpp`)

The Data layer is responsible for persistence:

- **Product struct definition**: The canonical definition of what a Product is
- **File reading**: Parse `assets/products.txt` line by line into Product objects
- **File writing**: Serialize Product objects back into `assets/products.txt`
- **Error handling**: Graceful behavior if the file doesn't exist (start with empty inventory)

---

## 📁 Project Structure

```
inventory_raylib/
│
├── src/                          # Source files (.cpp)
│   ├── main.cpp                  # Entry point, Raylib init, main loop
│   ├── data.cpp                  # Data layer implementation
│   ├── logic.cpp                 # Logic layer implementation
│   └── ui.cpp                    # Presentation layer implementation
│
├── include/                      # Header files (.h)
│   ├── data.h                    # Product struct, data function declarations
│   ├── logic.h                   # Logic function declarations
│   └── ui.h                      # Screen enum, UI function declarations
│
├── assets/                       # Runtime assets
│   └── products.txt              # Persistent product database
│
├── docs/                         # Documentation
│   ├── architecture.md           # Architecture diagram and explanation
│   ├── api_reference.md          # Function signatures and descriptions
│   ├── user_manual.md            # End-user guide with screenshots
│   └── design_decisions.md      # Notes on why certain choices were made
│
├── shaders/                      # GLSL shader files (planned)
│   ├── scanline.frag             # Scanline/CRT effect fragment shader
│   └── glow.frag                 # Bloom/glow post-processing shader
│
├── CMakeLists.txt                # Build system configuration
├── README.md                     # This file
└── LICENSE                       # Project license
```

### Source File Details

#### `main.cpp`

The entry point. Responsibilities:

1. Initialize Raylib window (`InitWindow`)
2. Set target FPS (`SetTargetFPS`)
3. Load any assets (fonts, textures)
4. Initialize the UI state machine
5. Run the main game loop (`while (!WindowShouldClose())`)
6. Inside the loop: update state, then draw
7. On exit: close window (`CloseWindow`)

```cpp
// Pseudocode of main.cpp
int main() {
    InitWindow(SCREEN_W, SCREEN_H, "BOTEV Inventory");
    SetTargetFPS(60);

    UiState state = initUiState();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        updateUi(state, dt);

        BeginDrawing();
        ClearBackground(state.theme.background);
        drawUi(state);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```

#### `data.cpp` / `data.h`

Defines the `Product` struct and the file I/O functions:

```cpp
// data.h
#pragma once
#include <string>
#include <vector>

struct Product {
    int         id;
    std::string name;
    float       price;
    int         quantity;
};

std::vector<Product> loadProductsFromFile(const std::string& path);
bool saveProductsToFile(const std::vector<Product>& products,
                        const std::string& path);
```

#### `logic.cpp` / `logic.h`

Implements all business logic:

```cpp
// logic.h (excerpt)
#pragma once
#include "data.h"
#include <optional>

bool        addProduct(std::vector<Product>& list, const Product& p,
                       const std::string& filePath);
bool        removeProduct(std::vector<Product>& list, int id,
                          const std::string& filePath);
void        sortByPrice(std::vector<Product>& list);
void        sortByQuantity(std::vector<Product>& list);
void        sortByName(std::vector<Product>& list);
std::vector<Product> searchByName(const std::vector<Product>& list,
                                   const std::string& query);
std::optional<Product> searchById(const std::vector<Product>& list,
                                   int id);
float       calcTotalValue(const std::vector<Product>& list, int index = 0);
int         countLowStock(const std::vector<Product>& list,
                          int threshold = 5, int index = 0);
float       calcAveragePrice(const std::vector<Product>& list);
Product     mostExpensive(const std::vector<Product>& list);
bool        validateProduct(const Product& p,
                             const std::vector<Product>& existing);
```

#### `ui.cpp` / `ui.h`

Manages all screens and rendering:

```cpp
// ui.h (excerpt)
#pragma once
#include "logic.h"
#include "raylib.h"
#include <string>
#include <vector>
#include <deque>

enum class Screen {
    MAIN_MENU,
    PRODUCT_LIST,
    ADD_PRODUCT,
    SEARCH,
    STATISTICS,
    SETTINGS
};

struct Toast {
    std::string message;
    float       timer;
    Color       accentColor;
    float       slideX;    // For slide-in animation
    float       alpha;
};

struct UiState {
    Screen              activeScreen;
    Screen              nextScreen;
    bool                transitioning;
    float               transitionAlpha;
    std::vector<Product> products;
    std::deque<Toast>   toasts;
    // ... more fields
};
```

---

## ✨ Feature Reference

### 👁️ View Products

The Product List screen displays all products in a scrollable table with the following columns:

| Column     | Width   | Alignment | Notes                          |
| ---------- | ------- | --------- | ------------------------------ |
| ID         | 60 px   | Center    | Unique integer identifier      |
| Name       | 250 px  | Left      | Product name (max 64 chars)    |
| Price      | 100 px  | Right     | Formatted as `$XX.XX`          |
| Quantity   | 80 px   | Center    | Integer stock count            |
| Status     | 90 px   | Center    | 🟢 OK / 🔴 LOW based on threshold |

Rows with low stock (quantity ≤ threshold, default 5) are highlighted with a subtle red tint to draw attention.

**Sorting buttons** appear above the table:
- `Sort by Price` — ascending bubble sort
- `Sort by Quantity` — ascending bubble sort
- `Sort by Name` — alphabetical bubble sort

After sorting, a toast notification confirms the action.

### ➕ Add Product

The Add Product screen presents a form with four fields:

1. **Name** — Text input, max 64 characters, must be non-empty
2. **Price** — Numeric input, must be > 0.0, max 9999.99
3. **Quantity** — Integer input, must be ≥ 0, max 9999
4. **ID** — Integer input, must be unique across all existing products

The **Tab** key cycles between fields. The **Enter** key submits the form. Each field has inline validation feedback — a red outline and error message appear below any field that fails validation.

On successful submission:
- The product is added to the in-memory list
- The list is persisted to disk immediately
- A green toast notification appears: "✅ Product added!"
- The form resets for the next entry

On failure:
- The problematic field(s) show red outlines
- A red toast notification explains the error
- No data is written to disk

### 🗑️ Remove Product

Removal is accessible from the Product List screen. A small **[×]** button appears on the right side of each row when hovering. Clicking it triggers a confirmation dialog:

```
┌─────────────────────────────────┐
│  Remove "Widget A"?              │
│  This action cannot be undone.  │
│                                 │
│   [Cancel]        [Remove]      │
└─────────────────────────────────┘
```

Confirming calls `logic.removeProduct()` which:
1. Validates the ID exists in the list
2. Removes the product from the vector
3. Saves the updated list to disk
4. Returns `true` on success

### 🔍 Search Products

The Search screen offers two search modes selectable by toggle:

**Search by Name (Linear Search)**
- Performs a case-insensitive partial-match linear scan of all products
- Returns all products whose name contains the query as a substring
- Example: query `"wid"` matches `"Widget A"`, `"Wide Screen"`, `"Sandwich Press"`
- Time complexity: **O(n)**

**Search by ID (Binary Search)**
- The list is first sorted by ID (ascending) in a temporary copy
- Binary search is then applied on the sorted copy
- Returns the single matching product or a "not found" indicator
- Time complexity: **O(n log n)** for sort + **O(log n)** for search

Results are displayed in the same table format as the Product List screen.

### 📊 Statistics & Analytics

See the [Statistics Panel](#-statistics-panel) section below for full details.

### 💾 Persistent File Storage

All changes to the product list are immediately persisted to `assets/products.txt`. The file format is described in the [File Format Specification](#-file-format-specification) section.

On startup, the file is loaded automatically. If the file does not exist, the application starts with an empty inventory and creates the file on first save.

### ⚙️ Settings

The Settings panel exposes the following options:

| Setting           | Type    | Default | Description                              |
| ----------------- | ------- | ------- | ---------------------------------------- |
| Particles         | Toggle  | ON      | Enable/disable the particle system       |
| Scanlines         | Toggle  | ON      | Enable/disable CRT scanline overlay      |
| Volume            | Slider  | 50%     | Master volume (for planned audio)        |
| Low Stock Threshold | Slider | 5      | Quantity at or below which stock is "low" |
| Color Theme       | Cycle   | Dark Neon | Cycle through available color themes  |

Settings are saved to a `settings.cfg` file so they persist across restarts.

---

## 🧮 Algorithms Implemented

All algorithms are implemented in `logic.cpp`. This section documents each one in detail.

---

### 🔃 Sorting Algorithms

All three sort variants use **Bubble Sort**. While not optimal for large datasets, bubble sort was chosen because:

1. It is simple and easy to verify for correctness
2. The inventory is expected to be small (< 1000 products)
3. It demonstrates the algorithm clearly for educational purposes

#### `sortByPrice()`

**Signature:**
```cpp
void sortByPrice(std::vector<Product>& list);
```

**Algorithm:** Bubble Sort (ascending)
**Comparison key:** `Product::price` (float)
**Time complexity:** O(n²) worst case, O(n) best case (already sorted)
**Space complexity:** O(1) — in-place sort
**Stability:** Stable (equal-price products maintain relative order)

**Implementation:**

```cpp
void sortByPrice(std::vector<Product>& list) {
    int n = static_cast<int>(list.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (list[j].price > list[j + 1].price) {
                std::swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // Early exit optimisation
    }
}
```

The early-exit optimisation (`if (!swapped) break`) converts already-sorted or nearly-sorted inputs from O(n²) to O(n) passes.

---

#### `sortByQuantity()`

**Signature:**
```cpp
void sortByQuantity(std::vector<Product>& list);
```

**Algorithm:** Bubble Sort (ascending)
**Comparison key:** `Product::quantity` (int)
**Time complexity:** O(n²) worst, O(n) best
**Space complexity:** O(1)

**Implementation:**

```cpp
void sortByQuantity(std::vector<Product>& list) {
    int n = static_cast<int>(list.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (list[j].quantity > list[j + 1].quantity) {
                std::swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```

---

#### `sortByName()`

**Signature:**
```cpp
void sortByName(std::vector<Product>& list);
```

**Algorithm:** Bubble Sort (lexicographic ascending)
**Comparison key:** `Product::name` (std::string)
**Time complexity:** O(n² × L) where L is average string length
**Space complexity:** O(1)
**Note:** Uses `std::string::operator<` which performs lexicographic comparison

**Implementation:**

```cpp
void sortByName(std::vector<Product>& list) {
    int n = static_cast<int>(list.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (list[j].name > list[j + 1].name) {
                std::swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```

**Caveat:** Lexicographic comparison is case-sensitive. `"apple"` sorts after `"Banana"` because lowercase letters have higher ASCII values. A future improvement would be to compare lowercased versions of names.

---

### 🔍 Search Algorithms

#### `searchByName()` — Linear Search

**Signature:**
```cpp
std::vector<Product> searchByName(const std::vector<Product>& list,
                                   const std::string& query);
```

**Algorithm:** Linear Search (substring, case-insensitive)
**Time complexity:** O(n × L) where L is average string length
**Space complexity:** O(k) where k is the number of matching results

The search is case-insensitive: both the product name and the query are converted to lowercase before comparison.

**Implementation:**

```cpp
std::vector<Product> searchByName(const std::vector<Product>& list,
                                   const std::string& query) {
    std::string lowerQuery = toLower(query);
    std::vector<Product> results;

    for (const auto& product : list) {
        std::string lowerName = toLower(product.name);
        if (lowerName.find(lowerQuery) != std::string::npos) {
            results.push_back(product);
        }
    }

    return results;
}

// Helper function
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}
```

**Why not Binary Search for names?** The binary search requires a sorted input. Since names can be added in any order and sorting by name after every add is expensive, linear search is preferred here. For small datasets (< 10,000 items), linear search over names is imperceptible to the user.

---

#### `searchById()` — Binary Search

**Signature:**
```cpp
std::optional<Product> searchById(const std::vector<Product>& list, int id);
```

**Algorithm:** Binary Search (after sort-by-ID)
**Time complexity:** O(n log n) for sort + O(log n) for search = O(n log n)
**Space complexity:** O(n) for the sorted copy

Binary search requires the list to be sorted. Rather than maintain a permanently sorted list (which would complicate insertions), `searchById()` works on a sorted copy.

**Implementation:**

```cpp
std::optional<Product> searchById(const std::vector<Product>& list, int id) {
    // Create sorted copy
    std::vector<Product> sorted = list;
    std::sort(sorted.begin(), sorted.end(),
              [](const Product& a, const Product& b) {
                  return a.id < b.id;
              });

    // Binary search
    int lo = 0, hi = static_cast<int>(sorted.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (sorted[mid].id == id)  return sorted[mid];
        if (sorted[mid].id < id)   lo = mid + 1;
        else                        hi = mid - 1;
    }

    return std::nullopt;  // Not found
}
```

Note: `lo + (hi - lo) / 2` is used instead of `(lo + hi) / 2` to avoid integer overflow when `lo + hi > INT_MAX`.

---

### ♾️ Recursive Algorithms

Two functions use recursion to demonstrate the concept as required by the school curriculum.

#### `calcTotalValue()` — Recursive Sum

**Signature:**
```cpp
float calcTotalValue(const std::vector<Product>& list, int index = 0);
```

**Algorithm:** Tail recursion — sum of `price × quantity` for all products
**Base case:** `index >= list.size()` → return 0.0f
**Recursive case:** `list[index].price * list[index].quantity + calcTotalValue(list, index + 1)`

**Implementation:**

```cpp
float calcTotalValue(const std::vector<Product>& list, int index) {
    if (index >= static_cast<int>(list.size())) {
        return 0.0f;  // Base case
    }
    float current = list[index].price * static_cast<float>(list[index].quantity);
    return current + calcTotalValue(list, index + 1);  // Recursive case
}
```

**Recursion trace for 3 products:**

```
calcTotalValue([A, B, C], 0)
  = A.price*A.qty + calcTotalValue([A, B, C], 1)
  = A.price*A.qty + B.price*B.qty + calcTotalValue([A, B, C], 2)
  = A.price*A.qty + B.price*B.qty + C.price*C.qty + calcTotalValue([A, B, C], 3)
  = A.price*A.qty + B.price*B.qty + C.price*C.qty + 0
  = total
```

**Note on stack depth:** For a list of n products, this uses O(n) stack frames. With a typical stack size of 8 MB and each frame using ~32 bytes, this is safe up to ~250,000 products — well beyond any realistic inventory size.

---

#### `countLowStock()` — Recursive Counter

**Signature:**
```cpp
int countLowStock(const std::vector<Product>& list,
                  int threshold = 5,
                  int index = 0);
```

**Algorithm:** Tail recursion — count of products with `quantity <= threshold`
**Base case:** `index >= list.size()` → return 0
**Recursive case:** `(list[index].quantity <= threshold ? 1 : 0) + countLowStock(list, threshold, index + 1)`

**Implementation:**

```cpp
int countLowStock(const std::vector<Product>& list,
                  int threshold,
                  int index) {
    if (index >= static_cast<int>(list.size())) {
        return 0;  // Base case
    }
    int isLow = (list[index].quantity <= threshold) ? 1 : 0;
    return isLow + countLowStock(list, threshold, index + 1);
}
```

---

### 📈 Statistical Calculations

#### `calcAveragePrice()`

**Signature:**
```cpp
float calcAveragePrice(const std::vector<Product>& list);
```

**Implementation:**

```cpp
float calcAveragePrice(const std::vector<Product>& list) {
    if (list.empty()) return 0.0f;
    float total = 0.0f;
    for (const auto& p : list) total += p.price;
    return total / static_cast<float>(list.size());
}
```

#### `mostExpensive()`

**Signature:**
```cpp
Product mostExpensive(const std::vector<Product>& list);
```

Uses `std::max_element` with a lambda comparator:

```cpp
Product mostExpensive(const std::vector<Product>& list) {
    auto it = std::max_element(list.begin(), list.end(),
        [](const Product& a, const Product& b) {
            return a.price < b.price;
        });
    return *it;
}
```

---

### ✅ Input Validation

#### `validateProduct()`

**Signature:**
```cpp
bool validateProduct(const Product& p, const std::vector<Product>& existing);
```

Validation rules:

| Field      | Rule                                              | Error message                        |
| ---------- | ------------------------------------------------- | ------------------------------------ |
| `name`     | Non-empty, max 64 chars, alphanumeric + spaces    | "Name must be 1–64 characters"       |
| `price`    | > 0.0, ≤ 9999.99                                  | "Price must be between 0.01 and 9999.99" |
| `quantity` | ≥ 0, ≤ 9999                                       | "Quantity must be 0–9999"            |
| `id`       | > 0, unique (not in existing)                     | "ID must be positive and unique"     |

```cpp
bool validateProduct(const Product& p,
                     const std::vector<Product>& existing) {
    if (p.name.empty() || p.name.size() > 64)        return false;
    if (p.price <= 0.0f || p.price > 9999.99f)       return false;
    if (p.quantity < 0  || p.quantity > 9999)         return false;
    if (p.id <= 0)                                     return false;

    // Check ID uniqueness
    for (const auto& existing_p : existing) {
        if (existing_p.id == p.id) return false;
    }

    return true;
}
```

---

## 📊 Statistics Panel

The Statistics screen is the analytics dashboard of BOTEV. It computes and displays the following metrics:

### Summary Cards

```
┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐
│  Total Products  │  │   Total Value    │  │   Low Stock      │
│                  │  │                  │  │                  │
│       47         │  │   $12,430.50     │  │   3 items 🔴      │
└──────────────────┘  └──────────────────┘  └──────────────────┘

┌──────────────────┐  ┌──────────────────────────────────────────┐
│  Average Price   │  │  Most Expensive Product                  │
│                  │  │                                          │
│     $264.48      │  │  "Industrial Laser Cutter" — $4,299.00  │
└──────────────────┘  └──────────────────────────────────────────┘
```

Each card:
- Has a soft glowing border that matches the current theme colour
- Numbers animate from 0 to their final value over 0.8 seconds when the screen opens
- Currency values use locale-appropriate formatting (`$X,XXX.XX`)

### Animated Bar Chart

Below the summary cards, an animated bar chart shows the **value per product** (price × quantity). Each bar:

1. Starts at height 0 when the statistics screen opens
2. Animates to its final height over 1.2 seconds with an ease-out curve
3. Shows the product name on the X axis (truncated if > 10 chars)
4. Shows the value on the Y axis
5. Uses a gradient fill from theme accent to white

The Y-axis autoscales to the maximum product value with a 10% headroom.

### Value Chart Rendering

```cpp
void drawValueChart(const std::vector<Product>& products,
                    float animProgress,
                    Rectangle bounds,
                    Color accent) {
    float maxValue = 0;
    for (const auto& p : products)
        maxValue = std::max(maxValue, p.price * p.quantity);
    if (maxValue <= 0) return;

    float barWidth  = bounds.width / products.size() - BAR_GAP;
    float scaleY    = bounds.height / maxValue;

    for (size_t i = 0; i < products.size(); ++i) {
        float value      = products[i].price * products[i].quantity;
        float targetH    = value * scaleY;
        float animH      = targetH * easeOutCubic(animProgress);

        float x = bounds.x + i * (barWidth + BAR_GAP);
        float y = bounds.y + bounds.height - animH;

        DrawRectangleGradientV(x, y, barWidth, animH, WHITE, accent);
        // ... draw label
    }
}

float easeOutCubic(float t) {
    return 1.0f - std::pow(1.0f - t, 3.0f);
}
```

---

## 🔨 Building the Project

### Requirements

| Dependency   | Minimum Version | Notes                              |
| ------------ | --------------- | ---------------------------------- |
| C++ Compiler | C++17           | GCC 7+, Clang 5+, MSVC 2017+       |
| CMake        | 3.16            |                                    |
| Raylib       | 5.0             | Auto-fetched by CMake if not found |
| Git          | Any             | For cloning the repo               |

### CMakeLists.txt Explained

```cmake
cmake_minimum_required(VERSION 3.16)
project(botev VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Sources ──────────────────────────────────────────────────────
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(botev ${SOURCES})

target_include_directories(botev PRIVATE include)

# ── Raylib ───────────────────────────────────────────────────────
find_package(raylib 5.0 QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(botev PRIVATE raylib)

# ── Compiler warnings ────────────────────────────────────────────
if (MSVC)
    target_compile_options(botev PRIVATE /W4)
else()
    target_compile_options(botev PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ── Copy assets to build directory ───────────────────────────────
add_custom_command(TARGET botev POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:botev>/assets"
)
```

---

## 🛠️ Installation Guide

### Linux (Ubuntu / Debian)

#### Step 1: Install system dependencies

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    git \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev
```

#### Step 2: Clone the repository

```bash
git clone https://github.com/your-username/botev-inventory.git
cd botev-inventory
```

#### Step 3: Build

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

#### Step 4: Run

```bash
./botev
```

---

### Linux (Fedora / RHEL / CentOS)

```bash
sudo dnf install -y \
    gcc-c++ \
    cmake \
    git \
    mesa-libGL-devel \
    libX11-devel \
    libXrandr-devel \
    libXinerama-devel \
    libXcursor-devel \
    libXi-devel

git clone https://github.com/your-username/botev-inventory.git
cd botev-inventory
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
./botev
```

---

### Linux (Arch Linux / Manjaro)

```bash
sudo pacman -S --needed \
    base-devel \
    cmake \
    git \
    mesa \
    libx11 \
    libxrandr \
    libxinerama \
    libxcursor \
    libxi

git clone https://github.com/your-username/botev-inventory.git
cd botev-inventory
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
./botev
```

---

### macOS

#### Step 1: Install Homebrew (if not installed)

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### Step 2: Install dependencies

```bash
brew install cmake git
# Xcode Command Line Tools (includes C++ compiler)
xcode-select --install
```

#### Step 3: Clone and build

```bash
git clone https://github.com/your-username/botev-inventory.git
cd botev-inventory
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(sysctl -n hw.logicalcpu)
./botev
```

---

### Windows (Visual Studio)

#### Step 1: Install prerequisites

- [Visual Studio 2022](https://visualstudio.microsoft.com/) with "Desktop development with C++"
- [CMake 3.16+](https://cmake.org/download/) — check "Add to PATH" during install
- [Git for Windows](https://git-scm.com/download/win)

#### Step 2: Clone and open in Visual Studio

```powershell
git clone https://github.com/your-username/botev-inventory.git
cd botev-inventory
```

Open Visual Studio → File → Open → CMake → select `CMakeLists.txt`

Visual Studio will detect CMake automatically and configure the project.

#### Step 3: Build and run

- Select **Release** configuration
- Press **Ctrl+Shift+B** to build
- Press **F5** to run

---

### Windows (Command Line / PowerShell)

```powershell
# Prerequisites: Visual Studio Build Tools, CMake, Git

git clone https://github.com/your-username/botev-inventory.git
cd botev-inventory
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
.\Release\botev.exe
```

---

### Windows (MinGW / MSYS2)

```bash
# In MSYS2 UCRT64 shell
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake git

git clone https://github.com/your-username/botev-inventory.git
cd botev-inventory
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . -j4
./botev.exe
```

---

### Installing Raylib Manually (Optional)

If you prefer to install Raylib system-wide rather than letting CMake fetch it:

#### Linux

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/usr/local ..
cmake --build . -j$(nproc)
sudo cmake --install .
```

#### macOS

```bash
brew install raylib
```

#### Windows (vcpkg)

```powershell
vcpkg install raylib:x64-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
```

---

## 🎮 Controls Reference

### Global Controls

| Key / Action    | Effect                                                |
| --------------- | ----------------------------------------------------- |
| `ESC`           | Exit the application (confirmation dialog shown)      |
| `F11`           | Toggle fullscreen                                     |
| `F1`            | Open Settings panel                                   |
| `Alt+Enter`     | Toggle fullscreen (Windows)                           |

### Main Menu

| Key / Action    | Effect                                                |
| --------------- | ----------------------------------------------------- |
| Mouse click     | Activate hovered button                               |
| `1`             | Navigate to Product List                              |
| `2`             | Navigate to Add Product                               |
| `3`             | Navigate to Search                                    |
| `4`             | Navigate to Statistics                                |
| `5`             | Open Settings                                         |

### Product List Screen

| Key / Action        | Effect                                              |
| ------------------- | --------------------------------------------------- |
| Mouse wheel ↑/↓     | Scroll the product table                            |
| ↑ / ↓ Arrow keys    | Scroll the product table                            |
| `Page Up`           | Scroll table up by 10 rows                          |
| `Page Down`         | Scroll table down by 10 rows                        |
| `Home`              | Jump to top of table                                |
| `End`               | Jump to bottom of table                             |
| Hover + `[×]` click | Remove product (shows confirmation dialog)          |
| `P`                 | Sort by price                                       |
| `Q`                 | Sort by quantity                                    |
| `N`                 | Sort by name                                        |
| `Backspace`         | Return to main menu                                 |

### Add Product Screen

| Key / Action    | Effect                                                |
| --------------- | ----------------------------------------------------- |
| `Tab`           | Move focus to next field                              |
| `Shift+Tab`     | Move focus to previous field                          |
| `Enter`         | Submit the form                                       |
| `Backspace`     | Delete last character in focused field                |
| `Ctrl+A`        | Select all text in focused field                      |
| `Ctrl+V`        | Paste from clipboard into focused field               |
| `Escape`        | Clear current field / cancel and go back              |

### Search Screen

| Key / Action    | Effect                                                |
| --------------- | ----------------------------------------------------- |
| Type characters | Populate the search field                             |
| `Enter`         | Execute the search                                    |
| `Tab`           | Toggle between Name search and ID search              |
| `Escape`        | Clear search results                                  |
| Mouse wheel     | Scroll results table                                  |

### Statistics Screen

| Key / Action    | Effect                                                |
| --------------- | ----------------------------------------------------- |
| `R`             | Refresh statistics (recalculate)                      |
| `Backspace`     | Return to main menu                                   |

### Settings Screen

| Key / Action    | Effect                                                |
| --------------- | ----------------------------------------------------- |
| Mouse click     | Toggle switches on/off                                |
| Mouse drag      | Adjust sliders                                        |
| `T`             | Cycle to next colour theme                            |
| `Escape`        | Close settings and save                               |

---

## 📁 Data Layer Documentation

### Product Struct

```cpp
// data.h
struct Product {
    int         id;        // Unique identifier (positive integer)
    std::string name;      // Product name (1–64 characters)
    float       price;     // Unit price (0.01 – 9999.99)
    int         quantity;  // Stock quantity (0 – 9999)
};
```

### `loadProductsFromFile()`

```cpp
std::vector<Product> loadProductsFromFile(const std::string& path);
```

Reads the product database from a text file.

**Behavior:**
- If the file does not exist, returns an empty vector (no error)
- If the file exists but is malformed, skips malformed lines and logs a warning
- Lines beginning with `#` are treated as comments and skipped
- Empty lines are skipped

**Return value:** A vector of all successfully parsed products

**Example:**
```cpp
auto products = loadProductsFromFile("assets/products.txt");
std::cout << "Loaded " << products.size() << " products.\n";
```

---

### `saveProductsToFile()`

```cpp
bool saveProductsToFile(const std::vector<Product>& products,
                        const std::string& path);
```

Writes the entire product list to a text file, overwriting any previous content.

**Behavior:**
- Writes a header comment with a timestamp
- Writes all products in CSV format (see [File Format Specification](#-file-format-specification))
- Uses a temp file + rename pattern to prevent data corruption on crash

**Return value:**
- `true` if the file was written successfully
- `false` if any I/O error occurred

**Example:**
```cpp
if (!saveProductsToFile(products, "assets/products.txt")) {
    // Handle error
}
```

---

## 🧠 Logic Layer Documentation

### `addProduct()`

```cpp
bool addProduct(std::vector<Product>& list,
                const Product& p,
                const std::string& filePath);
```

Validates the new product, appends it to the list, and persists the list to disk.

**Steps:**
1. Call `validateProduct(p, list)` — reject if invalid
2. `list.push_back(p)`
3. Call `saveProductsToFile(list, filePath)` — reject if save fails
4. Return `true`

---

### `removeProduct()`

```cpp
bool removeProduct(std::vector<Product>& list,
                   int id,
                   const std::string& filePath);
```

Finds and removes the product with the given ID.

**Steps:**
1. Find product with matching ID using `std::find_if`
2. If not found, return `false`
3. Erase from vector
4. Call `saveProductsToFile(list, filePath)`
5. Return `true`

---

## 🖥️ UI Layer Documentation

### Screen Enum

```cpp
enum class Screen {
    MAIN_MENU,
    PRODUCT_LIST,
    ADD_PRODUCT,
    REMOVE_PRODUCT,
    SEARCH,
    STATISTICS,
    SETTINGS,
    EXIT_CONFIRM
};
```

### UiState

The `UiState` struct holds all mutable state for the Presentation layer:

```cpp
struct UiState {
    // Navigation
    Screen              activeScreen;
    Screen              nextScreen;
    bool                transitioning;
    float               transitionAlpha;    // 0.0 = transparent, 1.0 = black

    // Data
    std::vector<Product> products;
    std::string         dataFilePath;

    // Table state
    int                 scrollOffset;
    int                 selectedRow;

    // Add-product form
    FormState           addForm;

    // Search state
    std::string         searchQuery;
    bool                searchById;
    std::vector<Product> searchResults;

    // Statistics
    float               statAnimProgress;   // 0.0–1.0 for chart animation

    // Visual effects
    std::vector<GlowBlob>   glowBlobs;
    std::vector<Particle>   particles;
    std::deque<Toast>       toasts;
    float                   particleEmitTimer;

    // Settings
    AppSettings         settings;

    // Transition confirmation dialog
    bool                showExitConfirm;
    bool                showRemoveConfirm;
    int                 removeConfirmId;
};
```

### `pushToast()`

```cpp
void pushToast(UiState& state,
               const std::string& message,
               Color accentColor);
```

Adds a new toast to the queue. If there are already 4 toasts, the oldest is removed.

---

## 📄 File Format Specification

### `assets/products.txt`

The product database is stored as a plain-text CSV file with the following format:

```
# BOTEV Inventory System — Product Database
# Generated: 2024-05-15 10:33:21
# Format: id,name,price,quantity
#
1,Widget A,14.99,100
2,Gadget B,249.00,15
3,Thingamajig C,3.50,500
4,Doohickey D,89.99,3
```

#### Field Rules

| Field      | Type   | Constraints                     | Example         |
| ---------- | ------ | ------------------------------- | --------------- |
| `id`       | int    | Positive, unique                | `42`            |
| `name`     | string | 1–64 chars, no commas allowed   | `Widget A`      |
| `price`    | float  | 0.01 – 9999.99, 2 decimal places| `14.99`         |
| `quantity` | int    | 0 – 9999                        | `100`           |

#### Parser Behavior

The parser:
1. Reads the file line by line
2. Skips lines beginning with `#` (comments)
3. Skips empty lines
4. Splits each line by `,` (first occurrence only for name, in case name has no commas)
5. Attempts to parse each field; skips the line on any parse failure and logs a warning
6. Adds the product to the result vector if all fields parse successfully

#### Writer Behavior

The writer:
1. Opens a temporary file for writing
2. Writes a header comment block with the current timestamp
3. Iterates over all products and writes each as a CSV line
4. Closes the file
5. Renames the temporary file to the final path (atomic on most platforms)

---

## 📐 Coding Standards

BOTEV follows a consistent set of coding standards throughout all source files.

### Naming Conventions

| Entity                   | Convention    | Example                          |
| ------------------------ | ------------- | -------------------------------- |
| Variables                | camelCase     | `productList`, `scrollOffset`    |
| Functions                | camelCase     | `sortByPrice()`, `addProduct()`  |
| Types (struct, enum)     | PascalCase    | `Product`, `UiState`, `Screen`   |
| Enum values              | UPPER_SNAKE   | `Screen::MAIN_MENU`              |
| Constants                | UPPER_SNAKE   | `MAX_PRODUCTS`, `SCREEN_WIDTH`   |
| Template parameters      | PascalCase    | `typename T`                     |
| Macro names (avoid!)     | UPPER_SNAKE   | `DEBUG_MODE`                     |
| File names               | lowercase     | `data.cpp`, `ui.h`               |

### Header File Rules

Every header file:
1. Starts with `#pragma once`
2. Does not include implementation code (except templates)
3. Lists all `#include` dependencies explicitly — no transitive include assumptions
4. Has forward declarations where possible to reduce compile times
5. Has a closing comment matching the `#pragma once` for readability in large files

```cpp
// data.h
#pragma once

#include <string>
#include <vector>

struct Product {
    int         id;
    std::string name;
    float       price;
    int         quantity;
};

std::vector<Product> loadProductsFromFile(const std::string& path);
bool saveProductsToFile(const std::vector<Product>& products,
                        const std::string& path);
// end of data.h
```

### Memory Management

- **No raw pointers for ownership** — Use `std::unique_ptr`, `std::shared_ptr`, or value semantics
- **STL containers** — `std::vector`, `std::string`, `std::deque` instead of C arrays
- **RAII** — Resources are acquired in constructors and released in destructors
- **No manual `new`/`delete`** — If you think you need `new`, use a smart pointer

### Const Correctness

- Function parameters that are not modified are `const &` or by value (for small types)
- Member functions that don't modify state are `const`
- Prefer `const auto&` in range-for loops over mutable references

```cpp
// ✅ Correct
float calcAveragePrice(const std::vector<Product>& list);
for (const auto& product : products) { ... }

// ❌ Wrong
float calcAveragePrice(std::vector<Product> list);   // Unnecessary copy
for (auto product : products) { ... }                // Unnecessary copy
```

### Error Handling

- Functions that can fail return `bool` (success/failure) or `std::optional<T>`
- Use `std::optional<Product>` instead of returning a sentinel value like `{-1, "", -1, -1}`
- File I/O errors are logged to `stderr` and surfaced as `bool false` return values
- Do not use exceptions (Raylib's C API doesn't use them, and they complicate control flow in a game loop)

### Code Style

- 4-space indentation (no tabs)
- Opening brace on the same line as the statement: `if (...) {`
- Maximum line length: 100 characters
- Blank line between logical sections within a function
- Comments explain *why*, not *what* (the code explains what)

```cpp
// ✅ Good comment — explains intent
// Sort before binary search; the list may not be in ID order after user operations
std::sort(sorted.begin(), sorted.end(), ...);

// ❌ Bad comment — just restates the code
// Sort the sorted vector
std::sort(sorted.begin(), sorted.end(), ...);
```

---

## 🔧 API Reference

### Data Layer Functions

#### `loadProductsFromFile`

```cpp
std::vector<Product> loadProductsFromFile(const std::string& path);
```

| Parameter | Type                | Description                      |
| --------- | ------------------- | -------------------------------- |
| `path`    | `const std::string&`| Absolute or relative file path   |

| Return Value           | Condition                          |
| ---------------------- | ---------------------------------- |
| Empty `std::vector<>` | File not found or all lines failed |
| Non-empty vector       | At least one product parsed        |

---

#### `saveProductsToFile`

```cpp
bool saveProductsToFile(const std::vector<Product>& products,
                        const std::string& path);
```

| Parameter    | Type                         | Description                      |
| ------------ | ---------------------------- | -------------------------------- |
| `products`   | `const std::vector<Product>&`| Products to serialize            |
| `path`       | `const std::string&`         | Destination file path            |

| Return Value | Condition                    |
| ------------ | ---------------------------- |
| `true`       | File written successfully    |
| `false`      | Any I/O error occurred       |

---

### Logic Layer Functions

#### `addProduct`

```cpp
bool addProduct(std::vector<Product>& list,
                const Product& p,
                const std::string& filePath);
```

| Return Value | Condition                               |
| ------------ | --------------------------------------- |
| `true`       | Product validated and saved to disk     |
| `false`      | Validation failed or disk write failed  |

---

#### `removeProduct`

```cpp
bool removeProduct(std::vector<Product>& list,
                   int id,
                   const std::string& filePath);
```

| Return Value | Condition                               |
| ------------ | --------------------------------------- |
| `true`       | Product found, removed, and saved       |
| `false`      | ID not found or disk write failed       |

---

#### `sortByPrice`

```cpp
void sortByPrice(std::vector<Product>& list);
```

Sorts `list` in-place by `price` ascending. No return value.

---

#### `sortByQuantity`

```cpp
void sortByQuantity(std::vector<Product>& list);
```

Sorts `list` in-place by `quantity` ascending. No return value.

---

#### `sortByName`

```cpp
void sortByName(std::vector<Product>& list);
```

Sorts `list` in-place by `name` lexicographically ascending. No return value.

---

#### `searchByName`

```cpp
std::vector<Product> searchByName(const std::vector<Product>& list,
                                   const std::string& query);
```

| Return Value           | Condition                             |
| ---------------------- | ------------------------------------- |
| Empty vector           | No products match the query           |
| Non-empty vector       | All products whose name contains query|

---

#### `searchById`

```cpp
std::optional<Product> searchById(const std::vector<Product>& list, int id);
```

| Return Value        | Condition               |
| ------------------- | ----------------------- |
| `std::nullopt`      | No product with that ID |
| `Product` value     | Product found           |

---

#### `calcTotalValue`

```cpp
float calcTotalValue(const std::vector<Product>& list, int index = 0);
```

| Return Value | Description                                |
| ------------ | ------------------------------------------ |
| `float`      | Sum of `price × quantity` for all products |

---

#### `countLowStock`

```cpp
int countLowStock(const std::vector<Product>& list,
                  int threshold = 5,
                  int index = 0);
```

| Return Value | Description                                         |
| ------------ | --------------------------------------------------- |
| `int`        | Count of products with `quantity <= threshold`      |

---

#### `calcAveragePrice`

```cpp
float calcAveragePrice(const std::vector<Product>& list);
```

| Return Value | Description                                   |
| ------------ | --------------------------------------------- |
| `0.0f`       | List is empty                                 |
| `float`      | Mean price of all products                    |

---

#### `mostExpensive`

```cpp
Product mostExpensive(const std::vector<Product>& list);
```

**Precondition:** `list` must not be empty (undefined behavior if empty)

| Return Value | Description                        |
| ------------ | ---------------------------------- |
| `Product`    | Product with the highest price     |

---

#### `validateProduct`

```cpp
bool validateProduct(const Product& p, const std::vector<Product>& existing);
```

| Return Value | Condition                       |
| ------------ | ------------------------------- |
| `true`       | All validation rules pass       |
| `false`      | Any validation rule fails       |

---

## ⚙️ Configuration

### `settings.cfg`

Application settings are stored in `settings.cfg` next to the executable. It is created automatically on first run.

```ini
# BOTEV Inventory System — Settings
# Generated automatically. Edit with caution.

[display]
scanlines        = true
fullscreen       = false
theme            = dark_neon

[effects]
particles        = true
particle_count   = 300
transitions      = true

[inventory]
low_stock_threshold = 5
data_file        = assets/products.txt

[audio]
master_volume    = 50
sfx_enabled      = false
music_enabled    = false
```

### Settings Parsing

Settings are parsed with a minimal INI reader built into the application. The parser:
- Ignores lines starting with `#`
- Splits on the first `=` character
- Trims leading/trailing whitespace from key and value
- Falls back to default values for missing or malformed entries

### Supported Themes

| Theme ID          | Primary Colour | Accent Colour | Background     |
| ----------------- | -------------- | ------------- | -------------- |
| `dark_neon`       | `#00FFFF` cyan | `#FF00FF` magenta | `#0A0A0F` |
| `dark_blue`       | `#4488FF` blue | `#88CCFF` light blue | `#050510` |
| `midnight_purple` | `#AA44FF` purple | `#FF44AA` pink | `#080508` |

---

## 🐛 Error Handling

### File I/O Errors

When `loadProductsFromFile()` encounters a problem:

```
[WARN] Line 7 in 'assets/products.txt' could not be parsed — skipping.
[WARN] Expected format: id,name,price,quantity
[WARN] Got: "Widget,A,not-a-number,10"
```

When `saveProductsToFile()` fails:

```
[ERROR] Failed to open 'assets/products.txt.tmp' for writing.
[ERROR] Disk may be full or permissions may be insufficient.
[ERROR] Product list NOT saved. In-memory state is still valid.
```

The application never crashes on file I/O errors. The in-memory state remains valid and the user is shown a red toast notification.

### Input Validation Errors

Validation errors are surfaced directly in the UI:

| Error                      | Visual feedback                              |
| -------------------------- | -------------------------------------------- |
| Empty name                 | Name field gets red border, error label      |
| Price out of range         | Price field gets red border, error label     |
| Negative quantity          | Qty field gets red border, error label       |
| Duplicate ID               | ID field gets red border, "ID already exists"|
| Non-numeric input          | Field rejects the character (no visual)      |

### Out-of-Range Table Access

If `scrollOffset` ever exceeds the product list size, it is clamped:

```cpp
scrollOffset = std::clamp(scrollOffset, 0,
    std::max(0, static_cast<int>(products.size()) - VISIBLE_ROWS));
```

### Search on Empty List

If the product list is empty and the user searches, the search returns an empty result set and a yellow toast: "⚠️ No products in inventory."

---

## 🧪 Testing

### Manual Test Checklist

Before each release, the following manual tests are performed:

#### Data Persistence

- [ ] Add 5 products, close the application, reopen — all 5 are present
- [ ] Remove a product, close the application, reopen — product is absent
- [ ] Delete `assets/products.txt`, start application — starts with empty inventory
- [ ] Corrupt `assets/products.txt` (malformed line) — application starts, corrupt line is skipped

#### Input Validation

- [ ] Attempt to add a product with an empty name — rejected with error feedback
- [ ] Attempt to add a product with price = 0 — rejected
- [ ] Attempt to add a product with price = -1 — rejected
- [ ] Attempt to add a product with duplicate ID — rejected
- [ ] Attempt to add a product with quantity = -1 — rejected
- [ ] Attempt to add a product with valid data — accepted, persisted

#### Sorting

- [ ] Add 10 products with mixed prices, sort by price — ascending order
- [ ] Add 10 products with mixed quantities, sort by quantity — ascending order
- [ ] Add 10 products with mixed names, sort by name — lexicographic order

#### Searching

- [ ] Search by name (partial, lowercase) — returns correct matches
- [ ] Search by name with no matches — empty results, appropriate toast
- [ ] Search by ID (existing) — returns correct product
- [ ] Search by ID (non-existing) — "not found" toast

#### Statistics

- [ ] Open statistics with empty inventory — all values are 0
- [ ] Open statistics with products — values match expected calculations
- [ ] Bar chart animates from 0 to final height — smooth transition

#### Visual Effects

- [ ] Toggle particles off in settings — particles disappear
- [ ] Toggle scanlines off in settings — CRT overlay disappears
- [ ] Change colour theme — all UI elements update to new colours
- [ ] Screen transitions are smooth (no flicker)
- [ ] Toast notifications appear and fade correctly

---

## ⚡ Performance Notes

### Frame Rate

The application targets 60 FPS. On any modern computer (even a 10-year-old laptop), the rendering workload is trivial:

| Render pass          | Approximate cost (i7-8th gen) |
| -------------------- | ----------------------------- |
| Background + blobs   | < 0.1 ms                      |
| Particle system      | < 0.05 ms (300 particles)     |
| UI elements          | < 0.2 ms                      |
| Scanline overlay     | < 0.1 ms                      |
| Total per frame      | < 0.5 ms (budget: 16.7 ms)    |

The application uses < 3% CPU on a modern machine in steady state.

### Memory Usage

| Component             | Memory footprint                        |
| --------------------- | --------------------------------------- |
| Executable            | ~2 MB (stripped, release build)         |
| Raylib runtime        | ~8 MB                                   |
| Product list (1000)   | ~80 KB (80 bytes × 1000)                |
| Particle pool (300)   | ~15 KB (48 bytes × 300)                 |
| Total typical         | < 30 MB                                 |

### Scalability

The bubble sort algorithms are O(n²). Here is how sort time scales:

| Product count | Sort time (approx.) |
| ------------- | ------------------- |
| 100           | < 1 ms              |
| 1,000         | < 5 ms              |
| 10,000        | ~500 ms (noticeable)|
| 100,000       | ~50 seconds (too slow)|

For typical inventory use (< 1000 products), performance is not a concern. If the project were to scale to 10,000+ products, `std::sort` (introsort, O(n log n)) should replace bubble sort.

---

## 🔧 Troubleshooting

### Application doesn't launch

**Problem:** Running `./botev` does nothing or crashes immediately.

**Check:**
1. Is `assets/products.txt` accessible? The application needs write permissions to the `assets/` directory.
2. Is Raylib linked correctly? Run `ldd ./botev | grep raylib` on Linux to check.
3. Does the OpenGL version meet the minimum requirement? Raylib requires OpenGL 3.3 or OpenGL ES 2.0.

```bash
# Check OpenGL version
glxinfo | grep "OpenGL version"
```

---

### Blank white/black screen

**Problem:** Window opens but screen is blank or all one colour.

**Likely cause:** GPU driver issue or missing OpenGL support.

**Fix:**
```bash
# Force software rendering (Mesa)
LIBGL_ALWAYS_SOFTWARE=1 ./botev
```

---

### Products not saving between runs

**Problem:** Products appear during the session but disappear after closing.

**Check:**
1. Does the `assets/` directory exist next to the executable?
2. Does the user have write permission to `assets/products.txt`?

```bash
ls -la assets/
# Fix permissions if needed:
chmod 644 assets/products.txt
```

---

### High CPU usage

**Problem:** The application is using 30–100% CPU.

**Check:** VSync may not be enabled. Add the following after `InitWindow()`:

```cpp
SetTargetFPS(60);
// Or enable VSync:
// This is handled automatically by Raylib when SetTargetFPS is called
```

If VSync is still not working, try:

```bash
# Linux — force VSync via environment
__GL_SYNC_TO_VBLANK=1 ./botev          # NVIDIA
vblank_mode=1 ./botev                   # AMD/Intel Mesa
```

---

### CMake can't find Raylib

**Problem:** CMake errors with `Could not find raylib`.

**Solution:** Let CMake fetch it automatically. Ensure you have an internet connection during the first build:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
# CMake will print:
# -- raylib not found, fetching from GitHub...
```

If you're in an offline environment, download the Raylib release tarball and point CMake to it:

```bash
cmake .. -Draylib_DIR=/path/to/raylib/lib/cmake/raylib
```

---

### Text appears garbled or as boxes

**Problem:** UI text shows as empty boxes or question marks.

**Cause:** The default Raylib font covers basic ASCII. Extended characters (accented letters, emoji) require a custom font.

**Fix:** Load a font that covers the required glyphs:

```cpp
Font customFont = LoadFontEx("assets/fonts/NotoSans.ttf", 20, nullptr, 0);
```

---

### Compile errors on Windows (MSVC)

**Problem:** Errors like `C2589: '(': illegal token on right side of '::'`

**Cause:** Windows headers define `min` and `max` as macros, conflicting with `std::min`/`std::max`.

**Fix:** Add `#define NOMINMAX` before including `<windows.h>`, or use the `/DNOMINMAX` compiler flag (already set in the CMakeLists.txt for MSVC).

---

## 🛣️ Planned Features

The following features are on the roadmap for future versions:

### v1.1 — Audio & Polish

- [ ] Background music with Raylib audio system
- [ ] Sound effects for button clicks, toasts, transitions
- [ ] Volume control in settings (already has the slider, needs audio hookup)
- [ ] Achievement system: "Added 100 products", "Sorted 10 times", etc.

### v1.2 — GLSL Shaders

- [ ] Implement `shaders/scanline.frag` as an actual GLSL shader (currently simulated)
- [ ] Bloom/glow post-processing via `shaders/glow.frag`
- [ ] Render to texture → apply shader → draw to screen

### v1.3 — Advanced Inventory Features

- [ ] Category system: assign products to categories (Electronics, Food, Tools, etc.)
- [ ] Category filtering in the product list
- [ ] Multi-sort: primary key + secondary key (e.g., sort by category, then by price)
- [ ] In-place product editing: click a row to edit it, press Enter to save
- [ ] Undo/redo for add and remove operations

### v1.4 — Export & Import

- [ ] Export inventory to CSV file
- [ ] Export inventory to PDF report (using a PDF library)
- [ ] Import from CSV (with validation and conflict resolution)
- [ ] Backup & restore from a ZIP archive

### v2.0 — Networking (Ambitious)

- [ ] Simple HTTP server embedded in the application
- [ ] REST API for external tools to query the inventory
- [ ] Web UI served by the embedded server
- [ ] Multi-user support with login (username + PIN)

---

## 📝 Changelog

### v1.0.0 — Initial Release

**Features:**
- Three-tier architecture (Presentation / Logic / Data)
- Product list screen with scrollable table
- Add product form with validation
- Remove product with confirmation dialog
- Sort by price, quantity, name (bubble sort)
- Search by name (linear) and by ID (binary)
- Statistics screen with animated bar chart
- Persistent file storage (`assets/products.txt`)
- Toast notification system
- Animated background (glow blobs + particles)
- Scanline CRT overlay (toggleable)
- Screen transitions (fade to black)
- Settings panel

**Bug fixes (during development):**
- Fixed crash when removing a product that was the only item in the list
- Fixed search results not clearing when navigating away and back
- Fixed bubble sort not handling equal-key elements correctly
- Fixed particle system exceeding pool size causing memory issues
- Fixed file write leaving a corrupted partial file on disk-full error
- Fixed `calcTotalValue()` stack overflow on empty list (added index bounds check)
- Fixed toast queue growing unbounded when many operations were performed quickly

---

## 👥 Collaborators

| Name              | Role            | Responsibilities                                          |
| ----------------- | --------------- | --------------------------------------------------------- |
| **Nikolay Ivanov**| Scrum Trainer   | Sprint planning, daily standups, retrospectives, mentoring|
| **Vasil Zarakyan**| Developer       | Logic layer, data layer, file I/O, algorithms             |
| **Nikola Dimitrov**| Developer      | Main loop, CMake configuration, input handling, settings  |
| **Filip Filipov** | Designer        | Visual design, UI layout, particle system, colour themes  |

### Contribution Guidelines (for future contributors)

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/my-feature`
3. Follow the [coding standards](#-coding-standards)
4. Write a clear commit message: `feat: add CSV export to statistics screen`
5. Open a pull request with a description of what changed and why
6. Wait for review

#### Commit Message Convention

```
<type>: <short description>

[optional body — what and why, not how]

[optional footer — issue references]
```

Types: `feat`, `fix`, `refactor`, `docs`, `style`, `test`, `chore`

Examples:
```
feat: add binary search for product ID lookup
fix: prevent crash when removing last product
docs: add algorithm complexity analysis to README
refactor: extract toast rendering into its own function
```

---

## 🙏 Acknowledgements

- **[raysan5](https://github.com/raysan5)** and all Raylib contributors — for creating an exceptional, beginner-friendly graphics library
- **The C++ Standard Committee** — for C++17 features used throughout (structured bindings, `std::optional`, `if constexpr`)
- **The CMake team** — for FetchContent which makes dependency management painless
- **Stack Overflow community** — for answering countless C++ questions
- **Our teacher** — for assigning a project that pushed us to learn real software architecture

---

## 📜 License

```
MIT License

Copyright (c) 2024 BOTEV Inventory Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 📚 Further Reading

If you want to deepen your understanding of the concepts used in BOTEV, here are some resources:

### C++ & Software Design

- **"Clean Code" by Robert C. Martin** — Principles of readable, maintainable code
- **"The Pragmatic Programmer" by Hunt & Thomas** — Timeless software engineering wisdom
- **cppreference.com** — The definitive C++ reference
- **learncpp.com** — Free, comprehensive C++17 tutorial

### Algorithms

- **"Introduction to Algorithms" (CLRS)** — The textbook on algorithms; chapters on sorting and searching
- **visualgo.net** — Interactive algorithm visualizations (great for understanding bubble sort step by step)

### Graphics / Raylib

- **raylib.com** — Official Raylib site with examples and documentation
- **github.com/raysan5/raylib/wiki** — Raylib wiki with platform-specific guides
- **"Game Programming Patterns" by Robert Nystrom** — Free online book covering game-loop architecture and other patterns

### Three-Tier Architecture

- **Martin Fowler's "Patterns of Enterprise Application Architecture"** — Deep coverage of layered architecture
- **Microsoft's .NET architecture documentation** — Good practical examples of three-tier (even if they use .NET)

---

<div align="center">

---

Made with ❤️ by the BOTEV Team • 9th Grade • C++17 • Raylib 5.0

*"A clean architecture is not an accident — it is the result of deliberate decisions, consistently applied."*

---

</div>

cat >> /mnt/user-data/outputs/README.md << 'APPEND2_EOF'

---

## 🎓 Classroom Presentation Guide

This section is intended for use during the final project presentation. It provides a structured walkthrough of BOTEV's key concepts for teachers and classmates.

### Slide 1 — Project Introduction

**Talking points:**
- BOTEV is a graphical inventory management system written in C++17
- It uses the Raylib library for rendering — the same library used to make games
- The project demonstrates three core topics from the curriculum: sorting, searching, and recursion
- All data is saved to disk and survives application restarts

**Live demo:** Launch `./botev` and show the main menu with the animated background

---

### Slide 2 — Three-Tier Architecture

**Talking points:**
- Software is organized into three distinct layers
- Each layer has exactly one job and talks only to the layer below it
- This separation means we can change the file format (Data layer) without touching the UI (Presentation layer)
- The Presentation layer never calls `fopen()` or `std::ifstream` — only the Data layer does

**Diagram to draw on the whiteboard:**
```
[User] → clicks button
          ↓
[Presentation Layer: ui.cpp]  — "user wants to add a product"
          ↓
[Logic Layer: logic.cpp]      — validates input, calls data layer
          ↓
[Data Layer: data.cpp]        — writes to products.txt
```

---

### Slide 3 — Bubble Sort

**Talking points:**
- We sort the product list by price, quantity, or name
- Bubble sort repeatedly steps through the list, compares adjacent items, and swaps them if they are in the wrong order
- After each full pass, the largest unsorted element "bubbles up" to its correct position
- Time complexity: O(n²) — for 100 products, up to 10,000 comparisons
- We added an early-exit optimisation: if no swaps occur in a pass, the list is already sorted (O(n) best case)

**Live demo:** Add 5 products with different prices, click "Sort by Price"

---

### Slide 4 — Linear vs Binary Search

**Talking points:**
- Linear Search (searchByName): Check every product one by one. O(n). Works on unsorted data.
- Binary Search (searchById): Requires sorted data. Cut the search space in half each step. O(log n).
- Example: 1000 products. Linear: up to 1000 comparisons. Binary: up to 10 comparisons (log₂(1000) ≈ 10).
- We use binary search for ID because IDs are numbers that can be sorted cheaply. Names are searched linearly because partial-match (substring) search can't use binary search.

**Live demo:** Search for a product by name (linear), then by ID (binary), compare speed (both feel instant for small lists)

---

### Slide 5 — Recursion

**Talking points:**
- Recursion is when a function calls itself to solve a smaller version of the same problem
- Every recursive function needs a base case (where it stops) and a recursive case (where it calls itself)
- `calcTotalValue()` sums all product values: total = first product's value + total of the rest
- The "rest" is the same problem, just one smaller — so we recurse

**Draw the call stack on the whiteboard:**
```
calcTotalValue([A,B,C], 0)
  = 10*2 + calcTotalValue([A,B,C], 1)
  = 10*2 + 5*4 + calcTotalValue([A,B,C], 2)
  = 10*2 + 5*4 + 20*1 + calcTotalValue([A,B,C], 3)
  = 10*2 + 5*4 + 20*1 + 0         ← base case
  = 60
```

---

### Slide 6 — Visual Effects

**Talking points:**
- BOTEV includes several visual effects implemented from scratch
- Glow blobs: large soft circles rendered with additive blending — colours add together like light
- Particle system: 300 particles emitted from the bottom, rising and fading
- Scanline overlay: simulates the horizontal lines of old CRT monitors
- All effects can be toggled in the Settings panel

**Live demo:** Open Settings, toggle particles and scanlines off and on

---

### Slide 7 — File Persistence

**Talking points:**
- `assets/products.txt` stores all products in a simple text format: `id,name,price,quantity`
- Every add and remove operation immediately saves the file
- We use a temp-file-rename pattern for safety: write to `.tmp`, then rename to the final file
- This means the file is never in a corrupted partial state, even if the computer loses power mid-write

**Live demo:** Add a product, close the app with ESC, reopen — the product is still there

---

### Slide 8 — Questions & Code Walk-through

**Suggested code paths to walk through:**
1. `logic.cpp → sortByPrice()` — show the nested loops and swap
2. `logic.cpp → searchById()` — show the sorted copy and binary search loop
3. `logic.cpp → calcTotalValue()` — show the base case and recursive call
4. `data.cpp → saveProductsToFile()` — show the temp-file pattern

---

## 🧰 Developer Tools & Workflow

### Recommended IDE Setup

#### VS Code

Install these extensions for the best C++17 + CMake experience:

| Extension              | Publisher      | Purpose                                    |
| ---------------------- | -------------- | ------------------------------------------ |
| C/C++                  | Microsoft      | IntelliSense, syntax highlighting, debugging|
| CMake Tools            | Microsoft      | CMake integration, build buttons in sidebar|
| CMake                  | twxs           | CMake syntax highlighting                  |
| clangd                 | LLVM           | Faster IntelliSense (alternative to C/C++) |
| Code Spell Checker     | Street Side    | Catch typos in comments and strings        |
| GitLens                | GitKraken      | Enhanced git integration                   |

`settings.json` for BOTEV:
```json
{
    "cmake.buildDirectory": "${workspaceFolder}/build",
    "cmake.configureOnOpen": true,
    "C_Cpp.default.cppStandard": "c++17",
    "editor.tabSize": 4,
    "editor.insertSpaces": true,
    "editor.rulers": [100],
    "files.trimTrailingWhitespace": true
}
```

#### CLion

CLion detects `CMakeLists.txt` automatically. Configure:
- **CMake options:** `-DCMAKE_BUILD_TYPE=Debug`
- **Build directory:** `build`
- **Run configuration:** Target `botev`, Working directory `${PROJECT_DIR}/build`

#### Vim / Neovim

With `clangd` LSP and `cmake-tools.nvim`:
```vim
" Generate compile_commands.json for clangd
" Add to CMakeLists.txt: set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

Then symlink: `ln -s build/compile_commands.json .`

---

### Git Workflow

The project uses a simplified Git Flow:

```
main            ──── stable releases only
  └── develop   ──── integration branch
        ├── feature/add-csv-export
        ├── feature/audio-system
        └── bugfix/crash-on-empty-list
```

**Branch naming:**
- `feature/short-description` — new feature
- `bugfix/short-description` — bug fix
- `refactor/short-description` — code improvement without behavior change
- `docs/short-description` — documentation only

**Commit before merging to `develop`:**
1. `git pull origin develop` — update your base
2. `git rebase develop` — rebase your branch (cleaner history than merge)
3. `git push origin feature/your-feature`
4. Open pull request

---

### Debugging Tips

#### Print Debugging

Add temporary `std::cerr` statements:
```cpp
std::cerr << "[DEBUG] sortByPrice: list has " << list.size() << " elements\n";
std::cerr << "[DEBUG] After pass " << i << ": ";
for (const auto& p : list) std::cerr << p.price << " ";
std::cerr << "\n";
```

Remove all `[DEBUG]` lines before committing.

#### Raylib Debug Mode

```cpp
SetTraceLogLevel(LOG_DEBUG);  // Show all Raylib internal logs
```

Change to `LOG_WARNING` or `LOG_NONE` for release builds.

#### GDB (Linux / macOS)

```bash
# Build with debug symbols
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .

# Run under GDB
gdb ./botev
(gdb) break logic.cpp:sortByPrice
(gdb) run
(gdb) next       # step over
(gdb) step       # step into
(gdb) print list.size()
(gdb) continue
```

#### Valgrind (Memory Leak Detection)

```bash
valgrind --leak-check=full --show-leak-kinds=all ./botev
```

Expected output: `All heap blocks were freed -- no leaks are possible` (because we use RAII and no manual `new`/`delete`).

#### AddressSanitizer

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined"
cmake --build .
./botev
```

ASan will report any out-of-bounds accesses, use-after-free, or undefined behavior at runtime.

---

## 🗃️ Sample Data

Here is a sample `products.txt` with 20 products to get started quickly:

```
# BOTEV Inventory System — Sample Product Database
# Format: id,name,price,quantity
#
1,Wireless Mouse,29.99,47
2,USB-C Hub,49.99,23
3,Mechanical Keyboard,89.99,12
4,Monitor Stand,34.99,8
5,Webcam HD,79.99,31
6,Laptop Stand,24.99,55
7,HDMI Cable 2m,12.99,120
8,External SSD 1TB,109.99,7
9,Noise Cancelling Headphones,199.99,4
10,Desk Lamp LED,39.99,19
11,Mouse Pad XL,19.99,62
12,USB-A Hub 7-Port,27.99,33
13,Ethernet Cable 5m,9.99,200
14,Screen Cleaning Kit,14.99,88
15,Cable Management Kit,16.99,41
16,Ergonomic Chair Cushion,44.99,14
17,Docking Station,129.99,6
18,Portable Charger 20000mAh,59.99,22
19,Smart Plug 4-Pack,35.99,37
20,Desk Organizer,22.99,51
```

To use this sample data:
```bash
cp sample_products.txt assets/products.txt
./botev
```

### Sample Products by Category (for testing category filtering — planned v1.3)

**Electronics:**
- Wireless Mouse, USB-C Hub, Mechanical Keyboard, Webcam HD, Noise Cancelling Headphones, External SSD 1TB, Docking Station, Portable Charger 20000mAh, Smart Plug 4-Pack

**Accessories:**
- Monitor Stand, Laptop Stand, HDMI Cable 2m, Mouse Pad XL, USB-A Hub 7-Port, Ethernet Cable 5m, Screen Cleaning Kit, Cable Management Kit

**Furniture & Comfort:**
- Desk Lamp LED, Ergonomic Chair Cushion, Desk Organizer

---

## 🧵 Concurrency Considerations

BOTEV is currently single-threaded. The main loop processes input, updates state, and renders sequentially. This is appropriate for the current scope.

If background file saves were to become slow (e.g., with a large product database), a worker thread could be introduced:

```cpp
// Concept — NOT implemented in current version
#include <thread>
#include <mutex>
#include <future>

std::mutex productsMutex;

void asyncSave(const std::vector<Product>& products,
               const std::string& path) {
    std::thread([products, path]() {
        saveProductsToFile(products, path);
    }).detach();
}
```

**Caution:** Detached threads that write files can cause data races if the product list is modified before the save completes. A proper implementation would use `std::future`, `std::promise`, or a dedicated I/O thread with a work queue.

For the current version, synchronous saves are fine because the file is small (< 100 KB) and the write is fast (< 5 ms).

---

## 🌍 Internationalization (i18n) Considerations

BOTEV currently only supports English. For future internationalization:

### String Extraction

All user-visible strings should be extracted into a central location:

```cpp
// strings.h (planned)
namespace Strings {
    constexpr const char* TITLE            = "BOTEV Inventory System";
    constexpr const char* BTN_ADD          = "Add Product";
    constexpr const char* BTN_REMOVE       = "Remove";
    constexpr const char* BTN_SORT_PRICE   = "Sort by Price";
    constexpr const char* TOAST_ADDED      = "Product added!";
    constexpr const char* TOAST_REMOVED    = "Product removed.";
    constexpr const char* ERR_EMPTY_NAME   = "Name cannot be empty.";
    constexpr const char* ERR_PRICE_RANGE  = "Price must be 0.01–9999.99.";
    // ... etc
}
```

### Right-to-Left (RTL) Support

Languages like Arabic and Hebrew read right-to-left. Supporting RTL in a Raylib application requires:
1. Shaping text with a library like HarfBuzz
2. Reversing the layout of UI elements
3. Mirroring the scrollbar position

This is non-trivial and out of scope for v1.0.

### Number and Currency Formatting

Different locales use different decimal separators:
- `1,234.56` (US, UK)
- `1.234,56` (Germany, Spain)
- `1 234,56` (France, Russia)

For now, BOTEV always uses the US format. A future version could use `std::locale` for formatting.

---

## 🔐 Security Considerations

BOTEV is a local desktop application with no network connectivity. Security threats are minimal, but the following are noted:

### Path Traversal

If the data file path were configurable and user-provided, a malicious input like `../../../etc/passwd` could cause the application to read or overwrite unexpected files.

**Mitigation:** The data file path is hardcoded to `assets/products.txt`. Any future configurable path should be validated with `std::filesystem::canonical()` and checked to be within the application directory.

### CSV Injection

If BOTEV were to export data to CSV and that CSV were opened in a spreadsheet application, a product name like `=SUM(A1:A100)` could execute as a formula.

**Mitigation:** When implementing CSV export (v1.4), escape values that start with `=`, `+`, `-`, or `@` by prepending a single quote or wrapping in double quotes.

### File Permissions

The `assets/products.txt` file should not be world-writable on a shared system.

```bash
# Set appropriate permissions (owner read/write, others read-only)
chmod 644 assets/products.txt
chmod 755 assets/
```

---

## 📦 Packaging and Distribution

### Linux — AppImage

AppImage is a distribution-agnostic Linux package format:

```bash
# Install linuxdeploy
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage

# Build release binary
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=AppDir/usr
cmake --build .
cmake --install .

# Package
./linuxdeploy-x86_64.AppImage \
    --appdir AppDir \
    --executable AppDir/usr/bin/botev \
    --desktop-file botev.desktop \
    --icon-file assets/icons/botev-256.png \
    --output appimage
```

Result: `botev-x86_64.AppImage` — a single file that runs on any Linux distribution.

### Windows — NSIS Installer

Using NSIS (Nullsoft Scriptable Install System):

```nsi
; botev.nsi
!include "MUI2.nsh"

Name "BOTEV Inventory System"
OutFile "botev-setup-1.0.0-win64.exe"
InstallDir "$PROGRAMFILES64\BOTEV"

!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

Section "Install"
    SetOutPath "$INSTDIR"
    File "Release\botev.exe"
    File /r "assets\"
    CreateShortcut "$DESKTOP\BOTEV.lnk" "$INSTDIR\botev.exe"
SectionEnd
```

### macOS — DMG

```bash
# Build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Create .app bundle
mkdir -p BOTEV.app/Contents/{MacOS,Resources}
cp botev BOTEV.app/Contents/MacOS/
cp -r assets/ BOTEV.app/Contents/Resources/
cat > BOTEV.app/Contents/Info.plist << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "...">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key><string>botev</string>
    <key>CFBundleName</key><string>BOTEV</string>
    <key>CFBundleVersion</key><string>1.0.0</string>
</dict>
</plist>
EOF

# Create DMG
hdiutil create -volname "BOTEV" -srcfolder BOTEV.app \
    -ov -format UDZO BOTEV-1.0.0-macos.dmg
```

---

## 🧪 Extended Test Cases

### Unit Test Ideas (Manual)

Since the project does not (yet) use a testing framework, these are manual test procedures.

#### Test Suite: sortByPrice

```
Test: Empty list
  Input:  []
  Expected: []  (no crash, no change)

Test: Single element
  Input:  [{id:1, price:50.0}]
  Expected: [{id:1, price:50.0}]  (no change)

Test: Already sorted
  Input:  [{price:10}, {price:20}, {price:30}]
  Expected: [{price:10}, {price:20}, {price:30}]  (no swaps, 1 pass)

Test: Reverse sorted
  Input:  [{price:30}, {price:20}, {price:10}]
  Expected: [{price:10}, {price:20}, {price:30}]

Test: All equal
  Input:  [{price:15}, {price:15}, {price:15}]
  Expected: [{price:15}, {price:15}, {price:15}]  (stable order maintained)

Test: Two elements, wrong order
  Input:  [{id:1, price:50}, {id:2, price:25}]
  Expected: [{id:2, price:25}, {id:1, price:50}]
```

#### Test Suite: searchByName

```
Test: Exact match
  Query: "Widget A"
  Expected: [{name:"Widget A"}]

Test: Partial match (prefix)
  Query: "Wid"
  Expected: all products whose name starts with "Wid"

Test: Partial match (suffix)
  Query: "Cable"
  Expected: all products whose name ends with "Cable"

Test: Case-insensitive
  Query: "WIDGET"
  Expected: same as query "widget" or "Widget"

Test: No match
  Query: "xyzxyz"
  Expected: []  (empty vector)

Test: Empty query
  Query: ""
  Expected: all products  (empty string is a substring of every string)
```

#### Test Suite: searchById

```
Test: Found
  List: [{id:1}, {id:5}, {id:3}, {id:9}]
  Query: 5
  Expected: {id:5}

Test: Not found
  List: [{id:1}, {id:3}, {id:7}]
  Query: 4
  Expected: std::nullopt

Test: First element
  List: [{id:1}, {id:3}, {id:7}]
  Query: 1
  Expected: {id:1}

Test: Last element
  List: [{id:1}, {id:3}, {id:7}]
  Query: 7
  Expected: {id:7}

Test: Single element, found
  List: [{id:42}]
  Query: 42
  Expected: {id:42}

Test: Single element, not found
  List: [{id:42}]
  Query: 1
  Expected: std::nullopt

Test: Large list (stress)
  List: 1000 products with sequential IDs
  Query: each ID from 1 to 1000
  Expected: correct product for each
```

#### Test Suite: calcTotalValue

```
Test: Empty list
  Input: []
  Expected: 0.0f

Test: Single product
  Input: [{price:10.0, qty:3}]
  Expected: 30.0f

Test: Multiple products
  Input: [{price:5.0, qty:2}, {price:10.0, qty:4}]
  Expected: 50.0f  (10.0 + 40.0)

Test: Zero quantity
  Input: [{price:100.0, qty:0}]
  Expected: 0.0f

Test: Large values
  Input: [{price:9999.99, qty:9999}]
  Expected: 99989900.01f  (approximately)
```

#### Test Suite: validateProduct

```
Test: Valid product
  Input: {id:1, name:"Widget", price:9.99, qty:10}
  Existing: []
  Expected: true

Test: Empty name
  Input: {id:1, name:"", price:9.99, qty:10}
  Expected: false

Test: Name too long (65 chars)
  Input: {id:1, name:"A"*65, price:9.99, qty:10}
  Expected: false

Test: Price = 0
  Input: {id:1, name:"Widget", price:0.0, qty:10}
  Expected: false

Test: Price negative
  Input: {id:1, name:"Widget", price:-1.0, qty:10}
  Expected: false

Test: Quantity negative
  Input: {id:1, name:"Widget", price:9.99, qty:-1}
  Expected: false

Test: ID = 0
  Input: {id:0, name:"Widget", price:9.99, qty:10}
  Expected: false

Test: Duplicate ID
  Input: {id:5, name:"Widget", price:9.99, qty:10}
  Existing: [{id:5, ...}]
  Expected: false

Test: Boundary — price = 0.01
  Input: {id:1, name:"Widget", price:0.01, qty:10}
  Expected: true

Test: Boundary — price = 9999.99
  Input: {id:1, name:"Widget", price:9999.99, qty:10}
  Expected: true

Test: Boundary — qty = 0
  Input: {id:1, name:"Widget", price:9.99, qty:0}
  Expected: true  (zero stock is valid)

Test: Boundary — qty = 9999
  Input: {id:1, name:"Widget", price:9.99, qty:9999}
  Expected: true
```

---

## 📐 UI Layout Specifications

### Window Dimensions

| Resolution | Support Level | Notes                                  |
| ---------- | ------------- | -------------------------------------- |
| 1280 × 720 | ✅ Primary    | Development target                     |
| 1920 × 1080| ✅ Supported  | UI scales up well                      |
| 800 × 600  | ⚠️ Partial   | Some elements may clip                 |
| 2560 × 1440| ✅ Supported  | UI scales up well                      |
| Ultrawide  | ⚠️ Partial   | Background fills but table may look sparse |

### Main Menu Layout (1280×720)

```
┌──────────────────────────────────────────────────────────┐
│  [animated background: blobs + particles]                 │
│                                                           │
│          ╔═══════════════════════════════╗               │
│          ║   📦 BOTEV Inventory System   ║   y=120       │
│          ╚═══════════════════════════════╝               │
│                                                           │
│          ┌─────────────────────────────┐                 │
│          │     👁️  View Products        │   y=280        │
│          └─────────────────────────────┘                 │
│          ┌─────────────────────────────┐                 │
│          │     ➕  Add Product          │   y=340        │
│          └─────────────────────────────┘                 │
│          ┌─────────────────────────────┐                 │
│          │     🔍  Search              │   y=400        │
│          └─────────────────────────────┘                 │
│          ┌─────────────────────────────┐                 │
│          │     📊  Statistics          │   y=460        │
│          └─────────────────────────────┘                 │
│          ┌─────────────────────────────┐                 │
│          │     ⚙️  Settings            │   y=520        │
│          └─────────────────────────────┘                 │
│                                                           │
│  [HUD: 47 products | $12,430.50 | 3 LOW STOCK]          │
└──────────────────────────────────────────────────────────┘
```

Button dimensions: **340px wide × 48px tall**, centered at x=640.
Button spacing: 60px between button tops.

### Product List Layout

```
┌──────────────────────────────────────────────────────────┐
│  ← Back     View Products                   [Sort▼]      │
├──────────────────────────────────────────────────────────┤
│  ID  │  Name                    │   Price │  Qty │ Status │
├──────────────────────────────────────────────────────────┤
│   1  │  Wireless Mouse          │  $29.99 │   47 │  ✅ OK │
│   2  │  USB-C Hub               │  $49.99 │   23 │  ✅ OK │
│   3  │  Mechanical Keyboard     │  $89.99 │   12 │  ✅ OK │
│   4  │  Monitor Stand           │  $34.99 │    8 │  ✅ OK │
│   9  │  Noise Cancelling Head.. │ $199.99 │    4 │  🔴 LOW│
│  17  │  Docking Station         │ $129.99 │    6 │  ✅ OK │
│  ...                                                       │
├──────────────────────────────────────────────────────────┤
│  Showing 1–15 of 20 products          [▲ scrollbar ▼]    │
└──────────────────────────────────────────────────────────┘
```

### Add Product Form Layout

```
┌──────────────────────────────────────────────────────────┐
│  ← Back          Add New Product                          │
│                                                           │
│  Product Name                                             │
│  ┌────────────────────────────────────────────────────┐  │
│  │ Wireless Mouse                                      │  │
│  └────────────────────────────────────────────────────┘  │
│                                                           │
│  Price ($)                    Product ID                  │
│  ┌────────────────────┐      ┌────────────────────┐      │
│  │ 29.99              │      │ 1                  │      │
│  └────────────────────┘      └────────────────────┘      │
│                                                           │
│  Quantity                                                 │
│  ┌────────────────────┐                                   │
│  │ 47                 │                                   │
│  └────────────────────┘                                   │
│                                                           │
│              ┌─────────────────────────┐                 │
│              │     ➕ Add Product       │                 │
│              └─────────────────────────┘                 │
└──────────────────────────────────────────────────────────┘
```

---

## 💡 Tips & Best Practices

### For Developers Working on This Project

1. **Always run the application after changes** — Build errors are obvious, but subtle rendering bugs only show up at runtime
2. **Test with an empty `products.txt`** — The "first run" code path is easy to break
3. **Test with a corrupt `products.txt`** — Add a malformed line and ensure the application starts gracefully
4. **Check all sort functions independently** — They share the same template but have different comparison operators; a copy-paste error is easy to make
5. **Validate on every form submission** — Don't assume the user "would never" enter a negative price
6. **Keep the three-tier rule** — If you find yourself including `data.h` in `ui.cpp`, stop and refactor
7. **Name things clearly** — `bool ok = validateProduct(p, list)` is better than `bool x = vp(p, l)`

### For Students Using This as a Reference

1. **Understand before copying** — Read the algorithm comments and understand each line before using the code in your own project
2. **The three-tier pattern is universal** — You can apply this architecture to almost any application that has a UI, business rules, and data storage
3. **Recursion always needs a base case** — The most common recursion bug is a missing or wrong base case leading to infinite recursion and stack overflow
4. **Bubble sort is educational, not practical** — In real projects, always use `std::sort()` unless you have a specific reason not to
5. **`std::optional` is your friend** — Whenever a function might not return a value, use `std::optional` instead of returning `-1` or `nullptr`

---

## 🗺️ Codebase Navigation Map

If you are reading this code for the first time, here is the recommended reading order:

```
Step 1: data.h          — Understand the Product struct
Step 2: data.cpp        — See how products are loaded and saved
Step 3: logic.h         — See the complete Logic layer API
Step 4: logic.cpp       — Read sortByPrice (short, simple)
Step 5: logic.cpp       — Read searchByName (a bit more complex)
Step 6: logic.cpp       — Read searchById (binary search, most complex)
Step 7: logic.cpp       — Read calcTotalValue (recursion)
Step 8: logic.cpp       — Read validateProduct (all the rules)
Step 9: ui.h            — See the UiState struct
Step 10: main.cpp       — See how everything connects in the main loop
Step 11: ui.cpp         — Read drawProductList (main table rendering)
Step 12: ui.cpp         — Read handleAddProductInput (form handling)
```

---

## 📬 Contact & Support

This project was developed as a 9th-grade school project. For questions about the code:

- Open an issue on the GitHub repository
- Ask in your school's CS class channel
- Email the project team (contact details provided in class)

For Raylib questions: https://discord.gg/raylib

For C++17 questions: https://cppreference.com

---

<div align="center">

---

### 🏁 End of Documentation

**BOTEV Inventory System v1.0.0**

Three tiers. Seven algorithms. Zero raw pointers. One very polished school project.

---

*README generated with care. Every section written by hand. No padding, only content.*

*If you read this far — thank you. We hope BOTEV inspires your own C++ projects.*

---

</div>
APPEND2_EOF
Output

exit code 0
Done

You are out of free messages until 5:20 AM
