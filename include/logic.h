/*
 * logic.h
 * =======
 * Logic Layer — sorting, searching, recursion, validation, and statistics.
 *
 * Rules:
 *   - May call Data layer functions.
 *   - Must never include or call Presentation layer code.
 *   - All algorithms are implemented manually (no std::sort / std::find).
 */

#pragma once

#include "data.h"
#include <vector>
#include <string>

// -------------------------------------------------------
// Sorting (Bubble Sort — O(n²), teaches the algorithm)
// -------------------------------------------------------

/** Sort ascending by price. */
void sortByPrice(std::vector<Product>& products);

/** Sort ascending by stock quantity. */
void sortByQuantity(std::vector<Product>& products);

/** Sort alphabetically by name (case-insensitive). */
void sortByName(std::vector<Product>& products);

// -------------------------------------------------------
// Searching
// -------------------------------------------------------

/**
 * searchByName  — Linear Search, O(n)
 * Returns every product whose name contains the query (case-insensitive).
 */
std::vector<Product> searchByName(const std::vector<Product>& products,
                                  const std::string& query);

/**
 * searchById  — Binary Search, O(log n)
 * Products MUST be sorted by id before calling.
 * Returns a pointer to the found product, or nullptr.
 */
const Product* searchById(const std::vector<Product>& products, int id);

// -------------------------------------------------------
// Recursion
// -------------------------------------------------------

/**
 * calcTotalValue  — Recursive summation of (price × quantity).
 * Start call: calcTotalValue(products)  — index defaults to 0.
 */
double calcTotalValue(const std::vector<Product>& products, int index = 0);

/**
 * countLowStock  — Recursive count of products below threshold.
 * Start call: countLowStock(products, LOW_STOCK_THRESHOLD)
 */
int countLowStock(const std::vector<Product>& products,
                  int threshold,
                  int index = 0);

// -------------------------------------------------------
// Statistics helpers (used by the statistics panel)
// -------------------------------------------------------

/** Returns the most expensive product, or nullptr if list is empty. */
const Product* mostExpensive(const std::vector<Product>& products);

/** Returns the product with the highest stock quantity. */
const Product* highestStock(const std::vector<Product>& products);

/** Average price across all products. Returns 0 if list is empty. */
double averagePrice(const std::vector<Product>& products);

// -------------------------------------------------------
// Business Logic — Validated CRUD
// -------------------------------------------------------

/**
 * addNewProduct
 * Validates inputs, generates a unique ID, and appends to the list.
 * @return true on success; false + error string on failure.
 */
bool addNewProduct(std::vector<Product>& products,
                   const std::string& name,
                   double price,
                   int quantity,
                   Category category,
                   std::string& outError);

/**
 * deleteProduct
 * Removes the product with the given id.
 * @return true if removed, false if not found.
 */
bool deleteProduct(std::vector<Product>& products, int id);
