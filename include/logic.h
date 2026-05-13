/*
 * logic.h
 * Logic layer - function prototypes for sorting, searching, recursion, and validation.
 */

#pragma once

#include "data.h"
#include <vector>
#include <string>

// Sorting
void sortByPrice(std::vector<Product>& products);
void sortByQuantity(std::vector<Product>& products);
void sortByName(std::vector<Product>& products);

// Searching
std::vector<Product> searchByName(const std::vector<Product>& products, const std::string& query);
const Product* searchById(const std::vector<Product>& products, int id);

// Recursion
double calcTotalValue(const std::vector<Product>& products, int index = 0);
int countLowStock(const std::vector<Product>& products, int threshold, int index = 0);

// Business Logic
bool addNewProduct(std::vector<Product>& products, const std::string& name, double price, int quantity);
bool deleteProduct(std::vector<Product>& products, int id);
