# Inventory Management System

A C++ console application (with planned Dear ImGui GUI) for managing a product inventory.
Built as a 9th-grade C++ project following a three-tier architecture.

---

## Team Roles

| Role | Responsibility |
|------|---------------|
| Scrum Master | Sprint planning, GitHub Projects/Kanban, documentation |
| Back-End Developer 1 | Logic layer: sorting & searching algorithms |
| Back-End Developer 2 | Data layer: file I/O, data structures |
| Front-End Developer | Presentation layer: ImGui GUI integration |

---

## Features

- **View** all products in a formatted table
- **Add** new products with validation
- **Remove** products by ID
- **Sort** by price, quantity, or name (Bubble Sort)
- **Search** by name (Linear Search, case-insensitive)
- **Statistics**: total inventory value (recursive), low-stock count (recursive)
- **Persistent storage** — data saved to `assets/products.txt`

---

## Architecture

Three-Tier Architecture:

```
┌─────────────────────────┐
│   Presentation Layer    │  presentation.h / presentation.cpp
│  (UI / ImGui windows)   │  User input & display only
└────────────┬────────────┘
             │ calls
┌────────────▼────────────┐
│      Logic Layer        │  logic.h / logic.cpp
│  (Algorithms & Rules)   │  Sorting, searching, recursion, validation
└────────────┬────────────┘
             │ calls
┌────────────▼────────────┐
│      Data Layer         │  data.h / data.cpp
│  (File I/O & Structs)   │  Read/write products.txt, Product struct
└─────────────────────────┘
```

> The Presentation layer **never** accesses the Data layer directly.

---

## Project Structure

```
inventory_project/
├── src/
│   ├── main.cpp           # Entry point
│   ├── data.cpp           # Data layer implementation
│   ├── logic.cpp          # Logic layer implementation
│   └── presentation.cpp   # Presentation layer implementation
├── include/
│   ├── data.h             # Data structs & prototypes
│   ├── logic.h            # Algorithm prototypes
│   └── presentation.h     # UI function prototypes
├── assets/
│   └── products.txt       # Persistent data file
├── docs/                  # Architecture diagrams, sprint reports
├── tests/                 # Unit tests
├── CMakeLists.txt
└── README.md
```

---

## How to Build & Run

### Requirements
- C++17 compiler (g++, clang++, MSVC)
- CMake 3.16+

### Build with CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
./inventory
```

### Build manually (g++)
```bash
g++ -std=c++17 -Iinclude src/main.cpp src/data.cpp src/logic.cpp src/presentation.cpp -o inventory
./inventory
```

---

## Algorithms Implemented

| Category | Algorithm | Location |
|----------|-----------|----------|
| Sort | Bubble Sort (price) | `logic.cpp` → `sortByPrice()` |
| Sort | Bubble Sort (quantity) | `logic.cpp` → `sortByQuantity()` |
| Sort | Bubble Sort (name) | `logic.cpp` → `sortByName()` |
| Search | Linear Search | `logic.cpp` → `searchByName()` |
| Search | Binary Search | `logic.cpp` → `searchById()` |
| Recursion | Total value | `logic.cpp` → `calcTotalValue()` |
| Recursion | Low-stock count | `logic.cpp` → `countLowStock()` |

---

## Sprint Plan

See `docs/` for sprint reports.  
GitHub Project Kanban board tracks: **To Do → In Progress → Review → Done**

---

## ImGui Integration (Planned)

The `presentation.cpp` functions are designed as 1-to-1 replacements with ImGui windows:

| Console function | ImGui equivalent |
|-----------------|-----------------|
| `renderProductTable()` | `ImGui::BeginTable` / `ImGui::TableNextRow` |
| `showMainMenu()` | `ImGui::BeginMainMenuBar` |
| `showAddProductForm()` | `ImGui::InputText`, `ImGui::InputDouble` |
| `showSortMenu()` | `ImGui::BeginCombo` |
| `showStatistics()` | `ImGui::Text` in a stats panel |

See `CMakeLists.txt` for the commented-out ImGui build instructions.
