#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "Interfaces.h"
#include "Product.h"

class Order : public IObservable {
    int id;
    std::string customer;
    std::vector<std::shared_ptr<Product>> items;
    OrderStatus status = OrderStatus::Pending;
    std::shared_ptr<Delivery> delivery;
    std::vector<IObserver*> observers;
    double discountAmount = 0.0;

public:
    Order(int i, const std::string& c) : id(i), customer(c) {}

    int getId() const { return id; }
    const std::vector<std::shared_ptr<Product>>& getItems() const { return items; }

    void addItem(std::shared_ptr<Product> item) { items.push_back(item); }

    void removeItem(int itemId) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [itemId](const std::shared_ptr<Product>& p) { return p->getId() == itemId; }), items.end());
    }

    double getTotalWeight() const {
        double w = 0; for (const auto& i : items) w += i->getTotalWeight(); return w;
    }
    double getTotalPrice() const {
        double total = 0;
        for (const auto& i : items) total += i->getTotalPrice();
        total -= discountAmount;
        if (delivery) total += delivery->getCost(*this);
        return total < 0 ? 0 : total;
    }

    void applyDiscount(const Discount& discount) { discount.apply(*this); }
    void applyDiscountAmount(double amt) { discountAmount += amt; }
    void setDelivery(std::shared_ptr<Delivery> d) { delivery = d; }
    void setDeliveryFree() { delivery = nullptr; }

    void setStatus(OrderStatus s) {
        if (status == s) return;
        OrderStatus old = status;
        status = s;
        for (auto obs : observers) obs->onOrderEvent({ id, old, s, std::time(nullptr) });
    }

    void subscribe(IObserver* obs) override { observers.push_back(obs); }

    void unsubscribe(IObserver* obs) override {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notify(const OrderEvent& event) override {}

    friend Order& operator+(Order& order, const Discount& discount);
    friend Order& operator<<(Order& order, std::shared_ptr<Delivery> delivery);
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

inline Order& operator+(Order& order, const Discount& discount) {
    order.applyDiscount(discount);
    return order;
}
inline Order& operator<<(Order& order, std::shared_ptr<Delivery> delivery) {
    order.setDelivery(delivery); return order;
}
inline std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Order #" << order.id << " | Total: " << order.getTotalPrice() << " rub.";
    return os;
}