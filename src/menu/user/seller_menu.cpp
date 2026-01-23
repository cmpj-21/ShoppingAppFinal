#include "menu/user/seller_menu.h"
#include "shopping_app.h"
#include "utils/utils.h"
#include <iostream>
#include <string>
#include <vector>

SellerMenu::SellerMenu(ShoppingApp& app, int userId)
    : app_(app), actions_(), loggedInUserId_(userId) {
}

static void ShowSellerProducts(const std::vector<Item>& items, int sellerId) {
    std::vector<Item> sellerItems;
    for (int i = 0; i < (int)items.size(); ++i) {
        if (items[i].GetSellerID() == sellerId) sellerItems.push_back(items[i]);
    }

    for (int i = 0; i < (int)sellerItems.size(); ++i) {
        int minIdx = i;
        for (int j = i + 1; j < (int)sellerItems.size(); ++j) {
            if (sellerItems[j].GetProductID() < sellerItems[minIdx].GetProductID()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Item temp = sellerItems[i];
            sellerItems[i] = sellerItems[minIdx];
            sellerItems[minIdx] = temp;
        }
    }

    Utils::PrintItemsTable(sellerItems);
}

void SellerMenu::Show() {
    while (true) {
        std::cout << "=== SELL MENU (User " << loggedInUserId_ << ") ===\n";
        std::cout << "1. Add New Item\n";
        std::cout << "2. Edit Stock\n";
        std::cout << "3. Show My Products\n";
        std::cout << "4. Show My Low Stock Products\n";
        std::cout << "5. Exit Sell Menu\n";
        std::cout << "Choose option: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string junk;
            std::getline(std::cin, junk);
            std::cout << "Invalid input.\n";
            continue;
        }
        std::string tmp;
        std::getline(std::cin, tmp); 

        if (choice == 1) {
            int productId;
            std::string name, category, description;
            int quantity;
            double unitPrice;

            std::cout << "Enter product ID: ";
            std::cin >> productId;
            std::getline(std::cin, tmp);

            std::cout << "Enter item name: ";
            std::getline(std::cin, name);

            std::cout << "Enter category: ";
            std::getline(std::cin, category);

            std::cout << "Enter description: ";
            std::getline(std::cin, description);

            std::cout << "Enter quantity: ";
            std::cin >> quantity;
            std::cout << "Enter unit price: ";
            std::cin >> unitPrice;
            std::getline(std::cin, tmp);

            if (quantity < 0 || unitPrice <= 0.0) {
                std::cout << "Invalid quantity (must be >=0) or unit price (must be >0).\n";
                continue;
            }

            Item it(productId, name, category, description, quantity, unitPrice, loggedInUserId_);
            bool ok = actions_.AddNewItem(app_.GetItems(), it, loggedInUserId_);
            if (ok) std::cout << "Item added.\n"; else std::cout << "Failed to add item (duplicate ID or seller limit).\n";
        } else if (choice == 2) {
            ShowSellerProducts(app_.GetItems(), loggedInUserId_);
            int productId;
            std::cout << "Enter product ID to edit: ";
            std::cin >> productId;
            std::getline(std::cin, tmp);

            Item* p = actions_.FindSellerItem(app_.GetItems(), loggedInUserId_, productId);
            if (p == 0) {
                std::cout << "Invalid product ID.\n";
                continue;
            }

            while (true) {
                std::cout << "-- Edit Item (Product " << productId << ") --\n";
                std::cout << "1. Replenish\n";
                std::cout << "2. Change Price\n";
                std::cout << "3. Change Item Name\n";
                std::cout << "4. Change Category\n";
                std::cout << "5. Change Description\n";
                std::cout << "6. Finish Editing\n";
                std::cout << "Choose option: ";
                int e = 0;
                if (!(std::cin >> e)) {
                    std::cin.clear();
                    std::string junk;
                    std::getline(std::cin, junk);
                    std::cout << "Invalid input.\n";
                    continue;
                }
                std::getline(std::cin, tmp);

                if (e == 1) {
                    int addQty;
                    std::cout << "Enter quantity to add: ";
                    std::cin >> addQty;
                    std::getline(std::cin, tmp);
                    bool ok = actions_.Replenish(*p, addQty);
                    if (ok) std::cout << "Quantity replenished.\n"; else std::cout << "Failed to replenish.\n";
                } else if (e == 2) {
                    double newPrice;
                    std::cout << "Enter new unit price: ";
                    std::cin >> newPrice;
                    std::getline(std::cin, tmp);
                    bool ok = actions_.ChangePrice(*p, newPrice);
                    if (ok) std::cout << "Price changed.\n"; else std::cout << "Failed to change price.\n";
                } else if (e == 3) {
                    std::string newName;
                    std::cout << "Enter new item name: ";
                    std::getline(std::cin, newName);
                    actions_.ChangeItemName(*p, newName);
                    std::cout << "Name changed.\n";
                } else if (e == 4) {
                    std::string newCat;
                    std::cout << "Enter new category: ";
                    std::getline(std::cin, newCat);
                    actions_.ChangeCategory(*p, newCat);
                    std::cout << "Category changed.\n";
                } else if (e == 5) {
                    std::string newDesc;
                    std::cout << "Enter new description: ";
                    std::getline(std::cin, newDesc);
                    actions_.ChangeDescription(*p, newDesc);
                    std::cout << "Description changed.\n";
                } else if (e == 6) {
                    break;
                } else {
                    std::cout << "Unknown option.\n";
                }
            }

        } else if (choice == 3) {
            ShowSellerProducts(app_.GetItems(), loggedInUserId_);
        } else if (choice == 4) {
            std::vector<Item> low;
            for (int i = 0; i < (int)app_.GetItems().size(); ++i) {
                const Item& it = app_.GetItems()[i];
                if (it.GetSellerID() == loggedInUserId_ && it.GetQuantity() < 5) {
                    low.push_back(it);
                }
            }
            if (low.size() == 0) {
                std::cout << "No low stock products.\n";
            } else {
                int idx = 0;
                while (true) {
                    const Item& it = low[idx];
                    std::cout << "Product ID: " << it.GetProductID() << "\n";
                    std::cout << "Name: " << it.GetItemName() << "\n";
                    std::cout << "Category: " << it.GetCategory() << "\n";
                    std::cout << "Description: " << it.GetDescription() << "\n";
                    std::cout << "Quantity: " << it.GetQuantity() << "\n";
                    std::cout << "Unit Price: " << it.GetUnitPrice() << "\n";
                    std::cout << "[N]ext, [X] exit: ";
                    std::string cmd;
                    std::getline(std::cin, cmd);
                    if (cmd.size() == 0) {
                        std::getline(std::cin, cmd);
                    }
                    if (cmd == "N" || cmd == "n") {
                        idx = idx + 1;
                        if (idx >= (int)low.size()) {
                            idx = 0; 
                        }
                    } else if (cmd == "X" || cmd == "x") {
                        break;
                    } else {
                        std::cout << "Unknown command.\n";
                    }
                }
            }
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Unknown option.\n";
        }
    }
}