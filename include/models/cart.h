#ifndef MODELS_CART_H
#define MODELS_CART_H

#include <vector>
#include <string>

struct CartItem {
    int productID;

    int sellerID;

    int quantity;

    double unitPrice;

    std::string itemName;

    CartItem();

    CartItem(int productID, int sellerID, int quantity, double unitPrice, const std::string& itemName);
};

class Cart {
private:
    std::vector<CartItem> items_;

public:
    Cart();

    Cart(const std::vector<CartItem>& items);

    const std::vector<CartItem>& GetItems() const;

    bool AddItem(const CartItem& item);

    bool RemoveItemByProductId(int productId);

    bool RemoveItemsBySellerId(int sellerId);

    bool UpdateQuantity(int productId, int newQuantity);

    void Clear();

    int Size() const;
};

#endif