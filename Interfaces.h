#pragma once
#include <string>
#include <iostream>
#include <ctime>

enum class OrderStatus { Pending, Paid, Shipped, Delivered, Cancelled };
class Order;

struct OrderEvent {
    int orderId;
    OrderStatus oldStatus;
    OrderStatus newStatus;
    std::time_t timestamp;
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onOrderEvent(const OrderEvent& event) = 0;
};

class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void subscribe(IObserver* obs) = 0;
    virtual void unsubscribe(IObserver* obs) = 0;
    virtual void notify(const OrderEvent& event) = 0;
};

class Delivery {
public:
    virtual ~Delivery() = default;
    virtual double getCost(const Order& order) const = 0;
    virtual std::string getEstimatedTime() const = 0;
    virtual bool isAvailable(const Order& order) const = 0;
};

class Discount {
public:
    virtual ~Discount() = default;
    virtual void apply(Order& order) const = 0;
};