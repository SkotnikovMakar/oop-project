#pragma once
#include "Interfaces.h"
#include "Order.h"

class PercentDiscount : public Discount {
    double pct;
public:
    PercentDiscount(double p) : pct(p) {}
    void apply(Order& o) const override {
        o.applyDiscountAmount(o.getTotalPrice() * (pct / 100.0));
    }
};

class CashbackDiscount : public Discount {
    double pct;
public:
    CashbackDiscount(double p) : pct(p) {}
    void apply(Order& o) const override {
        std::cout << "[Cashback] 5% returned to bonus account.\n";
    }
};

class FreeDeliveryDiscount : public Discount {
public:
    void apply(Order& o) const override {
        o.setDeliveryFree();
        std::cout << "[Promo] Delivery is now free.\n";
    }
};

class GiftDiscount : public Discount {
public:
    void apply(Order& o) const override {
        std::cout << "[Promo] Added free gift to the order.\n";
    }
};