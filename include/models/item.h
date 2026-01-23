#ifndef MODELS_ITEM_H
#define MODELS_ITEM_H

#include <string>

class Item {
private:
    int productID_;

    std::string itemName_;

    std::string category_;

    std::string description_;

    int quantity_;

    double unitPrice_;

    int sellerID_;

public:
    Item();

    Item(int productID, const std::string& itemName, const std::string& category,
         const std::string& description, int quantity, double unitPrice, int sellerID);

    int GetProductID() const;

    const std::string& GetItemName() const;

    const std::string& GetCategory() const;

    const std::string& GetDescription() const;

    int GetQuantity() const;

    double GetUnitPrice() const;

    int GetSellerID() const;

    void SetProductID(int id);

    void SetItemName(const std::string& name);

    void SetCategory(const std::string& category);

    void SetDescription(const std::string& desc);

    void SetQuantity(int qty);

    void SetUnitPrice(double price);

    void SetSellerID(int id);
};

#endif