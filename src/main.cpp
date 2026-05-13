/*
 * main.cpp
 * Entry point for the Inventory Management System.
 *
 * Responsibilities:
 *   1. Load product data from disk (Data layer).
 *   2. Launch the main menu (Presentation layer).
 *   3. Save data on exit (Data layer).
 *
 * Architecture: Presentation -> Logic -> Data
 *   main.cpp coordinates startup/shutdown only.
 */

#include "../include/presentation.h"
#include "../include/data.h"

#include <iostream>

int main() {
    // Load existing products from file
    std::vector<Product> products = loadProducts();

    // Start the main menu loop (presentation layer drives everything)
    showMainMenu(products);

    // Persist any changes made during the session
    saveProducts(products);

    std::cout << "Goodbye!\n";
    return 0;
}
