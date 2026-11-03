#pragma once
#include <memory>
#include <iostream>
#include "Interfaces.h"
#include "Order.h"

class CourierDelivery : public Delivery {
public:
    double getCost(const Order& o) const override { return 500.0; }
    std::string getEstimatedTime() const override { return "1-2 days"; }
    bool isAvailable(const Order& o) const override { return o.getTotalWeight() <= 20.0; }
};

class PickupDelivery : public Delivery {
public:
    double getCost(const Order& o) const override { return 0.0; }
    std::string getEstimatedTime() const override { return "1-3 days"; }
    bool isAvailable(const Order& o) const override { return true; }
};

class PostDelivery : public Delivery {
public:
    double getCost(const Order& o) const override { return 200.0; }
    std::string getEstimatedTime() const override { return "5-10 days"; }
    bool isAvailable(const Order& o) const override { return o.getTotalWeight() <= 10.0; }
};

class DeliveryProxy : public Delivery {
    std::shared_ptr<Delivery> realDelivery;
    mutable double cachedCost = -1;
public:
    DeliveryProxy(std::shared_ptr<Delivery> d) : realDelivery(d) {}

    double getCost(const Order& o) const override {
        if (cachedCost < 0) {
            std::cout << "[Proxy] Logging: calculating delivery cost via " << realDelivery->getEstimatedTime() << "...\n";
            cachedCost = realDelivery->getCost(o);
        }
        return cachedCost;
    }

    std::string getEstimatedTime() const override { return realDelivery->getEstimatedTime(); }

    bool isAvailable(const Order& o) const override {
        std::cout << "[Proxy] Logging: checking availability and region...\n";
        return realDelivery->isAvailable(o);
    }
};