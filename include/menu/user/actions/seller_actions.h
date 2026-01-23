#ifndef MENU_USER_ACTIONS_SELLER_ACTIONS_H
#define MENU_USER_ACTIONS_SELLER_ACTIONS_H

#include <string>
#include <vector>
#include "models/item.h"

class SellerActions {
public:
    SellerActions();

    bool AddNewItem(std::vector<Item>& globalItems, const Item& item, int sellerId);

    Item* FindSellerItem(std::vector<Item>& globalItems, int sellerId, int productId);

    bool Replenish(Item& item, int addQty);

    bool ChangePrice(Item& item, double newPrice);

    bool ChangeItemName(Item& item, const std::string& newName);

    bool ChangeCategory(Item& item, const std::string& newCategory);

    bool ChangeDescription(Item& item, const std::string& newDescription);
};

#endif