#pragma once
#include <string>
#include <memory>
#include "Attributes.h"

class Warehouse;

class Product {
protected:
    int id;
    std::string name;
    Price price;
    Quantity quantity;
    Weight weight;
    std::string category;
    static int nextId;

public:
    Product(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight, const std::string& category);
    virtual ~Product() = default;

    int getId() const { return id; }
    std::string getCategory() const { return category; }
    Price getPrice() const { return price; }
    Quantity getQuantity() const { return quantity; }
    Weight getWeight() const { return weight; }

    void changeQuantity(int delta) { quantity.change(delta); }
    void setPrice(const Price& newPrice) { price = newPrice; }

    bool transferTo(Warehouse& other);

    virtual std::unique_ptr<Product> clone() const = 0;
};

class Electronics : public Product {
public:
    Electronics(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Smartphone : public Electronics {
public:
    Smartphone(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override { return std::make_unique<Smartphone>(*this); }
};

class Laptop : public Electronics {
public:
    Laptop(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override { return std::make_unique<Laptop>(*this); }
};

class Clothing : public Product {
public:
    Clothing(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class TShirt : public Clothing {
public:
    TShirt(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override { return std::make_unique<TShirt>(*this); }
};

class Jacket : public Clothing {
public:
    Jacket(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override { return std::make_unique<Jacket>(*this); }
};

class Food : public Product {
public:
    Food(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Milk : public Food {
public:
    Milk(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override { return std::make_unique<Milk>(*this); }
};

class Bread : public Food {
public:
    Bread(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override { return std::make_unique<Bread>(*this); }
};