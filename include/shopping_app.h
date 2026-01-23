#ifndef SHOPPING_APP_H
#define SHOPPING_APP_H

#include <string>
#include <vector>

#include "models/user.h"
#include "models/item.h"
#include "models/transaction.h"

class ShoppingApp {
private:
    std::vector<User> users_;

    std::vector<Item> items_;

    std::vector<Transaction> transactions_;

public:
    ShoppingApp();

    ShoppingApp(const std::string& dataDirectory);

    bool LoadUsersFromFile(const std::string& filepath);

    bool SaveUsersToFile(const std::string& filepath) const;

    bool LoadItemsFromFile(const std::string& filepath);

    bool SaveItemsToFile(const std::string& filepath) const;

    bool LoadTransactionsFromFile(const std::string& filepath);

    bool SaveTransactionsToFile(const std::string& filepath) const;

    std::vector<User>& GetUsers();

    const std::vector<User>& GetUsers() const;

    std::vector<Item>& GetItems();

    const std::vector<Item>& GetItems() const;

    std::vector<Transaction>& GetTransactions();

    const std::vector<Transaction>& GetTransactions() const;

    bool RegisterUser(const User& user);

    User* FindUserById(int userId);

    const User* FindUserById(int userId) const;

    bool AddItem(const Item& item);

    Item* FindItemByProductId(int productId);

    bool AddTransaction(const Transaction& transaction);
};

#endif
