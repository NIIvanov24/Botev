/*
 * data.cpp
 * ========
 * Data Layer — file I/O and raw data operations.
 *
 * File format (pipe-delimited):
 *   id|name|price|quantity|category
 *
 * Backward compatible: if a line has only 4 fields (old format),
 * category defaults to OTHER.
 */

#include "../include/data.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// -------------------------------------------------------
// categoryFromString / categoryToString
// -------------------------------------------------------
Category categoryFromString(const std::string& s) {
    if (s == "FOOD")   return Category::FOOD;
    if (s == "DRINK")  return Category::DRINK;
    if (s == "DAIRY")  return Category::DAIRY;
    if (s == "BAKERY") return Category::BAKERY;
    return Category::OTHER;
}

std::string categoryToString(Category c) {
    switch (c) {
        case Category::FOOD:   return "FOOD";
        case Category::DRINK:  return "DRINK";
        case Category::DAIRY:  return "DAIRY";
        case Category::BAKERY: return "BAKERY";
        default:               return "OTHER";
    }
}

// -------------------------------------------------------
// loadProducts
// -------------------------------------------------------
std::vector<Product> loadProducts() {
    std::vector<Product> products;
    std::ifstream file(DATA_FILE);

    if (!file.is_open()) {
        // First run — return empty list; UI will show empty inventory.
        return products;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        Product p;
        const char DELIM = '|';

        std::string idStr, priceStr, qtyStr, catStr;

        // Mandatory fields
        if (!std::getline(ss, idStr,    DELIM)) continue;
        if (!std::getline(ss, p.name,   DELIM)) continue;
        if (!std::getline(ss, priceStr, DELIM)) continue;
        if (!std::getline(ss, qtyStr,   DELIM)) continue;

        // Optional category (backward compat)
        if (!std::getline(ss, catStr, DELIM)) catStr = "OTHER";

        try {
            p.id       = std::stoi(idStr);
            p.price    = std::stod(priceStr);
            p.quantity = std::stoi(qtyStr);
            p.category = categoryFromString(catStr);
            products.push_back(p);
        } catch (...) {
            std::cerr << "[data] Skipping malformed line: " << line << "\n";
        }
    }

    return products;
}

// -------------------------------------------------------
// saveProducts
// -------------------------------------------------------
void saveProducts(const std::vector<Product>& products) {
    std::ofstream file(DATA_FILE);

    if (!file.is_open()) {
        std::cerr << "[data] Cannot open file for writing: " << DATA_FILE << "\n";
        return;
    }

    for (const Product& p : products) {
        file << p.id                        << '|'
             << p.name                      << '|'
             << p.price                     << '|'
             << p.quantity                  << '|'
             << categoryToString(p.category) << "|\n";
    }
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
