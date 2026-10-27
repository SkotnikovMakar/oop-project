#include "Product.h"
#include "Warehouse.h"

int Product::nextId = 1;

Product::Product(const std::string& n, const Price& p, const Quantity& q, const Weight& w, const std::string& c)
    : id(nextId++), name(n), price(p), quantity(q), weight(w), category(c) {
}

Electronics::Electronics(const std::string& n, const Price& p, const Quantity& q, const Weight& w)
    : Product(n, p, q, w, "electronics") {
}
Clothing::Clothing(const std::string& n, const Price& p, const Quantity& q, const Weight& w)
    : Product(n, p, q, w, "clothing") {
}
Food::Food(const std::string& n, const Price& p, const Quantity& q, const Weight& w)
    : Product(n, p, q, w, "food") {
}

Smartphone::Smartphone(const std::string& n, const Price& p, const Quantity& q, const Weight& w) : Electronics(n, p, q, w) {}
Laptop::Laptop(const std::string& n, const Price& p, const Quantity& q, const Weight& w) : Electronics(n, p, q, w) {}
TShirt::TShirt(const std::string& n, const Price& p, const Quantity& q, const Weight& w) : Clothing(n, p, q, w) {}
Jacket::Jacket(const std::string& n, const Price& p, const Quantity& q, const Weight& w) : Clothing(n, p, q, w) {}
Milk::Milk(const std::string& n, const Price& p, const Quantity& q, const Weight& w) : Food(n, p, q, w) {}
Bread::Bread(const std::string& n, const Price& p, const Quantity& q, const Weight& w) : Food(n, p, q, w) {}

bool Product::transferTo(Warehouse& other) {
    auto copy = clone();
    return other.addProduct(std::move(copy));
}