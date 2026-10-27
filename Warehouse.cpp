#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse(size_t maxSize) : maxSize(maxSize) {
    if (maxSize == 0) throw std::invalid_argument("Max size must be positive");
}

Warehouse::Warehouse(const Warehouse& other) : maxSize(other.maxSize) {
    for (const auto& p : other.products) products.push_back(p->clone());
}

Warehouse& Warehouse::operator=(const Warehouse& other) {
    if (this != &other) {
        products.clear();
        maxSize = other.maxSize;
        for (const auto& p : other.products) products.push_back(p->clone());
    }
    return *this;
}

Warehouse::Warehouse(Warehouse&& other) noexcept
    : products(std::move(other.products)), maxSize(other.maxSize) {
}

Warehouse& Warehouse::operator=(Warehouse&& other) noexcept {
    if (this != &other) {
        products = std::move(other.products);
        maxSize = other.maxSize;
    }
    return *this;
}

bool Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (!product) return false;
    if (products.size() >= maxSize) return false;
    products.push_back(std::move(product));
    return true;
}

void Warehouse::removeById(int id) {
    products.erase(
        std::remove_if(products.begin(), products.end(),
            [id](const std::unique_ptr<Product>& p) { return p->getId() == id; }),
        products.end());
}

void Warehouse::removeByIndex(size_t index) {
    if (index >= products.size()) throw std::out_of_range("Index out of range");
    products.erase(products.begin() + index);
}

Product* Warehouse::findById(int id) {
    for (const auto& p : products)
        if (p->getId() == id) return p.get();
    return nullptr;
}

std::vector<Product*> Warehouse::findByCategory(const std::string& category) {
    std::vector<Product*> result;
    for (const auto& p : products)
        if (p->getCategory() == category) result.push_back(p.get());
    return result;
}

std::vector<Product*> Warehouse::findByPrice(const Price& price) {
    std::vector<Product*> result;
    for (const auto& p : products)
        if (p->getPrice().getValue() == price.getValue()) result.push_back(p.get());
    return result;
}

bool Warehouse::containsProduct(int id) const {
    for (const auto& p : products)
        if (p->getId() == id) return true;
    return false;
}

Product* Warehouse::getProductById(int id) {
    return findById(id);
}

bool Warehouse::moveProductTo(int id, Warehouse& other) {
    auto it = std::find_if(products.begin(), products.end(),
        [id](const std::unique_ptr<Product>& p) { return p->getId() == id; });
    if (it == products.end()) return false;

    if (!other.addProduct(std::move(*it))) return false;

    products.erase(it);
    return true;
}