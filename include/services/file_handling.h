#ifndef SERVICES_FILE_HANDLING_H
#define SERVICES_FILE_HANDLING_H

#include <string>
#include <vector>
#include "models/user.h"
#include "models/item.h"
#include "models/transaction.h"
#include "models/cart.h"

class FileHandling {
public:
    FileHandling();

    static bool LoadUsersText(const std::string& filepath, std::vector<User>& outUsers);

    static bool SaveUsersText(const std::string& filepath, const std::vector<User>& users);

    static bool LoadItemsText(const std::string& filepath, std::vector<Item>& outItems);

    static bool SaveItemsText(const std::string& filepath, const std::vector<Item>& items);

    static bool AppendTransactionText(const std::string& filepath, const Transaction& transaction);

    static bool LoadTransactionsText(const std::string& filepath, std::vector<Transaction>& outTransactions);

    static bool LoadCartText(const std::string& filepath, Cart& outCart);

    static bool SaveCartText(const std::string& filepath, const Cart& cart);
};

#endif