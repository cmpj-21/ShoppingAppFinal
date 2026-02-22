#include "menu/admin/admin_menu.h"
#include "shopping_app.h"   

#include <iostream>
#include <string>

AdminMenu::AdminMenu(ShoppingApp& app)
    : app_(app), actions_() {
}

void AdminMenu::Show() {
    std::string password;
    std::cout << "Enter admin password: ";
    std::getline(std::cin, password);

    if (!actions_.Authenticate(password)) {
        std::cout << "Unauthorized access not allowed.\n";
        return;
    }

    while (true) {
        std::cout << "=== ADMIN MENU ===\n";
        std::cout << "1. Show All Users\n";
        std::cout << "2. Show All Sellers\n";
        std::cout << "3. Show Total Sales in Given Duration\n";
        std::cout << "4. Show Sellers Sales in Given Duration\n";
        std::cout << "5. Show Shopaholics in Given Duration\n";
        std::cout << "6. Back to Main Menu\n";
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
            actions_.ShowAllUsers(app_.GetUsers());
        } else if (choice == 2) {
            actions_.ShowAllSellers(app_.GetUsers(), app_.GetItems());
        } else if (choice == 3) {
            int sm, sd, sy, em, ed, ey;
            std::cout << "Enter start date (month day year): ";
            std::cin >> sm >> sd >> sy;
            std::cout << "Enter end date (month day year): ";
            std::cin >> em >> ed >> ey;
            std::getline(std::cin, tmp);
            double total = actions_.ShowTotalSalesInDuration(app_.GetTransactions(), sm, sd, sy, em, ed, ey);
            std::cout << "Total sales in duration: " << total << "\n";
        } else if (choice == 4) {
            int sm, sd, sy, em, ed, ey;
            std::cout << "Enter start date (month day year): ";
            std::cin >> sm >> sd >> sy;
            std::cout << "Enter end date (month day year): ";
            std::cin >> em >> ed >> ey;
            std::getline(std::cin, tmp);
            actions_.ShowSellersSales(app_.GetTransactions(), sm, sd, sy, em, ed, ey);
        } else if (choice == 5) {
            int sm, sd, sy, em, ed, ey;
            std::cout << "Enter start date (month day year): ";
            std::cin >> sm >> sd >> sy;
            std::cout << "Enter end date (month day year): ";
            std::cin >> em >> ed >> ey;
            std::getline(std::cin, tmp);
            actions_.ShowShopaholics(app_.GetTransactions(), sm, sd, sy, em, ed, ey);
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Unknown option.\n";
        }
    }
}