# 📦 BOTEV Inventory System — Raylib Edition

<div class="readme">
  <h1>📦 Inventory Management System</h1>
  <p class="tagline">
    A C++ Raylib-based inventory management system built with a clean three-tier architecture.
  </p>

  <div class="badges">
    <span class="badge blue">🛠️ C++17</span>
    <span class="badge green">📐 CMake 3.16+</span>
    <span class="badge amber">🏗️ Three-Tier Architecture</span>
    <span class="badge">🎓 9th Grade Project</span>
    <span class="badge">💾 File Persistence</span>
    <span class="badge">🎮 Raylib GUI</span>
  </div>

---

## ✨ Visual Features

| Feature                | Details                                           |
| ---------------------- | ------------------------------------------------- |
| 🌌 Animated background | Floating glow blobs, grid, live particles         |
| 🎞 Scanline overlay    | CRT-style post-processing, toggleable in Settings |
| 🔀 Screen transitions  | Smooth fade-to-black between screens              |
| 🔘 Animated buttons    | Hover glow, colour lerp, border pulse             |
| 🔔 Toast notifications | Slide-in corner toasts for add/remove events      |
| 📊 Bar chart           | Animated product-value chart in Statistics        |
| 📋 Scrollable table    | Mouse-wheel + arrow-key scrolling                 |
| 🕐 Live HUD            | Product count, total value, low-stock badge       |
| ⚙️ Settings panel      | Volume slider, particle & scanline toggles        |

---

## 🏗️ Architecture (Three-Tier)

```text
┌──────────────────────────┐
│   Presentation Layer     │
│  Raylib windows & input  │
└────────────┬─────────────┘
             │ calls
┌────────────▼─────────────┐
│      Logic Layer         │
│ Algorithms & validation  │
└────────────┬─────────────┘
             │ calls
┌────────────▼─────────────┐
│       Data Layer         │
│  File I/O & structures   │
└──────────────────────────┘
```

> The Presentation layer never communicates directly with the Data layer.

---

## 📁 Project Structure

```text
inventory_raylib/
├── src/
│   ├── main.cpp
│   ├── data.cpp
│   ├── logic.cpp
│   └── ui.cpp
├── include/
│   ├── data.h
│   ├── logic.h
│   └── ui.h
├── assets/
│   └── products.txt
├── docs/
├── shaders/
├── CMakeLists.txt
└── README.md
```

---

## ✨ Features

* 👁️ View products in a formatted table
* ➕ Add products with validation
* 🗑️ Remove products by ID
* 🔃 Sort by price, quantity, or name
* 🔍 Search products by name
* 📊 Statistics and inventory analytics
* 💾 Persistent file storage
* 🎮 Full Raylib graphical interface

---

## 🧮 Algorithms Implemented

| Category     | Algorithm              | Function           |
| ------------ | ---------------------- | ------------------ |
| 🔃 Sort      | Bubble Sort (price)    | `sortByPrice()`    |
| 🔃 Sort      | Bubble Sort (quantity) | `sortByQuantity()` |
| 🔃 Sort      | Bubble Sort (name)     | `sortByName()`     |
| 🔍 Search    | Linear Search          | `searchByName()`   |
| 🔍 Search    | Binary Search          | `searchById()`     |
| ♾️ Recursion | Total inventory value  | `calcTotalValue()` |
| ♾️ Recursion | Low-stock count        | `countLowStock()`  |

---

## 📊 Statistics Panel

The statistics screen displays:

* Total products count
* Total inventory value
* Low-stock products
* Average product price
* Most expensive product
* Animated value-per-product chart

---

## 🔨 Building

### Requirements

* C++17 compiler
* CMake 3.16+
* Raylib 5.0

### Linux / macOS

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
./botev
```

### Windows

```powershell
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
.\Release\botev.exe
```

---

## 🎮 Controls

| Key / Action | Effect             |
| ------------ | ------------------ |
| Mouse click  | Navigate menus     |
| Mouse drag   | Move sliders       |
| ↑ / ↓ Arrow  | Scroll table       |
| Tab          | Switch form fields |
| Backspace    | Delete character   |
| Enter        | Submit search      |
| ESC          | Exit application   |

---

## 🛣️ Planned Features

* [ ] GLSL shader effects
* [ ] Background music & sound effects
* [ ] Achievement system
* [ ] CSV / PDF export
* [ ] Multi-sort system
* [ ] Category filtering
* [ ] In-place product editing

---

## 👥 Collaborators

| Name            | Role          |
| --------------- | ------------- |
| Nikolay Ivanov  | Scrum Trainer |
| Vasil Zarakyan  | Developer     |
| Nikola Dimitrov | Developer     |
| Filip Filipov   | Designer      |

---

## 📜 Coding Standards

* camelCase for variables and functions
* PascalCase for types and enums
* `#pragma once` in headers
* Input validation before data processing
* STL containers instead of raw pointers
* Const correctness where applicable
