/*
 * logic.cpp
 * Logic layer implementation - sorting, searching, recursion, and validation.
 */

#include "../include/logic.h"

#include <algorithm>
#include <cctype>
#include <iostream>

// -------------------------------------------------------
// Helper: lowercase string for case-insensitive comparison
// -------------------------------------------------------
static std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = static_cast<char>(std::tolower(c));
    return result;
}

// -------------------------------------------------------
// Sorting - Bubble Sort by Price
// -------------------------------------------------------
void sortByPrice(std::vector<Product>& products) {
    int n = static_cast<int>(products.size());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (products[j].price > products[j + 1].price) {
                std::swap(products[j], products[j + 1]);
            }
        }
    }
}

// -------------------------------------------------------
// Sorting - Bubble Sort by Quantity
// -------------------------------------------------------
void sortByQuantity(std::vector<Product>& products) {
    int n = static_cast<int>(products.size());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (products[j].quantity > products[j + 1].quantity) {
                std::swap(products[j], products[j + 1]);
            }
        }
    }
}

// -------------------------------------------------------
// Sorting - Bubble Sort by Name (alphabetical)
// -------------------------------------------------------
void sortByName(std::vector<Product>& products) {
    int n = static_cast<int>(products.size());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (toLower(products[j].name) > toLower(products[j + 1].name)) {
                std::swap(products[j], products[j + 1]);
            }
        }
    }
}

// -------------------------------------------------------
// Searching - Linear Search by Name (partial, case-insensitive)
// -------------------------------------------------------
std::vector<Product> searchByName(const std::vector<Product>& products,
                                  const std::string& query)
{
    std::vector<Product> results;
    std::string lowerQuery = toLower(query);

    for (const Product& p : products) {
        if (toLower(p.name).find(lowerQuery) != std::string::npos) {
            results.push_back(p);
        }
    }

    return results;
}

// -------------------------------------------------------
// Searching - Binary Search by ID
// (products must be sorted by ID before calling)
// -------------------------------------------------------
const Product* searchById(const std::vector<Product>& products, int id) {
    int left  = 0;
    int right = static_cast<int>(products.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].id == id) return &products[mid];
        if (products[mid].id < id)  left  = mid + 1;
        else                        right = mid - 1;
    }

    return nullptr; // Not found
}

// -------------------------------------------------------
// Recursion - Total Inventory Value
// -------------------------------------------------------
double calcTotalValue(const std::vector<Product>& products, int index) {
    // Base case: index out of bounds
    if (index >= static_cast<int>(products.size())) return 0.0;

    // Recursive case: add current product value + rest
    return (products[index].price * products[index].quantity)
           + calcTotalValue(products, index + 1);
}

// -------------------------------------------------------
// Recursion - Count Low Stock Products
// -------------------------------------------------------
int countLowStock(const std::vector<Product>& products,
                  int threshold,
                  int index)
{
    // Base case
    if (index >= static_cast<int>(products.size())) return 0;

    // Check current product
    int current = (products[index].quantity < threshold) ? 1 : 0;

    // Recursive case
    return current + countLowStock(products, threshold, index + 1);
}

// -------------------------------------------------------
// Business Logic - Add New Product (with validation)
// -------------------------------------------------------
bool addNewProduct(std::vector<Product>& products,
                   const std::string& name,
                   double price,
                   int quantity)
{
    // Validate inputs
    if (name.empty()) {
        std::cerr << "Error: product name cannot be empty.\n";
        return false;
    }
    if (price <= 0.0) {
        std::cerr << "Error: price must be greater than 0.\n";
        return false;
    }
    if (quantity < 0) {
        std::cerr << "Error: quantity cannot be negative.\n";
        return false;
    }

    Product p;
    p.id       = nextProductId(products);
    p.name     = name;
    p.price    = price;
    p.quantity = quantity;

    addProduct(products, p);
    return true;
}

// -------------------------------------------------------
// Business Logic - Delete Product
// -------------------------------------------------------
bool deleteProduct(std::vector<Product>& products, int id) {
    return removeProduct(products, id);
}
