#pragma once
#include <vector>
#include <memory>
#include "Product.h"

class WarehouseIterator {
    std::vector<std::unique_ptr<Product>>::iterator current;
public:
    explicit WarehouseIterator(std::vector<std::unique_ptr<Product>>::iterator it) : current(it) {}
    Product& operator*() { return **current; }
    Product* operator->() { return current->get(); }
    WarehouseIterator& operator++() { ++current; return *this; }
    bool operator!=(const WarehouseIterator& other) const { return current != other.current; }
    bool operator==(const WarehouseIterator& other) const { return current == other.current; }
};

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products;
    size_t maxSize;

public:
    explicit Warehouse(size_t maxSize);

    Warehouse(const Warehouse& other);
    Warehouse& operator=(const Warehouse& other);
    Warehouse(Warehouse&& other) noexcept;
    Warehouse& operator=(Warehouse&& other) noexcept;
    ~Warehouse() = default;

    bool addProduct(std::unique_ptr<Product> product);
    void removeById(int id);
    void removeByIndex(size_t index);

    Product* findById(int id);
    std::vector<Product*> findByCategory(const std::string& category);
    std::vector<Product*> findByPrice(const Price& price);

    bool containsProduct(int id) const;
    Product* getProductById(int id);

    bool moveProductTo(int id, Warehouse& other);

    WarehouseIterator begin() { return WarehouseIterator(products.begin()); }
    WarehouseIterator end() { return WarehouseIterator(products.end()); }

    size_t size() const { return products.size(); }
    size_t getMaxSize() const { return maxSize; }
};