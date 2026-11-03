#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include "OrderManager.h"
#include "DeliveryImpl.h"
#include "DiscountImpl.h"
#include "Factories.h"

void printMenu() {
    std::cout << "\n=== Order Management System ===\n";
    std::cout << "1.  Create Order\n";
    std::cout << "2.  Add Item to Order\n";
    std::cout << "3.  Set Delivery\n";
    std::cout << "4.  Apply Percent Discount\n";
    std::cout << "5.  Change Order Status\n";
    std::cout << "6.  Print Order Info\n";
    std::cout << "7.  Print Manager Turnover\n";
    std::cout << "8.  Exit\n";
    std::cout << "Choose: ";
}

int main() {
    try {
        OrderManager manager(5);
        std::vector<Order*> orders;
        int choice = 0;

        while (choice != 8) {
            printMenu();
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input.\n";
                continue;
            }

            try {
                switch (choice) {
                case 1: {
                    std::string customer;
                    std::cout << "Customer name: ";
                    std::cin >> customer;
                    Order* order = manager.createOrder(customer);
                    orders.push_back(order);
                    std::cout << "Order created. Index: " << orders.size() - 1 << "\n";
                    break;
                }
                case 2: {
                    if (orders.empty()) { std::cout << "No orders.\n"; break; }
                    int idx;
                    std::cout << "Order index: ";
                    std::cin >> idx;
                    if (idx < 0 || idx >= (int)orders.size()) { std::cout << "Invalid index.\n"; break; }

                    int itemChoice;
                    std::cout << "1. Smartphone\n2. Laptop\n3. TShirt\n4. Jacket\n5. Milk\n6. Bread\nChoose: ";
                    std::cin >> itemChoice;

                    std::string name;
                    int price, qty;
                    double weight;
                    std::cout << "Name: "; std::cin >> name;
                    std::cout << "Price: "; std::cin >> price;
                    std::cout << "Quantity: "; std::cin >> qty;
                    std::cout << "Weight: "; std::cin >> weight;

                    ProductFactory* f = nullptr;
                    SmartphoneFactory sf; LaptopFactory lf; TShirtFactory tf;
                    JacketFactory jf; MilkFactory mf; BreadFactory bf;

                    if (itemChoice == 1) f = &sf;
                    else if (itemChoice == 2) f = &lf;
                    else if (itemChoice == 3) f = &tf;
                    else if (itemChoice == 4) f = &jf;
                    else if (itemChoice == 5) f = &mf;
                    else if (itemChoice == 6) f = &bf;
                    else { std::cout << "Invalid item.\n"; break; }

                    orders[idx]->addItem(std::shared_ptr<Product>(f->createProduct(name, price, qty, weight)));
                    std::cout << "Item added.\n";
                    break;
                }
                case 3: {
                    if (orders.empty()) { std::cout << "No orders.\n"; break; }
                    int idx;
                    std::cout << "Order index: ";
                    std::cin >> idx;
                    if (idx < 0 || idx >= (int)orders.size()) { std::cout << "Invalid index.\n"; break; }

                    int delChoice;
                    std::cout << "1. Courier (500), 2. Pickup (0), 3. Post (200): ";
                    std::cin >> delChoice;

                    std::shared_ptr<Delivery> real;
                    if (delChoice == 1) real = std::make_shared<CourierDelivery>();
                    else if (delChoice == 2) real = std::make_shared<PickupDelivery>();
                    else if (delChoice == 3) real = std::make_shared<PostDelivery>();
                    else { std::cout << "Invalid delivery.\n"; break; }

                    auto proxy = std::make_shared<DeliveryProxy>(real);

                    if (proxy->isAvailable(*orders[idx])) {
                        *orders[idx] << proxy;
                        std::cout << "Delivery assigned. Cost: " << proxy->getCost(*orders[idx]) << " rub.\n";
                    }
                    else {
                        std::cout << "Delivery not available for this weight.\n";
                    }
                    break;
                }
                case 4: {
                    if (orders.empty()) { std::cout << "No orders.\n"; break; }
                    int idx;
                    std::cout << "Order index: ";
                    std::cin >> idx;
                    if (idx < 0 || idx >= (int)orders.size()) { std::cout << "Invalid index.\n"; break; }

                    PercentDiscount promo(10);
                    *orders[idx] + promo;
                    std::cout << "10% discount applied.\n";
                    break;
                }
                case 5: {
                    if (orders.empty()) { std::cout << "No orders.\n"; break; }
                    int idx, statusChoice;
                    std::cout << "Order index: ";
                    std::cin >> idx;
                    if (idx < 0 || idx >= (int)orders.size()) { std::cout << "Invalid index.\n"; break; }

                    std::cout << "Status (0-Pending, 1-Paid, 2-Shipped, 3-Delivered, 4-Cancelled): ";
                    std::cin >> statusChoice;

                    if (statusChoice < 0 || statusChoice > 4) {
                        std::cout << "Invalid status code.\n";
                        break;
                    }

                    orders[idx]->setStatus(static_cast<OrderStatus>(statusChoice));
                    std::cout << "Status changed.\n";
                    break;
                }
                case 6: {
                    if (orders.empty()) { std::cout << "No orders.\n"; break; }
                    int idx;
                    std::cout << "Order index: ";
                    std::cin >> idx;
                    if (idx < 0 || idx >= (int)orders.size()) { std::cout << "Invalid index.\n"; break; }
                    std::cout << *orders[idx] << "\n";
                    break;
                }
                case 7: {
                    std::cout << "Manager turnover: " << manager.getTurnover() << " rub.\n";
                    std::cout << "Total customers: " << manager.getCustomerCount() << "\n";
                    break;
                }
                case 8:
                    std::cout << "Bye.\n";
                    break;
                default:
                    std::cout << "Unknown option.\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
    return 0;
}