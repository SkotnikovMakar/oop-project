#pragma once
#include <stdexcept>

class Price {
    int value;
public:
    Price(int val = 0) : value(val) {
        if (val < 0) throw std::invalid_argument("Price can't be negative");
    }
    int getValue() const { return value; }
    void setValue(int newVal) {
        if (newVal < 0) throw std::invalid_argument("Price can't be negative");
        value = newVal;
    }
};

class Quantity {
    int value;
public:
    Quantity(int val = 0) : value(val) {
        if (val < 0) throw std::invalid_argument("Quantity can't be negative");
    }
    int getValue() const { return value; }
    void setValue(int newVal) {
        if (newVal < 0) throw std::invalid_argument("Quantity can't be negative");
        value = newVal;
    }
    void change(int delta) {
        if (value + delta < 0) throw std::invalid_argument("Not enough quantity");
        value += delta;
    }
};

class Weight {
    double value;
public:
    Weight(double val = 0.0) : value(val) {
        if (val < 0.0) throw std::invalid_argument("Weight can't be negative");
    }
    double getValue() const { return value; }
    void setValue(double newVal) {
        if (newVal < 0.0) throw std::invalid_argument("Weight can't be negative");
        value = newVal;
    }
};