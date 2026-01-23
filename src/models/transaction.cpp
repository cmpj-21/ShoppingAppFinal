#include "models/transaction.h"

Date::Date() {
    month = 0;
    day = 0;
    year = 0;
}

Date::Date(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
}

TransactionItem::TransactionItem() {
    productID = 0;
    itemName = "";
    quantity = 0;
    unitPrice = 0.0;
}

TransactionItem::TransactionItem(int productID_, const std::string& itemName_, int quantity_, double unitPrice_) {
    productID = productID_;
    itemName = itemName_;
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
}

Transaction::Transaction() {
    date_ = Date();
    items_.clear();
    buyerID_ = 0;
    sellerID_ = 0;
    totalAmount_ = 0.0;
}

Transaction::Transaction(const Date& date, const std::vector<TransactionItem>& items, int buyerID, int sellerID, double totalAmount) {
    date_ = date;
    items_.clear();
    for (int i = 0; i < (int)items.size() && i < 5; ++i) {
        items_.push_back(items[i]);
    }
    buyerID_ = buyerID;
    sellerID_ = sellerID;

    double computed = 0.0;
    for (int i = 0; i < (int)items_.size(); ++i) {
        computed = computed + (items_[i].quantity * items_[i].unitPrice);
    }
    totalAmount_ = computed;
}

const Date& Transaction::GetDate() const {
    return date_;
}

const std::vector<TransactionItem>& Transaction::GetItems() const {
    return items_;
}

int Transaction::GetBuyerID() const {
    return buyerID_;
}

int Transaction::GetSellerID() const {
    return sellerID_;
}

double Transaction::GetTotalAmount() const {
    return totalAmount_;
}

void Transaction::SetDate(const Date& date) {
    date_ = date;
}

void Transaction::SetItems(const std::vector<TransactionItem>& items) {
    items_.clear();
    for (int i = 0; i < (int)items.size() && i < 5; ++i) {
        items_.push_back(items[i]);
    }

    double total = 0.0;
    for (int i = 0; i < (int)items_.size(); ++i) {
        total = total + (items_[i].quantity * items_[i].unitPrice);
    }
    totalAmount_ = total;
}

void Transaction::SetBuyerID(int id) {
    buyerID_ = id;
}

void Transaction::SetSellerID(int id) {
    sellerID_ = id;
}

void Transaction::SetTotalAmount(double amount) {
    if (amount < 0.0) {
        totalAmount_ = 0.0;
    } else {
        totalAmount_ = amount;
    }
}

bool Transaction::AddItem(const TransactionItem& item) {
    if ((int)items_.size() >= 5) {
        return false; 
    }
    if (item.quantity <= 0) {
        return false; 
    }
    if (item.unitPrice < 0.0) {
        return false; 
    }

    items_.push_back(item);
    totalAmount_ = totalAmount_ + (item.quantity * item.unitPrice);
    return true;
}