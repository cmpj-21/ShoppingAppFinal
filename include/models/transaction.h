#ifndef MODELS_TRANSACTION_H
#define MODELS_TRANSACTION_H

#include <vector>
#include <string>

struct Date {
    int month;

    int day;

    int year;

    Date();

    Date(int m, int d, int y);
};

struct TransactionItem {
    int productID;

    std::string itemName;

    int quantity;

    double unitPrice;

    TransactionItem();

    TransactionItem(int productID, const std::string& itemName, int quantity, double unitPrice);
};

class Transaction {
private:
    Date date_;
    std::vector<TransactionItem> items_; 
    int buyerID_;
    int sellerID_;
    double totalAmount_;

public:
    Transaction();

    Transaction(const Date& date, const std::vector<TransactionItem>& items, int buyerID, int sellerID, double totalAmount);

    const Date& GetDate() const;

    const std::vector<TransactionItem>& GetItems() const;

    int GetBuyerID() const;

    int GetSellerID() const;

    double GetTotalAmount() const;

    void SetDate(const Date& date);

    void SetItems(const std::vector<TransactionItem>& items);

    void SetBuyerID(int id);

    void SetSellerID(int id);

    void SetTotalAmount(double amount);

    bool AddItem(const TransactionItem& item);
};

#endif