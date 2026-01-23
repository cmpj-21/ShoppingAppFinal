#include "services/file_handling.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileHandling::FileHandling() {
}

bool FileHandling::LoadUsersText(const std::string& filepath, std::vector<User>& outUsers) {
    std::ifstream in(filepath.c_str());
    if (!in.is_open()) {
        return false;
    }

    std::string line;
    while (true) {
        bool found = false;
        while (std::getline(in, line)) {
            if (line.size() == 0) {
                continue;
            }
            found = true;
            break;
        }
        if (!found) break; 

        std::istringstream first(line);
        int userId = 0;
        std::string password;
        if (!(first >> userId >> password)) {
            while (std::getline(in, line)) {
                if (line.size() == 0) break;
            }
            continue;
        }

        std::string name;
        std::string address;
        std::string contactLine;

        if (!std::getline(in, name)) break;
        if (!std::getline(in, address)) break;
        if (!std::getline(in, contactLine)) break;

        long long contact = 0;
        {
            std::istringstream cs(contactLine);
            if (!(cs >> contact)) {
                contact = 0; 
            }
        }

        User u(userId, password, name, address, contact);
        outUsers.push_back(u);

        std::getline(in, line);
    }

    in.close();
    return true;
}

bool FileHandling::SaveUsersText(const std::string& filepath, const std::vector<User>& users) {
    std::ofstream out(filepath.c_str());
    if (!out.is_open()) {
        return false;
    }

    for (int i = 0; i < (int)users.size(); ++i) {
        const User& u = users[i];
        out << u.GetUserID() << " " << u.GetPassword() << "\n";
        out << u.GetName() << "\n";
        out << u.GetAddress() << "\n";
        out << u.GetContactNumber() << "\n";
        out << "\n";
    }

    out.close();
    return true;
}

bool FileHandling::LoadItemsText(const std::string& filepath, std::vector<Item>& outItems) {
    std::ifstream in(filepath.c_str());
    if (!in.is_open()) {
        return false;
    }

    std::string line;
    while (true) {
        bool found = false;
        while (std::getline(in, line)) {
            if (line.size() == 0) continue;
            found = true;
            break;
        }
        if (!found) break; 

        std::istringstream first(line);
        int productId = 0;
        int sellerId = 0;
        if (!(first >> productId >> sellerId)) {
            while (std::getline(in, line)) {
                if (line.size() == 0) break;
            }
            continue;
        }

        std::string name;
        std::string category;
        std::string description;
        std::string qtyPriceLine;

        if (!std::getline(in, name)) break;
        if (!std::getline(in, category)) break;
        if (!std::getline(in, description)) break;
        if (!std::getline(in, qtyPriceLine)) break;

        int quantity = 0;
        double unitPrice = 0.0;
        {
            std::istringstream qp(qtyPriceLine);
            if (!(qp >> quantity >> unitPrice)) {
                quantity = 0;
                unitPrice = 0.0;
            }
        }

        Item it(productId, name, category, description, quantity, unitPrice, sellerId);
        outItems.push_back(it);

        std::getline(in, line);
    }

    in.close();
    return true;
}

bool FileHandling::SaveItemsText(const std::string& filepath, const std::vector<Item>& items) {
    std::ofstream out(filepath.c_str());
    if (!out.is_open()) {
        return false;
    }

    for (int i = 0; i < (int)items.size(); ++i) {
        const Item& it = items[i];
        out << it.GetProductID() << " " << it.GetSellerID() << "\n";
        out << it.GetItemName() << "\n";
        out << it.GetCategory() << "\n";
        out << it.GetDescription() << "\n";
        out << it.GetQuantity() << " " << it.GetUnitPrice() << "\n";
        out << "\n";
    }

    out.close();
    return true;
}

bool FileHandling::AppendTransactionText(const std::string& filepath, const Transaction& transaction) {
    std::ofstream out(filepath.c_str(), std::ios::app);
    if (!out.is_open()) {
        return false;
    }

    const Date& d = transaction.GetDate();
    out << "DATE " << d.month << " " << d.day << " " << d.year << "\n";
    out << "BUYER " << transaction.GetBuyerID() << " SELLER " << transaction.GetSellerID() << " TOTAL " << transaction.GetTotalAmount() << "\n";

    const std::vector<TransactionItem>& items = transaction.GetItems();
    for (int i = 0; i < (int)items.size(); ++i) {
        const TransactionItem& ti = items[i];
        out << "ITEM " << ti.productID << " " << ti.quantity << " " << ti.unitPrice << " " << ti.itemName << "\n";
    }

    out << "\n";
    out.close();
    return true;
}

bool FileHandling::LoadTransactionsText(const std::string& filepath, std::vector<Transaction>& outTransactions) {
    std::ifstream in(filepath.c_str());
    if (!in.is_open()) {
        return false;
    }

    std::string line;
    Date curDate;
    int curBuyer = 0;
    int curSeller = 0;
    double curTotal = 0.0;
    std::vector<TransactionItem> curItems;
    bool inBlock = false;

    while (std::getline(in, line)) {
        if (line.size() == 0) {
            if (inBlock) {
                Transaction t;
                t.SetDate(curDate);
                t.SetItems(curItems);
                t.SetBuyerID(curBuyer);
                t.SetSellerID(curSeller);
                t.SetTotalAmount(curTotal);
                outTransactions.push_back(t);

                curItems.clear();
                curBuyer = 0;
                curSeller = 0;
                curTotal = 0.0;
                inBlock = false;
            }
            continue;
        }

        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "DATE") {
            int m = 0;
            int d = 0;
            int y = 0;
            iss >> m >> d >> y;
            curDate = Date(m, d, y);
            inBlock = true;
        } else if (token == "BUYER") {
            int b = 0;
            iss >> b;
            curBuyer = b;
            std::string tmp;
            iss >> tmp; 
            int s = 0;
            iss >> s;
            curSeller = s;
            iss >> tmp; 
            double tot = 0.0;
            iss >> tot;
            curTotal = tot;
            inBlock = true;
        } else if (token == "ITEM") {
            int pid = 0;
            int qty = 0;
            double price = 0.0;
            iss >> pid >> qty >> price;
            std::string name;
            std::getline(iss, name);
            if (name.size() > 0 && name[0] == ' ') {
                name.erase(0, 1);
            }
            TransactionItem ti(pid, name, qty, price);
            curItems.push_back(ti);
            inBlock = true;
        }
    }

    if (inBlock && curItems.size() > 0) {
        Transaction t;
        t.SetDate(curDate);
        t.SetItems(curItems);
        t.SetBuyerID(curBuyer);
        t.SetSellerID(curSeller);
        t.SetTotalAmount(curTotal);
        outTransactions.push_back(t);
    }

    in.close();
    return true;
}

bool FileHandling::LoadCartText(const std::string& filepath, Cart& outCart) {
    std::ifstream in(filepath.c_str());
    if (!in.is_open()) return false;

    std::string line;
    std::vector<CartItem> items;
    while (std::getline(in, line)) {
        if (line.size() == 0) continue;
        std::istringstream iss(line);
        int pid = 0;
        int sid = 0;
        int qty = 0;
        double price = 0.0;
        if (!(iss >> pid >> sid >> qty >> price)) {
            continue; 
        }
        std::string name;
        std::getline(iss, name);
        if (name.size() > 0 && name[0] == ' ') name.erase(0, 1);
        CartItem ci(pid, sid, qty, price, name);
        items.push_back(ci);
    }

    in.close();
    outCart = Cart(items);
    return true;
}

bool FileHandling::SaveCartText(const std::string& filepath, const Cart& cart) {
    std::ofstream out(filepath.c_str());
    if (!out.is_open()) return false;

    const std::vector<CartItem>& items = cart.GetItems();
    for (int i = 0; i < (int)items.size(); ++i) {
        const CartItem& ci = items[i];
        out << ci.productID << " " << ci.sellerID << " " << ci.quantity << " " << ci.unitPrice << " " << ci.itemName << "\n";
    }

    out.close();
    return true;
}