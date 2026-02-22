#include "shopping_app.h"
#include "menu/main_menu.h"
#include <iostream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h> 
#else
    #include <sys/stat.h> 
    #include <sys/types.h>
#endif

bool EnsureDirectoryExists(const std::string& path) {
#if defined(_WIN32) || defined(_WIN64)
    int rc = _mkdir(path.c_str());
    if (rc == 0) return true;
    return true; 
#else
    int rc = mkdir(path.c_str(), 0755);
    if (rc == 0) return true;
    return true;
#endif
}

int main() {
    bool okDir = true;
    if (!EnsureDirectoryExists("data")) {
        std::cerr << "Warning: could not ensure 'data' directory exists.\n";
        okDir = false;
    }
    if (!EnsureDirectoryExists("data/carts")) {
        std::cerr << "Warning: could not ensure 'data/carts' directory exists.\n";
        okDir = false;
    }
    if (!okDir) {
        std::cerr << "Warning: directory creation had issues. File saves may fail.\n";
    }

    ShoppingApp app;

    std::string usersPath = "data/Users.txt";
    std::string itemsPath = "data/Items.txt";
    std::string transactionsPath = "data/Transactions.txt";

    bool ok;

    ok = app.LoadUsersFromFile(usersPath);
    if (!ok) {
        std::cout << "Notice: could not load users from " << usersPath << " (file may not exist or is unreadable). Starting with empty users.\n";
    } else {
        std::cout << "Loaded users from " << usersPath << ".\n";
    }

    ok = app.LoadItemsFromFile(itemsPath);
    if (!ok) {
        std::cout << "Notice: could not load items from " << itemsPath << " (file may not exist or is unreadable). Starting with empty items.\n";
    } else {
        std::cout << "Loaded items from " << itemsPath << ".\n";
    }

    ok = app.LoadTransactionsFromFile(transactionsPath);
    if (!ok) {
        std::cout << "Notice: could not load transactions from " << transactionsPath << " (file may not exist or is unreadable). Starting with empty transactions.\n";
    } else {
        std::cout << "Loaded transactions from " << transactionsPath << ".\n";
    }

    MainMenu menu(app);
    menu.Show();

    ok = app.SaveUsersToFile(usersPath);
    if (!ok) {
        std::cerr << "Error: failed to save users to " << usersPath << ".\n";
    } else {
        std::cout << "Saved users to " << usersPath << ".\n";
    }

    ok = app.SaveItemsToFile(itemsPath);
    if (!ok) {
        std::cerr << "Error: failed to save items to " << itemsPath << ".\n";
    } else {
        std::cout << "Saved items to " << itemsPath << ".\n";
    }

    ok = app.SaveTransactionsToFile(transactionsPath);
    if (!ok) {
        std::cerr << "Error: failed to save transactions to " << transactionsPath << ".\n";
    } else {
        std::cout << "Saved transactions to " << transactionsPath << ".\n";
    }

    std::cout << "Program terminated.\n";
    return 0;
}
