/*
 * presentation.cpp
 * Presentation layer implementation.
 *
 * Currently uses console I/O as a working placeholder.
 * Each function maps to a future ImGui window/widget.
 * Only calls logic layer functions - never data layer directly.
 */

#include "presentation.h"
#include "logic.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

// -------------------------------------------------------
// Helper: clear input buffer
// -------------------------------------------------------
static void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// -------------------------------------------------------
// renderProductTable
// -------------------------------------------------------
void renderProductTable(const std::vector<Product>& products,
                        const std::string& title)
{
    std::cout << "\n=== " << title << " ===\n";

    if (products.empty()) {
        std::cout << "  (no products)\n\n";
        return;
    }

    // Table header
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(24) << "Name"
              << std::setw(10) << "Price"
              << std::setw(10) << "Quantity"
              << "\n";
    std::cout << std::string(50, '-') << "\n";

    // Table rows
    for (const Product& p : products) {
        std::cout << std::left
                  << std::setw(6)  << p.id
                  << std::setw(24) << p.name
                  << std::setw(10) << std::fixed << std::setprecision(2) << p.price
                  << std::setw(10) << p.quantity
                  << "\n";
    }
    std::cout << "\n";
}

// -------------------------------------------------------
// showSortMenu
// -------------------------------------------------------
void showSortMenu(std::vector<Product>& products) {
    std::cout << "\n--- Sort Products ---\n"
              << "1. Sort by Price\n"
              << "2. Sort by Quantity\n"
              << "3. Sort by Name\n"
              << "0. Back\n"
              << "Choice: ";

    int choice = 0;
    std::cin >> choice;
    clearInputBuffer();

    switch (choice) {
        case 1:
            sortByPrice(products);
            renderProductTable(products, "Sorted by Price");
            break;
        case 2:
            sortByQuantity(products);
            renderProductTable(products, "Sorted by Quantity");
            break;
        case 3:
            sortByName(products);
            renderProductTable(products, "Sorted by Name");
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice.\n";
    }
}

// -------------------------------------------------------
// showSearchMenu
// -------------------------------------------------------
void showSearchMenu(const std::vector<Product>& products) {
    std::cout << "\n--- Search Products ---\n"
              << "Enter product name (or part of it): ";

    std::string query;
    std::getline(std::cin, query);

    if (query.empty()) {
        std::cout << "Search query cannot be empty.\n";
        return;
    }

    std::vector<Product> results = searchByName(products, query);

    if (results.empty()) {
        std::cout << "No products found matching \"" << query << "\".\n";
    } else {
        renderProductTable(results, "Search Results for: " + query);
    }
}

// -------------------------------------------------------
// showAddProductForm
// -------------------------------------------------------
void showAddProductForm(std::vector<Product>& products) {
    std::cout << "\n--- Add New Product ---\n";

    std::string name;
    double price = 0.0;
    int quantity = 0;

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Price: ";
    if (!(std::cin >> price)) {
        std::cout << "Error: invalid price.\n";
        clearInputBuffer();
        return;
    }

    std::cout << "Quantity: ";
    if (!(std::cin >> quantity)) {
        std::cout << "Error: invalid quantity.\n";
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (addNewProduct(products, name, price, quantity)) {
        std::cout << "Product added successfully (ID: "
                  << products.back().id << ").\n";
    } else {
        std::cout << "Failed to add product. Check the values and try again.\n";
    }
}

// -------------------------------------------------------
// showRemoveProductForm
// -------------------------------------------------------
void showRemoveProductForm(std::vector<Product>& products) {
    std::cout << "\n--- Remove Product ---\n"
              << "Enter product ID to remove: ";

    int id = 0;
    if (!(std::cin >> id)) {
        std::cout << "Error: invalid ID.\n";
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (deleteProduct(products, id)) {
        std::cout << "Product with ID " << id << " removed.\n";
    } else {
        std::cout << "No product found with ID " << id << ".\n";
    }
}

// -------------------------------------------------------
// showStatistics
// -------------------------------------------------------
void showStatistics(const std::vector<Product>& products) {
    const int LOW_STOCK_THRESHOLD = 5;

    double totalValue = calcTotalValue(products);
    int    lowStock   = countLowStock(products, LOW_STOCK_THRESHOLD);

    std::cout << "\n=== Inventory Statistics ===\n"
              << "Total products     : " << products.size() << "\n"
              << "Total inventory    : "
              << std::fixed << std::setprecision(2) << totalValue << " BGN\n"
              << "Low stock items    : " << lowStock
              << " (quantity < " << LOW_STOCK_THRESHOLD << ")\n\n";
}

// -------------------------------------------------------
// showMainMenu
// -------------------------------------------------------
void showMainMenu(std::vector<Product>& products) {
    bool running = true;

    while (running) {
        std::cout << "\n=============================\n"
                  << "  Inventory Management System\n"
                  << "=============================\n"
                  << "1. View All Products\n"
                  << "2. Add Product\n"
                  << "3. Remove Product\n"
                  << "4. Sort Products\n"
                  << "5. Search Products\n"
                  << "6. Statistics\n"
                  << "0. Exit\n"
                  << "Choice: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: renderProductTable(products);           break;
            case 2: showAddProductForm(products);           break;
            case 3: showRemoveProductForm(products);        break;
            case 4: showSortMenu(products);                 break;
            case 5: showSearchMenu(products);               break;
            case 6: showStatistics(products);               break;
            case 0: running = false;                        break;
            default: std::cout << "Invalid choice.\n";     break;
        }
    }
}
