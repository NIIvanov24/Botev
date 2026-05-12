/*
 * data.h
 * Data layer - defines core data structures and file I/O functions.
 * Responsible for storing and retrieving product data.
 */

#pragma once

#include <string>
#include <vector>

// -------------------------------------------------------
// Constants
// -------------------------------------------------------
const int MAX_PRODUCTS = 500;
const std::string DATA_FILE = "assets/products.txt";

// -------------------------------------------------------
// Data Structures
// -------------------------------------------------------

/*
 * Represents a single product in the inventory.
 */
struct Product {
    int    id;
    std::string name;
    double price;
    int    quantity;
};

// -------------------------------------------------------
// Function Prototypes
// -------------------------------------------------------

/*
 * Loads products from the data file into a vector.
 * Returns: vector of Product records.
 */
std::vector<Product> loadProducts();

/*
 * Saves all products from the vector to the data file.
 * Parameters:
 *   - products: vector of Product records to save.
 */
void saveProducts(const std::vector<Product>& products);

/*
 * Adds a new product to the vector.
 * Parameters:
 *   - products: reference to the product vector.
 *   - p: the new Product to add.
 */
void addProduct(std::vector<Product>& products, const Product& p);

/*
 * Removes a product by ID from the vector.
 * Parameters:
 *   - products: reference to the product vector.
 *   - id: ID of the product to remove.
 * Returns: true if removed, false if not found.
 */
bool removeProduct(std::vector<Product>& products, int id);

/*
 * Generates the next available unique product ID.
 * Parameters:
 *   - products: current product vector.
 * Returns: next available integer ID.
 */
int nextProductId(const std::vector<Product>& products);
