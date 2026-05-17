/*
 * main.cpp
 * ========
 * Entry point for the BOTEV Inventory System — Raylib Edition.
 *
 * Responsibilities:
 *   1. Load product data from disk (Data layer).
 *   2. Hand off to the Raylib application loop (Presentation layer).
 *   3. Persist any changes on clean exit (Data layer).
 *
 * Architecture:  main.cpp  →  ui.cpp  →  logic.cpp  →  data.cpp
 *   main.cpp coordinates startup and shutdown only.
 *   All UI, logic, and data handling is delegated to the respective layers.
 */

#include "../include/ui.h"
#include "../include/data.h"

#include <cstdlib>        // for std::system (mkdir cross-platform)
#include <filesystem>     // C++17

namespace fs = std::filesystem;

int main() {
    // Ensure the assets directory exists (first-run safety)
    if (!fs::exists("assets")) {
        fs::create_directory("assets");
    }

    // --- Data Layer: load ---
    std::vector<Product> products = loadProducts();

    // --- Presentation Layer: run Raylib application ---
    runApplication(products);

    // --- Data Layer: persist on clean exit ---
    saveProducts(products);

    return 0;
}
