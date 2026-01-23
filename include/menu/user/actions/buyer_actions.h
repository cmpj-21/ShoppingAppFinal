#ifndef MENU_USER_ACTIONS_BUYER_ACTIONS_H
#define MENU_USER_ACTIONS_BUYER_ACTIONS_H

#include <string>
#include <vector>
#include "models/item.h"
#include "models/cart.h"
#include "models/transaction.h"

class BuyerActions {
public:
    BuyerActions();

    void ViewAllProducts(const std::vector<Item>& items) const;

    void ViewProductsBySeller(const std::vector<Item>& items, int sellerId) const;

    std::vector<Item> SearchProductsByCategory(const std::vector<Item>& items, const std::string& category) const;

    std::vector<Item> SearchProductsByName(const std::vector<Item>& items, const std::string& keyword) const;

    bool AddToCart(Cart& cart, const Item& item, int quantity);

    bool EditCartQuantity(Cart& cart, int productId, int newQuantity);

    bool RemoveFromCart(Cart& cart, int productId);

    Transaction CreateTransactionFromCartItems(const std::vector<CartItem>& items, int buyerId, int sellerId, const Date& date) const;
};

#endif