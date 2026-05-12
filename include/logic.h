/*
 * logic.h
 * Logic layer - sorting, searching, and recursive algorithms.
 * Acts as intermediary between presentation and data layers.
 */

#pragma once

#include "data.h"
#include <vector>
#include <string>

// -------------------------------------------------------
// Sorting Algorithms
// -------------------------------------------------------

/*
 * Sorts products by price in ascending order using Bubble Sort.
 * Parameters:
 *   - products: reference to the product vector to sort.
 */
void sortByPrice(std::vector<Product>& products);

/*
 * Sorts products by quantity in ascending order using Bubble Sort.
 * Parameters:
 *   - products: reference to the product vector to sort.
 */
void sortByQuantity(std::vector<Product>& products);

/*
 * Sorts products by name alphabetically using Bubble Sort.
 * Parameters:
 *   - products: reference to the product vector to sort.
 */
void sortByName(std::vector<Product>& products);

// -------------------------------------------------------
// Searching Algorithms
// -------------------------------------------------------

/*
 * Searches for products whose name contains the query string (case-insensitive).
 * Uses Linear Search.
 * Parameters:
 *   - products: the product vector to search in.
 *   - query: the search string.
 * Returns: vector of matching Products.
 */
std::vector<Product> searchByName(const std::vector<Product>& products,
                                  const std::string& query);

/*
 * Searches for a product by exact ID using Binary Search.
 * IMPORTANT: vector must be sorted by ID before calling this.
 * Parameters:
 *   - products: the sorted product vector.
 *   - id: the ID to find.
 * Returns: pointer to found Product, or nullptr if not found.
 */
const Product* searchById(const std::vector<Product>& products, int id);

// -------------------------------------------------------
// Recursive Algorithms
// -------------------------------------------------------

/*
 * Recursively calculates the total inventory value
 * (sum of price * quantity for all products).
 * Parameters:
 *   - products: the product vector.
 *   - index: current index (start with 0).
 * Returns: total value as double.
 */
double calcTotalValue(const std::vector<Product>& products, int index = 0);

/*
 * Recursively counts how many products have quantity below a threshold.
 * Parameters:
 *   - products: the product vector.
 *   - threshold: minimum quantity to consider "low stock".
 *   - index: current index (start with 0).
 * Returns: count of low-stock products.
 */
int countLowStock(const std::vector<Product>& products,
                  int threshold,
                  int index = 0);

// -------------------------------------------------------
// Business Logic (CRUD via Logic Layer)
// -------------------------------------------------------

/*
 * Validates and adds a new product.
 * Parameters:
 *   - products: reference to the product vector.
 *   - name: product name (must not be empty).
 *   - price: product price (must be > 0).
 *   - quantity: product quantity (must be >= 0).
 * Returns: true on success, false if validation fails.
 */
bool addNewProduct(std::vector<Product>& products,
                   const std::string& name,
                   double price,
                   int quantity);

/*
 * Removes a product by ID.
 * Parameters:
 *   - products: reference to the product vector.
 *   - id: ID to remove.
 * Returns: true if removed, false if not found.
 */
bool deleteProduct(std::vector<Product>& products, int id);
