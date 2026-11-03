#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include "Order.h"

class OrderManager : public IObserver {
    std::vector<Order*> activeOrders;
    std::map<std::string, int> customerOrders;
    double totalTurnover = 0;
    size_t maxActiveOrders;

public:
    OrderManager(size_t max) : maxActiveOrders(max) {}
    ~OrderManager() { for (auto o : activeOrders) delete o; }

    Order* createOrder(const std::string& customer) {
        if (activeOrders.size() >= maxActiveOrders) throw std::runtime_error("Max limit");
        Order* order = new Order(activeOrders.size() + 1, customer);
        order->subscribe(this);
        activeOrders.push_back(order);
        customerOrders[customer]++;
        return order;
    }

    void onOrderEvent(const OrderEvent& event) override {
        if (event.newStatus == OrderStatus::Paid) {
            totalTurnover += 1000;
        }
        if (event.newStatus == OrderStatus::Cancelled) {
            activeOrders.erase(
                std::remove_if(activeOrders.begin(), activeOrders.end(),
                    [&event](Order* o) { return o->getId() == event.orderId; }),
                activeOrders.end()
            );
        }
    }
    double getTurnover() const { return totalTurnover; }
    size_t getCustomerCount() const { return customerOrders.size(); }
};