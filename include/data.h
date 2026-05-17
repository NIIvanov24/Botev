/*
 * data.h
 * ======
 * Data Layer — core data structures, constants, and file I/O prototypes.
 *
 * Architecture: Presentation -> Logic -> Data
 *   This header is the foundation. Only the Logic layer should call these
 *   functions; the Presentation layer must never access them directly.
 *
 * File format: pipe-delimited (id|name|price|quantity|category)
 */

#pragma once

#include <string>
#include <vector>

// -------------------------------------------------------
// Constants
// -------------------------------------------------------
inline constexpr int    MAX_PRODUCTS       = 500;
inline constexpr int    LOW_STOCK_THRESHOLD = 5;
inline const std::string DATA_FILE         = "assets/products.txt";

// -------------------------------------------------------
// Enumerations
// -------------------------------------------------------

/** Product category for visual grouping and icon display. */
enum class Category {
    FOOD,
    DRINK,
    DAIRY,
    BAKERY,
    OTHER
};

// -------------------------------------------------------
// Data Structures
// -------------------------------------------------------

/**
 * Product
 * Represents a single item in the inventory.
 * All fields are value-initialized to safe defaults.
 */
struct Product {
    int         id       = 0;
    std::string name;
    double      price    = 0.0;
    int         quantity = 0;
    Category    category = Category::OTHER;

    /** Computed: total value for this product line. */
    [[nodiscard]] double lineValue() const { return price * quantity; }

    /** True when stock is below the global low-stock threshold. */
    [[nodiscard]] bool isLowStock() const { return quantity < LOW_STOCK_THRESHOLD; }
};

// -------------------------------------------------------
// Function Prototypes — File I/O
// -------------------------------------------------------

/**
 * loadProducts
 * Reads all products from DATA_FILE.
 * Returns an empty vector if the file does not exist.
 */
std::vector<Product> loadProducts();

/**
 * saveProducts
 * Serialises all products to DATA_FILE, overwriting previous content.
 * @param products  The product list to persist.
 */
void saveProducts(const std::vector<Product>& products);

// -------------------------------------------------------
// Function Prototypes — CRUD helpers (called by Logic layer)
// -------------------------------------------------------

/**
 * addProduct
 * Appends a new product to the collection.
 * @param products  Reference to the live product vector.
 * @param p         The product to add (id must already be set).
 */
void addProduct(std::vector<Product>& products, const Product& p);

/**
 * removeProduct
 * Removes the first product whose id matches.
 * @param products  Reference to the live product vector.
 * @param id        ID to search for and remove.
 * @return true if a product was removed; false if not found.
 */
bool removeProduct(std::vector<Product>& products, int id);

/**
 * nextProductId
 * Generates the next unique product ID (max existing + 1).
 * @param products  The current product vector.
 * @return          Integer ID guaranteed to be unique.
 */
int nextProductId(const std::vector<Product>& products);

/**
 * categoryFromString / categoryToString
 * Round-trip helpers for serialising Category in the data file.
 */
Category    categoryFromString(const std::string& s);
std::string categoryToString(Category c);
