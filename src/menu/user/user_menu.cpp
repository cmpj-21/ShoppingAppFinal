#include <iostream>
#include <string>

#include "menu/user/user_menu.h"
#include "menu/user/buyer_menu.h"
#include "menu/user/seller_menu.h"

UserMenu::UserMenu(ShoppingApp& app)
    : app_(app), userActions_() {
}

void UserMenu::Show() {
    std::cout << "--- User Login ---\n";
    int userId = 0;
    std::string password;
    std::cout << "Enter user ID: ";
    if (!(std::cin >> userId)) {
        std::cin.clear();
        std::string junk;
        std::getline(std::cin, junk);
        std::cout << "Invalid user ID.\n";
        return;
    }
    std::string tmp;
    std::getline(std::cin, tmp);

    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    bool ok = userActions_.Login(app_.GetUsers(), userId, password);
    if (!ok) {
        std::cout << "Login failed. Returning to main menu.\n";
        return;
    }

    std::string loggedUserName = "";
    const std::vector<User>& allUsers = app_.GetUsers();
    for (int i = 0; i < (int)allUsers.size(); ++i) {
        if (allUsers[i].GetUserID() == userId) {
            loggedUserName = allUsers[i].GetName();
            break;
        }
    }

    if (loggedUserName.empty()) {
        loggedUserName = "User";
    }

    while (true) {
        std::cout << "\n=== USER MENU (ID " << userId << ") ===\n";
        std::cout << "Welcome, " << loggedUserName << "!\n\n";

        std::cout << "1. Sell Menu\n";
        std::cout << "2. Buy Menu\n";
        std::cout << "3. Exit User Menu\n";
        std::cout << "Choose option: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string junk;
            std::getline(std::cin, junk);
            std::cout << "Invalid input.\n";
            continue;
        }
        std::getline(std::cin, tmp);

        if (choice == 1) {
            SellerMenu sm(app_, userId);
            sm.Show();
        } else if (choice == 2) {
            BuyerMenu bm(app_, userId);
            bm.Show();
        } else if (choice == 3) {
            std::cout << "Goodbye, " << loggedUserName << ". Returning to main menu.\n";
            break;
        } else {
            std::cout << "Unknown option.\n";
        }
    }
}