#include "models/item.h"

Item::Item() {
    productID_ = 0;
    itemName_ = "";
    category_ = "";
    description_ = "";
    quantity_ = 0;
    unitPrice_ = 0.0;
    sellerID_ = 0;
}

Item::Item(int productID, const std::string& itemName, const std::string& category,
           const std::string& description, int quantity, double unitPrice, int sellerID) {
    productID_ = productID;

    if ((int)itemName.size() > 20) {
        itemName_ = itemName.substr(0, 20);
    } else {
        itemName_ = itemName;
    }

    if ((int)category.size() > 15) {
        category_ = category.substr(0, 15);
    } else {
        category_ = category;
    }

    if ((int)description.size() > 30) {
        description_ = description.substr(0, 30);
    } else {
        description_ = description;
    }

    if (quantity < 0) {
        quantity_ = 0;
    } else {
        quantity_ = quantity;
    }

    if (unitPrice < 0.0) {
        unitPrice_ = 0.0;
    } else {
        unitPrice_ = unitPrice;
    }

    sellerID_ = sellerID;
}

int Item::GetProductID() const {
    return productID_;
}

const std::string& Item::GetItemName() const {
    return itemName_;
}

const std::string& Item::GetCategory() const {
    return category_;
}

const std::string& Item::GetDescription() const {
    return description_;
}

int Item::GetQuantity() const {
    return quantity_;
}

double Item::GetUnitPrice() const {
    return unitPrice_;
}

int Item::GetSellerID() const {
    return sellerID_;
}

void Item::SetProductID(int id) {
    productID_ = id;
}

void Item::SetItemName(const std::string& name) {
    if ((int)name.size() > 20) {
        itemName_ = name.substr(0, 20);
    } else {
        itemName_ = name;
    }
}

void Item::SetCategory(const std::string& category) {
    if ((int)category.size() > 15) {
        category_ = category.substr(0, 15);
    } else {
        category_ = category;
    }
}

void Item::SetDescription(const std::string& desc) {
    if ((int)desc.size() > 30) {
        description_ = desc.substr(0, 30);
    } else {
        description_ = desc;
    }
}

void Item::SetQuantity(int qty) {
    if (qty < 0) {
        quantity_ = 0;
    } else {
        quantity_ = qty;
    }
}

void Item::SetUnitPrice(double price) {
    if (price < 0.0) {
        unitPrice_ = 0.0;
    } else {
        unitPrice_ = price;
    }
}

void Item::SetSellerID(int id) {
    sellerID_ = id;
}