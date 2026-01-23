#include "menu/user/buyer_menu.h"
#include "services/file_handling.h"
#include "shopping_app.h"
#include "utils/utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

BuyerMenu::BuyerMenu(ShoppingApp& app, int userId)
    : app_(app), actions_(), loggedInUserId_(userId) {
}

static void PrintCart(const Cart& cart) {
    const std::vector<CartItem>& items = cart.GetItems();
    if (items.empty()) {
        std::cout << "Cart is empty.\n";
        return;
    }

    const std::string hdr1 = "ProductID";
    const std::string hdr2 = "SellerID";
    const std::string hdr3 = "Qty";
    const std::string hdr4 = "UnitPrice";
    const std::string hdr5 = "Name";

    size_t w1 = hdr1.size();
    size_t w2 = hdr2.size();
    size_t w3 = hdr3.size();
    size_t w4 = hdr4.size();
    size_t w5 = hdr5.size();

    auto FormatPrice = [](double price) -> std::string {
        std::ostringstream oss;
        oss.setf(std::ios::fixed);
        oss.precision(2);
        oss << price;
        return oss.str();
    };

    for (size_t i = 0; i < items.size(); ++i) {
        const CartItem& ci = items[i];
        std::string s1 = std::to_string(ci.productID);
        if (s1.size() > w1) w1 = s1.size();

        std::string s2 = std::to_string(ci.sellerID);
        if (s2.size() > w2) w2 = s2.size();

        std::string s3 = std::to_string(ci.quantity);
        if (s3.size() > w3) w3 = s3.size();

        std::string s4 = FormatPrice(ci.unitPrice);
        if (s4.size() > w4) w4 = s4.size();

        const std::string& s5 = ci.itemName;
        if (s5.size() > w5) w5 = s5.size();
    }

    const size_t COLUMN_SPACING = 3;
    std::string gap = std::string(COLUMN_SPACING, ' ');

    std::string header = Utils::RightJustify(hdr1, w1) + gap
                       + Utils::RightJustify(hdr2, w2) + gap
                       + Utils::RightJustify(hdr3, w3) + gap
                       + Utils::RightJustify(hdr4, w4) + gap
                       + Utils::LeftJustify(hdr5, w5);

    std::cout << header << "\n";

    size_t sepLen = w1 + w2 + w3 + w4 + w5 + (COLUMN_SPACING * 4);
    std::string sep(sepLen, '-');
    std::cout << sep << "\n";

    for (size_t i = 0; i < items.size(); ++i) {
        const CartItem& ci = items[i];
        std::string col1 = std::to_string(ci.productID);
        std::string col2 = std::to_string(ci.sellerID);
        std::string col3 = std::to_string(ci.quantity);
        std::string col4 = FormatPrice(ci.unitPrice);
        std::string col5 = ci.itemName;

        std::string line = Utils::RightJustify(col1, w1) + gap
                         + Utils::RightJustify(col2, w2) + gap
                         + Utils::RightJustify(col3, w3) + gap
                         + Utils::RightJustify(col4, w4) + gap
                         + Utils::LeftJustify(col5, w5);
        std::cout << line << "\n";
    }
}

void BuyerMenu::Show() {
    Cart cart;
    std::string cartPath = "../data/carts/" + std::to_string(loggedInUserId_) + ".bag";
    FileHandling::LoadCartText(cartPath, cart);

    while (true) {
        std::cout << "=== BUY MENU (User " << loggedInUserId_ << ") ===\n";
        std::cout << "1. View all products\n";
        std::cout << "2. Show all products by specific seller\n";
        std::cout << "3. Search products by category\n";
        std::cout << "4. Search products by name\n";
        std::cout << "5. Add to cart\n";
        std::cout << "6. Edit cart\n";
        std::cout << "7. Check out\n";
        std::cout << "8. Exit Buy Menu\n";
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
            actions_.ViewAllProducts(app_.GetItems());
        } else if (choice == 2) {
            int sellerId;
            std::cout << "Enter seller ID: ";
            std::cin >> sellerId;
            std::getline(std::cin, tmp);
            actions_.ViewProductsBySeller(app_.GetItems(), sellerId);
        } else if (choice == 3) {
            std::string category;
            std::cout << "Enter category (keyword): ";
            std::getline(std::cin, category);
            std::vector<Item> found = actions_.SearchProductsByCategory(app_.GetItems(), category);
            Utils::PrintItemsTable(found);
        } else if (choice == 4) {
            std::string keyword;
            std::cout << "Enter product name keyword: ";
            std::getline(std::cin, keyword);
            std::vector<Item> found = actions_.SearchProductsByName(app_.GetItems(), keyword);
            Utils::PrintItemsTable(found);
        } else if (choice == 5) {
            int productId;
            int qty;
            std::cout << "Enter product ID to add: ";
            std::cin >> productId;
            std::cout << "Enter quantity: ";
            std::cin >> qty;
            std::getline(std::cin, tmp);

            Item* it = app_.FindItemByProductId(productId);
            if (it == 0) {
                std::cout << "Invalid product ID.\n";
            } else if (it->GetSellerID() == loggedInUserId_) {
                std::cout << "Cannot buy your own product.\n";
            } else {
                bool ok = actions_.AddToCart(cart, *it, qty);
                if (ok) {
                    std::cout << "Added to cart.\n";
                } else {
                    std::cout << "Failed to add to cart (insufficient stock or cart full).\n";
                }
            }
        } else if (choice == 6) {
            while (true) {
                std::cout << "--- Edit Cart ---\n";
                PrintCart(cart);
                std::cout << "1. Remove all items from seller\n";
                std::cout << "2. Remove specific item\n";
                std::cout << "3. Edit quantity\n";
                std::cout << "4. Finish Edit Cart\n";
                std::cout << "Choose option: ";
                int echoice = 0;
                if (!(std::cin >> echoice)) {
                    std::cin.clear();
                    std::string junk;
                    std::getline(std::cin, junk);
                    std::cout << "Invalid input.\n";
                    continue;
                }
                std::getline(std::cin, tmp);
                if (echoice == 1) {
                    int sellerId;
                    std::cout << "Enter seller ID to remove: ";
                    std::cin >> sellerId;
                    std::getline(std::cin, tmp);
                    bool removed = cart.RemoveItemsBySellerId(sellerId);
                    if (removed) std::cout << "Removed items from that seller.\n";
                    else std::cout << "No items found for that seller in cart.\n";
                } else if (echoice == 2) {
                    int pid;
                    std::cout << "Enter product ID to remove: ";
                    std::cin >> pid;
                    std::getline(std::cin, tmp);
                    bool removed = cart.RemoveItemByProductId(pid);
                    if (removed) std::cout << "Item removed.\n"; else std::cout << "Item not found in cart.\n";
                } else if (echoice == 3) {
                    int pid, newQ;
                    std::cout << "Enter product ID: ";
                    std::cin >> pid;
                    std::cout << "Enter new quantity: ";
                    std::cin >> newQ;
                    std::getline(std::cin, tmp);
                    bool ok = actions_.EditCartQuantity(cart, pid, newQ);
                    if (ok) std::cout << "Updated quantity.\n"; else std::cout << "Failed to update (item not found).\n";
                } else if (echoice == 4) {
                    break;
                } else {
                    std::cout << "Unknown option.\n";
                }
            }
        } else if (choice == 7) {
            std::cout << "--- Checkout ---\n";
            int month, day, year;
            std::cout << "Enter date (month day year): ";
            std::cin >> month >> day >> year;
            std::getline(std::cin, tmp);

            while (true) {
                std::cout << "1. All\n";
                std::cout << "2. By a specific seller\n";
                std::cout << "3. Specific item\n";
                std::cout << "4. Exit Checkout\n";
                std::cout << "Choose option: ";
                int c = 0;
                if (!(std::cin >> c)) {
                    std::cin.clear();
                    std::string junk;
                    std::getline(std::cin, junk);
                    std::cout << "Invalid input.\n";
                    continue;
                }
                std::getline(std::cin, tmp);

                if (c == 1) {
                    std::vector<CartItem> items = cart.GetItems();
                    std::vector<int> sellers;
                    for (int i = 0; i < (int)items.size(); ++i) {
                        int sid = items[i].sellerID;
                        bool found = false;
                        for (int j = 0; j < (int)sellers.size(); ++j) {
                            if (sellers[j] == sid) { found = true; break; }
                        }
                        if (!found) sellers.push_back(sid);
                    }

                    for (int si = 0; si < (int)sellers.size(); ++si) {
                        int sid = sellers[si];
                        std::vector<CartItem> group;
                        for (int i = 0; i < (int)items.size(); ++i) {
                            if (items[i].sellerID == sid) group.push_back(items[i]);
                        }

                        Date date(month, day, year);
                        Transaction t = actions_.CreateTransactionFromCartItems(group, loggedInUserId_, sid, date);

                        bool ok = app_.AddTransaction(t);
                        if (ok) {
                            cart.RemoveItemsBySellerId(sid);
                            std::cout << "Transaction completed for seller " << sid << ".\n";
                        } else {
                            std::cout << "Transaction failed for seller " << sid << ".\n";
                        }
                    }
                } else if (c == 2) {
                    int sid;
                    std::cout << "Enter seller ID to checkout: ";
                    std::cin >> sid;
                    std::getline(std::cin, tmp);

                    std::vector<CartItem> items = cart.GetItems();
                    std::vector<CartItem> group;
                    for (int i = 0; i < (int)items.size(); ++i) {
                        if (items[i].sellerID == sid) group.push_back(items[i]);
                    }
                    if (group.size() == 0) {
                        std::cout << "No items from that seller in cart.\n";
                    } else {
                        Date date(month, day, year);
                        Transaction t = actions_.CreateTransactionFromCartItems(group, loggedInUserId_, sid, date);
                        bool ok = app_.AddTransaction(t);
                        if (ok) {
                            cart.RemoveItemsBySellerId(sid);
                            std::cout << "Transaction completed for seller " << sid << ".\n";
                        } else {
                            std::cout << "Transaction failed.\n";
                        }
                    }
                } else if (c == 3) {
                    int pid;
                    std::cout << "Enter product ID to checkout: ";
                    std::cin >> pid;
                    std::getline(std::cin, tmp);

                    std::vector<CartItem> items = cart.GetItems();
                    bool found = false;
                    CartItem chosen;
                    for (int i = 0; i < (int)items.size(); ++i) {
                        if (items[i].productID == pid) {
                            found = true;
                            chosen = items[i];
                            break;
                        }
                    }
                    if (!found) {
                        std::cout << "Item not in cart.\n";
                    } else {
                        std::vector<CartItem> group;
                        group.push_back(chosen);
                        Date date(month, day, year);
                        Transaction t = actions_.CreateTransactionFromCartItems(group, loggedInUserId_, chosen.sellerID, date);
                        bool ok = app_.AddTransaction(t);
                        if (ok) {
                            cart.RemoveItemByProductId(pid);
                            std::cout << "Transaction completed for product " << pid << ".\n";
                        } else {
                            std::cout << "Transaction failed.\n";
                        }
                    }
                } else if (c == 4) {
                    break;
                } else {
                    std::cout << "Unknown option.\n";
                }
            }
        } else if (choice == 8) {
            FileHandling::SaveCartText(cartPath, cart);
            std::cout << "Cart saved. Exiting Buy Menu.\n";
            break;
        } else {
            std::cout << "Unknown option.\n";
        }
    }
}