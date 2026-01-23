#include "menu/user/actions/buyer_actions.h"
#include "utils/utils.h"
#include <iostream>
#include <vector>
#include <algorithm>

BuyerActions::BuyerActions() {
}

void BuyerActions::ViewAllProducts(const std::vector<Item>& items) const {
    std::vector<int> sellers;
    for (int i = 0; i < (int)items.size(); ++i) {
        int sid = items[i].GetSellerID();
        bool found = false;
        for (int j = 0; j < (int)sellers.size(); ++j) {
            if (sellers[j] == sid) {
                found = true;
                break;
            }
        }
        if (!found) {
            sellers.push_back(sid);
        }
    }

    std::sort(sellers.begin(), sellers.end());

    for (int si = 0; si < (int)sellers.size(); ++si) {
        int sellerId = sellers[si];
        std::cout << "Seller ID: " << sellerId << "\n";

        std::vector<Item> sellerItems;
        for (int i = 0; i < (int)items.size(); ++i) {
            if (items[i].GetSellerID() == sellerId) {
                sellerItems.push_back(items[i]);
            }
        }

        Utils::PrintItemsTable(sellerItems);
        std::cout << "\n";
    }
}

void BuyerActions::ViewProductsBySeller(const std::vector<Item>& items, int sellerId) const {
    std::vector<Item> sellerItems;
    for (int i = 0; i < (int)items.size(); ++i) {
        if (items[i].GetSellerID() == sellerId) {
            sellerItems.push_back(items[i]);
        }
    }
    Utils::PrintItemsTable(sellerItems);
}

std::vector<Item> BuyerActions::SearchProductsByCategory(const std::vector<Item>& items, const std::string& category) const {
    std::vector<Item> result;
    for (int i = 0; i < (int)items.size(); ++i) {
        if (Utils::ContainsIgnoreCase(items[i].GetCategory(), category)) {
            result.push_back(items[i]);
        }
    }
    return result;
}

std::vector<Item> BuyerActions::SearchProductsByName(const std::vector<Item>& items, const std::string& keyword) const {
    std::vector<Item> result;
    for (int i = 0; i < (int)items.size(); ++i) {
        if (Utils::ContainsIgnoreCase(items[i].GetItemName(), keyword)) {
            result.push_back(items[i]);
        }
    }
    return result;
}

bool BuyerActions::AddToCart(Cart& cart, const Item& item, int quantity) {
    if (quantity <= 0) return false;
    if (quantity > item.GetQuantity()) return false;

    const std::vector<CartItem>& current = cart.GetItems();
    for (int i = 0; i < (int)current.size(); ++i) {
        if (current[i].productID == item.GetProductID()) {
            int newQty = current[i].quantity + quantity;
            if (newQty > item.GetQuantity()) {
                return false;
            }
            CartItem ci(item.GetProductID(), item.GetSellerID(), quantity, item.GetUnitPrice(), item.GetItemName());
            return cart.AddItem(ci);
        }
    }

    if ((int)current.size() >= 10) {
        return false;
    }

    CartItem ci(item.GetProductID(), item.GetSellerID(), quantity, item.GetUnitPrice(), item.GetItemName());
    return cart.AddItem(ci);
}

bool BuyerActions::EditCartQuantity(Cart& cart, int productId, int newQuantity) {
    return cart.UpdateQuantity(productId, newQuantity);
}

bool BuyerActions::RemoveFromCart(Cart& cart, int productId) {
    return cart.RemoveItemByProductId(productId);
}

Transaction BuyerActions::CreateTransactionFromCartItems(const std::vector<CartItem>& items, int buyerId, int sellerId, const Date& date) const {
    std::vector<TransactionItem> titems;
    double total = 0.0;
    for (int i = 0; i < (int)items.size(); ++i) {
        const CartItem& ci = items[i];
        TransactionItem ti(ci.productID, ci.itemName, ci.quantity, ci.unitPrice);
        titems.push_back(ti);
        total = total + (ci.quantity * ci.unitPrice);
    }

    Transaction trans(date, titems, buyerId, sellerId, total);
    return trans;
}