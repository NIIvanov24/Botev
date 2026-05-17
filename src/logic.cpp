/*
 * logic.cpp
 * =========
 * Logic Layer — sorting, searching, recursion, statistics, validation.
 *
 * All algorithms are hand-implemented to satisfy the educational requirement.
 * No std::sort / std::find / std::accumulate are used.
 */

#include "../include/logic.h"
#include "../include/data.h"

#include <cctype>
#include <string>
#include <sstream>

// -------------------------------------------------------
// Internal helper: lower-case a string
// -------------------------------------------------------
static std::string toLower(const std::string& s) {
    std::string r = s;
    for (char& c : r) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return r;
}

// -------------------------------------------------------
// Bubble Sort — by Price (ascending)
// -------------------------------------------------------
void sortByPrice(std::vector<Product>& products) {
    const int n = static_cast<int>(products.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (products[j].price > products[j + 1].price) {
                std::swap(products[j], products[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // early exit: already sorted
    }
}

// -------------------------------------------------------
// Bubble Sort — by Quantity (ascending)
// -------------------------------------------------------
void sortByQuantity(std::vector<Product>& products) {
    const int n = static_cast<int>(products.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (products[j].quantity > products[j + 1].quantity) {
                std::swap(products[j], products[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// -------------------------------------------------------
// Bubble Sort — by Name (alphabetical, case-insensitive)
// -------------------------------------------------------
void sortByName(std::vector<Product>& products) {
    const int n = static_cast<int>(products.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (toLower(products[j].name) > toLower(products[j + 1].name)) {
                std::swap(products[j], products[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// -------------------------------------------------------
// Linear Search — by Name (partial, case-insensitive)
// -------------------------------------------------------
std::vector<Product> searchByName(const std::vector<Product>& products,
                                  const std::string& query)
{
    std::vector<Product> results;
    const std::string lq = toLower(query);

    for (const Product& p : products) {
        if (toLower(p.name).find(lq) != std::string::npos) {
            results.push_back(p);
        }
    }
    return results;
}

// -------------------------------------------------------
// Binary Search — by ID  (list must be sorted by id)
// -------------------------------------------------------
const Product* searchById(const std::vector<Product>& products, int id) {
    int left  = 0;
    int right = static_cast<int>(products.size()) - 1;

    while (left <= right) {
        const int mid = left + (right - left) / 2;
        if      (products[mid].id == id) return &products[mid];
        else if (products[mid].id <  id) left  = mid + 1;
        else                             right = mid - 1;
    }
    return nullptr;
}

// -------------------------------------------------------
// Recursion — Total Inventory Value
// -------------------------------------------------------
double calcTotalValue(const std::vector<Product>& products, int index) {
    if (index >= static_cast<int>(products.size())) return 0.0;
    return products[index].lineValue()
           + calcTotalValue(products, index + 1);
}

// -------------------------------------------------------
// Recursion — Count Low-Stock Products
// -------------------------------------------------------
int countLowStock(const std::vector<Product>& products,
                  int threshold,
                  int index)
{
    if (index >= static_cast<int>(products.size())) return 0;
    const int hit = (products[index].quantity < threshold) ? 1 : 0;
    return hit + countLowStock(products, threshold, index + 1);
}

// -------------------------------------------------------
// Statistics helpers
// -------------------------------------------------------
const Product* mostExpensive(const std::vector<Product>& products) {
    if (products.empty()) return nullptr;
    const Product* best = &products[0];
    for (const Product& p : products) {
        if (p.price > best->price) best = &p;
    }
    return best;
}

const Product* highestStock(const std::vector<Product>& products) {
    if (products.empty()) return nullptr;
    const Product* best = &products[0];
    for (const Product& p : products) {
        if (p.quantity > best->quantity) best = &p;
    }
    return best;
}

double averagePrice(const std::vector<Product>& products) {
    if (products.empty()) return 0.0;
    double sum = 0.0;
    for (const Product& p : products) sum += p.price;
    return sum / static_cast<double>(products.size());
}

// -------------------------------------------------------
// Business Logic — Validated Add
// -------------------------------------------------------
bool addNewProduct(std::vector<Product>& products,
                   const std::string& name,
                   double price,
                   int quantity,
                   Category category,
                   std::string& outError)
{
    if (name.empty()) {
        outError = "Product name cannot be empty.";
        return false;
    }
    if (name.size() > 48) {
        outError = "Name too long (max 48 chars).";
        return false;
    }
    if (price <= 0.0) {
        outError = "Price must be greater than 0.";
        return false;
    }
    if (quantity < 0) {
        outError = "Quantity cannot be negative.";
        return false;
    }
    if (static_cast<int>(products.size()) >= MAX_PRODUCTS) {
        outError = "Inventory is full (max " + std::to_string(MAX_PRODUCTS) + ").";
        return false;
    }

    Product p;
    p.id       = nextProductId(products);
    p.name     = name;
    p.price    = price;
    p.quantity = quantity;
    p.category = category;

    addProduct(products, p);
    outError.clear();
    return true;
}

// -------------------------------------------------------
// Business Logic — Delete
// -------------------------------------------------------
bool deleteProduct(std::vector<Product>& products, int id) {
    return removeProduct(products, id);
}
