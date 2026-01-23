#include "menu/user/actions/seller_actions.h"

SellerActions::SellerActions() {
}

bool SellerActions::AddNewItem(std::vector<Item>& globalItems, const Item& item, int sellerId) {
    for (int i = 0; i < (int)globalItems.size(); ++i) {
        if (globalItems[i].GetProductID() == item.GetProductID()) {
            return false; 
        }
    }

    int count = 0;
    for (int i = 0; i < (int)globalItems.size(); ++i) {
        if (globalItems[i].GetSellerID() == sellerId) {
            count = count + 1;
        }
    }
    if (count >= 20) {
        return false; 
    }

    Item newItem = item;
    newItem.SetSellerID(sellerId);
    globalItems.push_back(newItem);
    return true;
}

Item* SellerActions::FindSellerItem(std::vector<Item>& globalItems, int sellerId, int productId) {
    for (int i = 0; i < (int)globalItems.size(); ++i) {
        if (globalItems[i].GetSellerID() == sellerId && globalItems[i].GetProductID() == productId) {
            return &globalItems[i];
        }
    }
    return 0;
}

bool SellerActions::Replenish(Item& item, int addQty) {
    if (addQty < 0) return false;
    int newQty = item.GetQuantity() + addQty;
    item.SetQuantity(newQty);
    return true;
}

bool SellerActions::ChangePrice(Item& item, double newPrice) {
    if (newPrice < 0.0) return false;
    item.SetUnitPrice(newPrice);
    return true;
}

bool SellerActions::ChangeItemName(Item& item, const std::string& newName) {
    item.SetItemName(newName);
    return true;
}

bool SellerActions::ChangeCategory(Item& item, const std::string& newCategory) {
    item.SetCategory(newCategory);
    return true;
}

bool SellerActions::ChangeDescription(Item& item, const std::string& newDescription) {
    item.SetDescription(newDescription);
    return true;
}