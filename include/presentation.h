/*
 * presentation.h
 * Presentation layer - all user interaction (input/output).
 * Calls only the Logic layer; never accesses the Data layer directly.
 *
 * NOTE: When ImGui is integrated, these functions will be replaced
 *       by ImGui window rendering functions. The signatures below
 *       serve as the console fallback and structural placeholders.
 */

#pragma once

#include "data.h"
#include <vector>

// -------------------------------------------------------
// Main Menu
// -------------------------------------------------------

/*
 * Displays the main menu and handles user choice.
 * Parameters:
 *   - products: reference to the product vector (may be modified).
 */
void showMainMenu(std::vector<Product>& products);

// -------------------------------------------------------
// Product Table Display
// -------------------------------------------------------

/*
 * Renders the product list as a formatted table.
 * Parameters:
 *   - products: vector of products to display.
 *   - title: optional title header for the table.
 */
void renderProductTable(const std::vector<Product>& products,
                        const std::string& title = "Inventory");

// -------------------------------------------------------
// Sort Menu
// -------------------------------------------------------

/*
 * Shows the sort submenu and performs the chosen sort.
 * Parameters:
 *   - products: reference to the product vector.
 */
void showSortMenu(std::vector<Product>& products);

// -------------------------------------------------------
// Search Menu
// -------------------------------------------------------

/*
 * Shows the search submenu, accepts query input, displays results.
 * Parameters:
 *   - products: the product vector to search in.
 */
void showSearchMenu(const std::vector<Product>& products);

// -------------------------------------------------------
// Add / Remove Products
// -------------------------------------------------------

/*
 * Shows form to add a new product, calls logic layer to validate and insert.
 * Parameters:
 *   - products: reference to the product vector.
 */
void showAddProductForm(std::vector<Product>& products);

/*
 * Shows form to remove a product by ID.
 * Parameters:
 *   - products: reference to the product vector.
 */
void showRemoveProductForm(std::vector<Product>& products);

// -------------------------------------------------------
// Statistics Panel
// -------------------------------------------------------

/*
 * Displays computed statistics: total value, low-stock count, etc.
 * Parameters:
 *   - products: the product vector.
 */
void showStatistics(const std::vector<Product>& products);
