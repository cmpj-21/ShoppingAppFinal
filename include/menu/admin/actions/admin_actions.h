#ifndef MENU_ADMIN_ACTIONS_ADMIN_ACTIONS_H
#define MENU_ADMIN_ACTIONS_ADMIN_ACTIONS_H

#include <string>
#include <vector>
#include "models/user.h"
#include "models/transaction.h"
#include "models/item.h"

class AdminActions {
private:
    std::string adminPassword_;

public:
    AdminActions();

    AdminActions(const std::string& adminPassword);

    bool Authenticate(const std::string& password) const;

    void ShowAllUsers(const std::vector<User>& users) const;

    void ShowAllSellers(const std::vector<User>& users, const std::vector<Item>& items) const;

    double ShowTotalSalesInDuration(const std::vector<Transaction>& transactions,
                                    int startMonth, int startDay, int startYear,
                                    int endMonth, int endDay, int endYear) const;

    void ShowSellersSales(const std::vector<Transaction>& transactions,
                          int startMonth, int startDay, int startYear,
                          int endMonth, int endDay, int endYear) const;

    void ShowShopaholics(const std::vector<Transaction>& transactions,
                         int startMonth, int startDay, int startYear,
                         int endMonth, int endDay, int endYear) const;
};

#endif