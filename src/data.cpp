/*
 * data.cpp
 * Data layer implementation - file I/O and raw data operations.
 */

#include "data.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// -------------------------------------------------------
// loadProducts
// -------------------------------------------------------
std::vector<Product> loadProducts() {
    std::vector<Product> products;
    std::ifstream file(DATA_FILE);

    if (!file.is_open()) {
        // File doesn't exist yet - return empty list
        return products;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        Product p;
        char delim = '|';

        // Format: id|name|price|quantity
        std::string idStr, priceStr, qtyStr;
        if (std::getline(ss, idStr,    delim) &&
            std::getline(ss, p.name,   delim) &&
            std::getline(ss, priceStr, delim) &&
            std::getline(ss, qtyStr,   delim))
        {
            try {
                p.id       = std::stoi(idStr);
                p.price    = std::stod(priceStr);
                p.quantity = std::stoi(qtyStr);
                products.push_back(p);
            } catch (...) {
                std::cerr << "Warning: skipping malformed line: " << line << "\n";
            }
        }
    }

    file.close();
    return products;
}

// -------------------------------------------------------
// saveProducts
// -------------------------------------------------------
void saveProducts(const std::vector<Product>& products) {
    std::ofstream file(DATA_FILE);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file for writing: " << DATA_FILE << "\n";
        return;
    }

    for (const Product& p : products) {
        file << p.id       << "|"
             << p.name     << "|"
             << p.price    << "|"
             << p.quantity << "|\n";
    }

    file.close();
}

// -------------------------------------------------------
// addProduct
// -------------------------------------------------------
void addProduct(std::vector<Product>& products, const Product& p) {
    products.push_back(p);
}

// -------------------------------------------------------
// removeProduct
// -------------------------------------------------------
bool removeProduct(std::vector<Product>& products, int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == id) {
            products.erase(it);
            return true;
        }
    }
    return false;
}

// -------------------------------------------------------
// nextProductId
// -------------------------------------------------------
int nextProductId(const std::vector<Product>& products) {
    if (products.empty()) return 1;

    int maxId = 0;
    for (const Product& p : products) {
        if (p.id > maxId) maxId = p.id;
    }
    return maxId + 1;
}
