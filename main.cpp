#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "Warehouse.h"
#include "Factories.h"

void printMenu() {
    std::cout << "\n=== Warehouse Manager ===\n";
    std::cout << "1.  Create warehouse\n";
    std::cout << "2.  Add Smartphone\n";
    std::cout << "3.  Add Laptop\n";
    std::cout << "4.  Add TShirt\n";
    std::cout << "5.  Add Jacket\n";
    std::cout << "6.  Add Milk\n";
    std::cout << "7.  Add Bread\n";
    std::cout << "8.  Remove by ID\n";
    std::cout << "9.  Remove by index\n";
    std::cout << "10. Find by ID\n";
    std::cout << "11. Find by category\n";
    std::cout << "12. Find by price\n";
    std::cout << "13. Copy warehouse\n";
    std::cout << "14. Move warehouse\n";
    std::cout << "15. Transfer product to another warehouse\n";
    std::cout << "16. Print all products\n";
    std::cout << "17. Exit\n";
    std::cout << "Choose: ";
}

std::unique_ptr<Product> createFromFactory(ProductFactory& factory) {
    std::string name;
    int price, qty;
    double weight;
    std::cout << "Name: "; std::cin >> name;
    std::cout << "Price: "; std::cin >> price;
    std::cout << "Quantity: "; std::cin >> qty;
    std::cout << "Weight: "; std::cin >> weight;
    return factory.createProduct(name, price, qty, weight);
}

int main() {
    std::vector<std::unique_ptr<Warehouse>> warehouses;
    SmartphoneFactory phoneF;
    LaptopFactory laptopF;
    TShirtFactory tshirtF;
    JacketFactory jacketF;
    MilkFactory milkF;
    BreadFactory breadF;

    int choice = 0;
    while (choice != 17) {
        printMenu();
        std::cin >> choice;
        try {
            switch (choice) {
            case 1: {
                size_t size;
                std::cout << "Max size: "; std::cin >> size;
                warehouses.push_back(std::make_unique<Warehouse>(size));
                std::cout << "Warehouse #" << warehouses.size() - 1 << " created.\n";
                break;
            }
            case 2: case 3: case 4: case 5: case 6: case 7: {
                if (warehouses.empty()) { std::cout << "No warehouse. Create first.\n"; break; }
                int widx;
                std::cout << "Warehouse index (0.." << warehouses.size() - 1 << "): "; std::cin >> widx;
                if (widx < 0 || widx >= (int)warehouses.size()) { std::cout << "Invalid index.\n"; break; }
                ProductFactory* f = nullptr;
                if (choice == 2) f = &phoneF;
                else if (choice == 3) f = &laptopF;
                else if (choice == 4) f = &tshirtF;
                else if (choice == 5) f = &jacketF;
                else if (choice == 6) f = &milkF;
                else f = &breadF;
                auto p = createFromFactory(*f);
                if (warehouses[widx]->addProduct(std::move(p)))
                    std::cout << "Added.\n";
                else
                    std::cout << "Warehouse is full.\n";
                break;
            }
            case 8: {
                if (warehouses.empty()) break;
                int widx, id;
                std::cout << "Warehouse index: "; std::cin >> widx;
                std::cout << "ID: "; std::cin >> id;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    warehouses[widx]->removeById(id);
                    std::cout << "Removed.\n";
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 9: {
                if (warehouses.empty()) break;
                int widx; size_t idx;
                std::cout << "Warehouse index: "; std::cin >> widx;
                std::cout << "Index: "; std::cin >> idx;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    warehouses[widx]->removeByIndex(idx);
                    std::cout << "Removed.\n";
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 10: {
                if (warehouses.empty()) break;
                int widx, id;
                std::cout << "Warehouse index: "; std::cin >> widx;
                std::cout << "ID: "; std::cin >> id;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    auto p = warehouses[widx]->findById(id);
                    if (p) std::cout << "Found: ID=" << p->getId()
                        << ", category=" << p->getCategory()
                        << ", price=" << p->getPrice().getValue()
                        << ", qty=" << p->getQuantity().getValue() << "\n";
                    else std::cout << "Not found.\n";
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 11: {
                if (warehouses.empty()) break;
                int widx; std::string cat;
                std::cout << "Warehouse index: "; std::cin >> widx;
                std::cout << "Category (electronics/clothing/food): "; std::cin >> cat;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    auto list = warehouses[widx]->findByCategory(cat);
                    std::cout << "Found " << list.size() << " items.\n";
                    for (auto* p : list)
                        std::cout << "  ID=" << p->getId()
                        << ", price=" << p->getPrice().getValue() << "\n";
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 12: {
                if (warehouses.empty()) break;
                int widx, price;
                std::cout << "Warehouse index: "; std::cin >> widx;
                std::cout << "Price: "; std::cin >> price;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    auto list = warehouses[widx]->findByPrice(Price(price));
                    std::cout << "Found " << list.size() << " items.\n";
                    for (auto* p : list)
                        std::cout << "  ID=" << p->getId()
                        << ", category=" << p->getCategory() << "\n";
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 13: {
                if (warehouses.empty()) break;
                int widx;
                std::cout << "Warehouse index to copy: "; std::cin >> widx;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    warehouses.push_back(std::make_unique<Warehouse>(*warehouses[widx]));
                    std::cout << "Copied to warehouse #" << warehouses.size() - 1 << "\n";
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 14: {
                if (warehouses.empty()) break;
                int widx;
                std::cout << "Warehouse index to move: "; std::cin >> widx;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    warehouses.push_back(std::make_unique<Warehouse>(std::move(*warehouses[widx])));
                    std::cout << "Moved to warehouse #" << warehouses.size() - 1
                        << ", original size: " << warehouses[widx]->size() << "\n";
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 15: {
                int from, to, id;
                std::cout << "From warehouse index: "; std::cin >> from;
                std::cout << "To warehouse index: "; std::cin >> to;
                std::cout << "Product ID: "; std::cin >> id;
                if (from >= 0 && from < (int)warehouses.size() &&
                    to >= 0 && to < (int)warehouses.size()) {
                    bool ok = warehouses[from]->moveProductTo(id, *warehouses[to]);
                    std::cout << (ok ? "Transferred.\n" : "Failed.\n");
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 16: {
                if (warehouses.empty()) break;
                int widx;
                std::cout << "Warehouse index: "; std::cin >> widx;
                if (widx >= 0 && widx < (int)warehouses.size()) {
                    std::cout << "Products in warehouse #" << widx << ":\n";
                    for (auto it = warehouses[widx]->begin(); it != warehouses[widx]->end(); ++it) {
                        std::cout << "  ID=" << it->getId()
                            << ", category=" << it->getCategory()
                            << ", price=" << it->getPrice().getValue()
                            << ", qty=" << it->getQuantity().getValue() << "\n";
                    }
                }
                else std::cout << "Invalid index.\n";
                break;
            }
            case 17:
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
    return 0;
}