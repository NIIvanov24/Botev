# 📦 BOTEV Inventory System — Raylib Edition

> A 9th-grade C++ inventory management system, redesigned with a modern
> dark cyberpunk visual style using the **Raylib** graphics library.

---

## ✨ Visual Features

| Feature | Details |
|---------|---------|
| 🌌 Animated background | Floating glow blobs, grid, 120 live particles |
| 🎞 Scanline overlay | CRT-style post-processing, toggleable in Settings |
| 🔀 Screen transitions | Smooth fade-to-black between all screens |
| 🔘 Animated buttons | Hover glow, colour lerp, border pulse |
| 🔔 Toast notifications | Slide-in corner toasts for add / remove events |
| 📊 Bar chart | Animated product-value chart in Statistics |
| 📋 Scrollable table | Mouse-wheel + arrow-key scroll with smooth lerp |
| 🕐 Live HUD | Product count, total value, low-stock badge, clock |
| ⚙️ Settings panel | Slider controls for volume, particle & scanline toggles |

---

## 🏗️ Architecture (Three-Tier)

```
┌──────────────────────────┐
│   Presentation Layer     │  src/ui.cpp  +  include/ui.h
│  Raylib windows & input  │  Calls Logic layer only
└────────────┬─────────────┘
             │ calls
┌────────────▼─────────────┐
│      Logic Layer         │  src/logic.cpp  +  include/logic.h
│  Algorithms & validation │  Sorting, searching, recursion, stats
└────────────┬─────────────┘
             │ calls
┌────────────▼─────────────┐
│      Data Layer          │  src/data.cpp  +  include/data.h
│  File I/O & structs      │  Read/write products.txt, Product struct
└──────────────────────────┘
```

> The Presentation layer **never** calls the Data layer directly.

---

## 📁 Project Structure

```
inventory_raylib/
├── src/
│   ├── main.cpp          # Entry point: load → run → save
│   ├── data.cpp          # Data layer: file I/O, CRUD helpers
│   ├── logic.cpp         # Logic layer: algorithms, stats, validation
│   └── ui.cpp            # Presentation layer: full Raylib GUI
├── include/
│   ├── data.h            # Product struct, constants, I/O prototypes
│   ├── logic.h           # Algorithm & stats prototypes
│   └── ui.h              # AppState, Screen enum, colour palette
├── assets/
│   └── products.txt      # Pipe-delimited persistent data
├── docs/                 # Architecture diagrams, sprint reports
├── shaders/              # (Reserved for future GLSL shaders)
├── CMakeLists.txt        # Build config with Raylib auto-fetch
└── README.md
```

---

## 🔨 Building

### Requirements
- C++17 compiler: `g++`, `clang++`, or MSVC 2019+
- CMake 3.16+
- Raylib 5.0 (auto-downloaded by CMake if not installed)

### Linux / macOS
```bash
# Option A: install Raylib system-wide first (faster builds)
sudo apt install libraylib-dev   # Ubuntu/Debian
brew install raylib              # macOS

# Then build:
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
./botev
```

### Windows (with MSVC / Visual Studio)
```powershell
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
.\Release\botev.exe
```

> CMake's `FetchContent` will automatically download and compile Raylib 5.0
> if it is not found on your system. First build takes ~2 minutes.

---

## 🎮 Controls

| Key / Action | Effect |
|-------------|--------|
| Mouse click | Navigate menus, activate form fields |
| Mouse drag | Sliders in Settings |
| ↑ / ↓ Arrow | Scroll product table |
| Tab | Switch between form fields |
| Backspace | Delete last character |
| Enter | Submit search |
| ESC / ✕ | Quit application |

---

## 🧮 Algorithms Implemented

| Category | Algorithm | Where |
|----------|-----------|-------|
| 🔃 Sort | Bubble Sort (price)    | `logic.cpp → sortByPrice()` |
| 🔃 Sort | Bubble Sort (quantity) | `logic.cpp → sortByQuantity()` |
| 🔃 Sort | Bubble Sort (name)     | `logic.cpp → sortByName()` |
| 🔍 Search | Linear Search (name)  | `logic.cpp → searchByName()` |
| 🔍 Search | Binary Search (ID)    | `logic.cpp → searchById()` |
| ♾️ Recursion | Total value        | `logic.cpp → calcTotalValue()` |
| ♾️ Recursion | Low-stock count    | `logic.cpp → countLowStock()` |

---

## 📊 Statistics Panel

The Statistics screen displays:
- **Total products** count
- **Total inventory value** (recursive sum of price × quantity)
- **Low-stock count** (items with quantity < 5)
- **Average price** across all products
- **Most expensive** product name
- **Animated bar chart** of value-per-product (top 10, entrance animation)

---

## 🛣️ Roadmap / Planned Features

- [ ] GLSL shader post-processing (bloom, chromatic aberration)
- [ ] Sound effects & background music via `raylib` audio API
- [ ] Achievement system (first product, 100 items, etc.)
- [ ] Export to CSV / PDF report
- [ ] Multi-sort (primary + secondary key)
- [ ] Category filter in View Products
- [ ] Edit product in-place

---

## 👥 Team Roles

| Role | Responsibility |
|------|---------------|
| 🗂️ Scrum Master | Sprint planning, GitHub Projects/Kanban, docs |
| 🧠 Back-End Dev 1 | Logic layer: sorting & searching algorithms |
| 💽 Back-End Dev 2 | Data layer: file I/O, data structures |
| 🎨 Front-End Dev | Presentation layer: Raylib GUI, visual effects |

---

## 📜 Coding Standards

- **Naming**: `camelCase` for functions/variables, `PascalCase` for types/enums.
- **Headers**: `#pragma once`, separated by layer.
- **Comments**: Every function has a doc-comment; complex blocks have inline notes.
- **Error handling**: All user input is validated before reaching the data layer.
- **No raw memory**: `std::vector`, `std::string` — no manual `new`/`delete`.
- **Const correctness**: Read-only parameters passed as `const&`.
