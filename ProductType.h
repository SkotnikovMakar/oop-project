#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <stdexcept>

class ProductType {
private:
    std::string category;
    double baseWeight;
    double basePrice;

    ProductType(const std::string& c, double w, double p) : category(c), baseWeight(w), basePrice(p) {}

    static std::unordered_map<std::string, std::shared_ptr<ProductType>>& getPool() {
        static std::unordered_map<std::string, std::shared_ptr<ProductType>> pool;
        return pool;
    }

public:
    static std::shared_ptr<ProductType> getType(const std::string& category) {
        auto& pool = getPool();
        if (pool.find(category) == pool.end()) {
            if (category == "electronics") pool[category] = std::shared_ptr<ProductType>(new ProductType(category, 1.5, 1000));
            else if (category == "clothing") pool[category] = std::shared_ptr<ProductType>(new ProductType(category, 0.5, 500));
            else if (category == "food") pool[category] = std::shared_ptr<ProductType>(new ProductType(category, 0.2, 100));
            else throw std::invalid_argument("Unknown category");
        }
        return pool[category];
    }

    std::string getCategory() const { return category; }
    double getBaseWeight() const { return baseWeight; }
    double getBasePrice() const { return basePrice; }
};