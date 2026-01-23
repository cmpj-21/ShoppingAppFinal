#include "shopping_app.h"
#include "services/file_handling.h"
#include <fstream>   

ShoppingApp::ShoppingApp() {
}

ShoppingApp::ShoppingApp(const std::string& dataDirectory) {
}

bool ShoppingApp::LoadUsersFromFile(const std::string& filepath) {
    return FileHandling::LoadUsersText(filepath, users_);
}

bool ShoppingApp::SaveUsersToFile(const std::string& filepath) const {
    return FileHandling::SaveUsersText(filepath, users_);
}

bool ShoppingApp::LoadItemsFromFile(const std::string& filepath) {
    return FileHandling::LoadItemsText(filepath, items_);
}

bool ShoppingApp::SaveItemsToFile(const std::string& filepath) const {
    return FileHandling::SaveItemsText(filepath, items_);
}

bool ShoppingApp::LoadTransactionsFromFile(const std::string& filepath) {
    return FileHandling::LoadTransactionsText(filepath, transactions_);
}

bool ShoppingApp::SaveTransactionsToFile(const std::string& filepath) const {
    std::ofstream out(filepath.c_str());
    if (!out.is_open()) {
        return false;
    }
    out.close();

    for (int i = 0; i < (int)transactions_.size(); ++i) {
        if (!FileHandling::AppendTransactionText(filepath, transactions_[i])) {
        }
    }
    return true;
}

std::vector<User>& ShoppingApp::GetUsers() {
    return users_;
}

const std::vector<User>& ShoppingApp::GetUsers() const {
    return users_;
}

std::vector<Item>& ShoppingApp::GetItems() {
    return items_;
}

const std::vector<Item>& ShoppingApp::GetItems() const {
    return items_;
}

std::vector<Transaction>& ShoppingApp::GetTransactions() {
    return transactions_;
}

const std::vector<Transaction>& ShoppingApp::GetTransactions() const {
    return transactions_;
}

bool ShoppingApp::RegisterUser(const User& user) {
    static const int MAX_USERS = 100;
    if ((int)users_.size() >= MAX_USERS) {
        return false;
    }

    for (size_t i = 0; i < users_.size(); ++i) {
        if (users_[i].GetUserID() == user.GetUserID()) {
            return false;
        }
    }

    users_.push_back(user);
    return true;
}

const User* ShoppingApp::FindUserById(int userId) const {
    for (size_t i = 0; i < users_.size(); ++i) {
        if (users_[i].GetUserID() == userId) {
            return &users_[i];
        }
    }
    return nullptr;
}

User* ShoppingApp::FindUserById(int userId) {
    return const_cast<User*>(const_cast<const ShoppingApp*>(this)->FindUserById(userId));
}

bool ShoppingApp::AddItem(const Item& item) {
    static const int MAX_ITEMS_PER_SELLER = 20;

    for (size_t i = 0; i < items_.size(); ++i) {
        if (items_[i].GetProductID() == item.GetProductID()) {
            return false;
        }
    }

    size_t sellerItemCount = 0;
    for (size_t i = 0; i < items_.size(); ++i) {
        if (items_[i].GetSellerID() == item.GetSellerID()) {
            ++sellerItemCount;
        }
    }
    if (sellerItemCount >= MAX_ITEMS_PER_SELLER) {
        return false;
    }

    items_.push_back(item);
    return true;
}

Item* ShoppingApp::FindItemByProductId(int productId) {
    for (size_t i = 0; i < items_.size(); ++i) {
        if (items_[i].GetProductID() == productId) {
            return &items_[i];
        }
    }
    return nullptr;
}

bool ShoppingApp::AddTransaction(const Transaction& transaction) {
    static const size_t MAX_ITEMS_PER_TRANSACTION = 5;

    const auto& transactionItems = transaction.GetItems();
    if (transactionItems.size() > MAX_ITEMS_PER_TRANSACTION) {
        return false;
    }

    if (transaction.GetBuyerID() == transaction.GetSellerID()) {
        return false;
    }

    std::vector<size_t> itemIndices;
    std::vector<int> remainingQuantities;

    for (const auto& ti : transactionItems) {
        int pid = ti.productID;
        int needQty = ti.quantity;

        size_t foundIndex = items_.size();
        for (size_t j = 0; j < items_.size(); ++j) {
            if (items_[j].GetProductID() == pid) {
                foundIndex = j;
                break;
            }
        }
        if (foundIndex == items_.size()) {
            return false;
        }

        if (items_[foundIndex].GetSellerID() != transaction.GetSellerID()) {
            return false;
        }

        int avail = items_[foundIndex].GetQuantity();
        if (needQty <= 0 || avail < needQty) {
            return false;
        }

        itemIndices.push_back(foundIndex);
        remainingQuantities.push_back(avail - needQty);
    }

    for (size_t i = 0; i < itemIndices.size(); ++i) {
        size_t idx = itemIndices[i];
        items_[idx].SetQuantity(remainingQuantities[i]);
    }

    transactions_.push_back(transaction);
    return true;
}
