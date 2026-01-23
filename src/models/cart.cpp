#include "models/cart.h"
#include <algorithm> 

CartItem::CartItem() {
    productID = 0;
    sellerID = 0;
    quantity = 0;
    unitPrice = 0.0;
    itemName = "";
}

CartItem::CartItem(int productID_, int sellerID_, int quantity_, double unitPrice_, const std::string& itemName_) {
    productID = productID_;
    sellerID = sellerID_;
    if (quantity_ < 0) {
        quantity = 0;
    } else {
        quantity = quantity_;
    }
    if (unitPrice_ < 0.0) {
        unitPrice = 0.0;
    } else {
        unitPrice = unitPrice_;
    }
    itemName = itemName_;
}

Cart::Cart() {
    items_.clear();
}

Cart::Cart(const std::vector<CartItem>& items) {
    items_ = items;
}

const std::vector<CartItem>& Cart::GetItems() const {
    return items_;
}

bool Cart::AddItem(const CartItem& item) {
    if (item.quantity <= 0) {
        return false; 
    }

    for (int i = 0; i < (int)items_.size(); ++i) {
        if (items_[i].productID == item.productID) {
            items_[i].quantity = items_[i].quantity + item.quantity;
            return true;
        }
    }

    if ((int)items_.size() >= 10) {
        return false; 
    }

    items_.push_back(item);
    return true;
}

bool Cart::RemoveItemByProductId(int productId) {
    int originalSize = (int)items_.size();

    items_.erase(std::remove_if(items_.begin(), items_.end(),
                                [productId](const CartItem& ci) {
                                    return ci.productID == productId;
                                }),
                 items_.end());

    return (int)items_.size() != originalSize;
}

bool Cart::RemoveItemsBySellerId(int sellerId) {
    int originalSize = (int)items_.size();

    items_.erase(std::remove_if(items_.begin(), items_.end(),
                                [sellerId](const CartItem& ci) {
                                    return ci.sellerID == sellerId;
                                }),
                 items_.end());

    return (int)items_.size() != originalSize;
}

bool Cart::UpdateQuantity(int productId, int newQuantity) {
    for (int i = 0; i < (int)items_.size(); ++i) {
        if (items_[i].productID == productId) {
            if (newQuantity <= 0) {
                items_.erase(items_.begin() + i);
            } else {
                items_[i].quantity = newQuantity;
            }
            return true;
        }
    }
    return false; 
}

void Cart::Clear() {
    items_.clear();
}

int Cart::Size() const {
    return (int)items_.size();
}