#include "menu/main_menu.h"
#include "menu/admin/admin_menu.h"
#include "menu/user/user_menu.h"
#include <iostream>
#include <string>

MainMenu::MainMenu(ShoppingApp& app)
    : app_(app) {
}

void MainMenu::Show() {
    while (true) {
        std::cout << "=== MAIN MENU ===\n";
        std::cout << "1. Register as a User\n";
        std::cout << "2. User Menu (login)\n";
        std::cout << "3. Admin Menu\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose option: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string junk;
            std::getline(std::cin, junk);
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        std::string tmp;
        std::getline(std::cin, tmp);

        if (choice == 1) {
            std::cout << "--- Register ---\n";
            int userId = 0;
            std::cout << "Enter numeric user ID: ";
            std::cin >> userId;
            std::getline(std::cin, tmp); 

            std::string password;
            std::cout << "Enter password (no spaces recommended): ";
            std::getline(std::cin, password);

            std::string name;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);

            std::string address;
            std::cout << "Enter address: ";
            std::getline(std::cin, address);

            long long contact = 0;
            std::cout << "Enter contact number (numeric): ";
            std::cin >> contact;
            std::getline(std::cin, tmp); 

            User u(userId, password, name, address, contact);
            bool ok = app_.RegisterUser(u);
            if (ok) {
                std::cout << "Registration successful.\n";
            } else {
                std::cout << "Registration failed (duplicate ID or user limit).\n";
            }
        } else if (choice == 2) {
            UserMenu um(app_);
            um.Show();
        } else if (choice == 3) {
            AdminMenu am(app_);
            am.Show();
        } else if (choice == 4) {
            std::cout << "Exiting program. Saving data...\n";
            app_.SaveUsersToFile("../../data/Users.txt");
            app_.SaveItemsToFile("../../data/Items.txt");
            app_.SaveTransactionsToFile("../../data/Transactions.txt");
            break;
        } else {
            std::cout << "Unknown option. Try again.\n";
        }
    }
}