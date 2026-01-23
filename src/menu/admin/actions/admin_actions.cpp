#include "menu/admin/actions/admin_actions.h"
#include "utils/utils.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

static const size_t COLUMN_SPACING = 3;

static std::string Spaces(size_t n) {
    std::string s;
    for (size_t i = 0; i < n; ++i) s.push_back(' ');
    return s;
}

AdminActions::AdminActions() {
    adminPassword_ = "H3LLo?";
}

AdminActions::AdminActions(const std::string& adminPassword) {
    adminPassword_ = adminPassword;
}

bool AdminActions::Authenticate(const std::string& password) const {
    return password == adminPassword_;
}

static bool DateInRange(const Date& d, int sm, int sd, int sy, int em, int ed, int ey) {
    if (d.year < sy) return false;
    if (d.year > ey) return false;
    if (d.year == sy) {
        if (d.month < sm) return false;
        if (d.month == sm && d.day < sd) return false;
    }
    if (d.year == ey) {
        if (d.month > em) return false;
        if (d.month == em && d.day > ed) return false;
    }
    return true;
}

void AdminActions::ShowAllUsers(const std::vector<User>& users) const {
    std::string hdr1 = "UserID";
    std::string hdr2 = "Password";
    std::string hdr3 = "Name";
    std::string hdr4 = "Address";
    std::string hdr5 = "Contact";

    size_t w1 = hdr1.size();
    size_t w2 = hdr2.size();
    size_t w3 = hdr3.size();
    size_t w4 = hdr4.size();
    size_t w5 = hdr5.size();

    for (int i = 0; i < (int)users.size(); ++i) {
        const User& u = users[i];
        std::string s1 = std::to_string(u.GetUserID());
        if (s1.size() > w1) w1 = s1.size();

        const std::string& p = u.GetPassword();
        if (p.size() > w2) w2 = p.size();

        const std::string& n = u.GetName();
        if (n.size() > w3) w3 = n.size();

        const std::string& a = u.GetAddress();
        if (a.size() > w4) w4 = a.size();

        std::string s5 = std::to_string(u.GetContactNumber());
        if (s5.size() > w5) w5 = s5.size();
    }

    std::string gap = Spaces(COLUMN_SPACING);

    std::string header = Utils::RightJustify(hdr1, w1) + gap +
                         Utils::LeftJustify(hdr2, w2) + gap +
                         Utils::LeftJustify(hdr3, w3) + gap +
                         Utils::LeftJustify(hdr4, w4) + gap +
                         Utils::RightJustify(hdr5, w5);

    std::cout << header << "\n";

    size_t sepLen = w1 + w2 + w3 + w4 + w5 + (COLUMN_SPACING * 4);
    std::string sep;
    for (size_t i = 0; i < sepLen; ++i) sep.push_back('-');
    std::cout << sep << "\n";

    for (int i = 0; i < (int)users.size(); ++i) {
        const User& u = users[i];
        std::string col1 = std::to_string(u.GetUserID());
        std::string col2 = u.GetPassword();
        std::string col3 = u.GetName();
        std::string col4 = u.GetAddress();
        std::string col5 = std::to_string(u.GetContactNumber());

        std::string line = Utils::RightJustify(col1, w1) + gap +
                           Utils::LeftJustify(col2, w2) + gap +
                           Utils::LeftJustify(col3, w3) + gap +
                           Utils::LeftJustify(col4, w4) + gap +
                           Utils::RightJustify(col5, w5);
        std::cout << line << "\n";
    }
}

void AdminActions::ShowAllSellers(const std::vector<User>& users, const std::vector<Item>& items) const {
    std::map<int,int> sellerCounts;
    for (int i = 0; i < (int)items.size(); ++i) {
        int sid = items[i].GetSellerID();
        if (sellerCounts.find(sid) == sellerCounts.end()) {
            sellerCounts[sid] = 1;
        } else {
            sellerCounts[sid] = sellerCounts[sid] + 1;
        }
    }

    std::string hdr1 = "SellerID";
    std::string hdr2 = "Password";
    std::string hdr3 = "Name";
    std::string hdr4 = "Address";
    std::string hdr5 = "Contact";
    std::string hdr6 = "NumItems";

    size_t w1 = hdr1.size();
    size_t w2 = hdr2.size();
    size_t w3 = hdr3.size();
    size_t w4 = hdr4.size();
    size_t w5 = hdr5.size();
    size_t w6 = hdr6.size();

    std::vector<const User*> sellers;
    for (int i = 0; i < (int)users.size(); ++i) {
        const User& u = users[i];
        int uid = u.GetUserID();
        if (sellerCounts.find(uid) != sellerCounts.end()) {
            sellers.push_back(&u);

            std::string s1 = std::to_string(uid);
            if (s1.size() > w1) w1 = s1.size();

            const std::string& p = u.GetPassword();
            if (p.size() > w2) w2 = p.size();

            const std::string& n = u.GetName();
            if (n.size() > w3) w3 = n.size();

            const std::string& a = u.GetAddress();
            if (a.size() > w4) w4 = a.size();

            std::string s5 = std::to_string(u.GetContactNumber());
            if (s5.size() > w5) w5 = s5.size();

            std::string s6 = std::to_string(sellerCounts[uid]);
            if (s6.size() > w6) w6 = s6.size();
        }
    }

    std::string gap = Spaces(COLUMN_SPACING);

    std::string header = Utils::RightJustify(hdr1, w1) + gap +
                         Utils::LeftJustify(hdr2, w2) + gap +
                         Utils::LeftJustify(hdr3, w3) + gap +
                         Utils::LeftJustify(hdr4, w4) + gap +
                         Utils::RightJustify(hdr5, w5) + gap +
                         Utils::RightJustify(hdr6, w6);

    std::cout << header << "\n";

    size_t sepLen = w1 + w2 + w3 + w4 + w5 + w6 + (COLUMN_SPACING * 5);
    std::string sep;
    for (size_t i = 0; i < sepLen; ++i) sep.push_back('-');
    std::cout << sep << "\n";

    for (int i = 0; i < (int)sellers.size(); ++i) {
        const User* u = sellers[i];
        int uid = u->GetUserID();
        std::string col1 = std::to_string(uid);
        std::string col2 = u->GetPassword();
        std::string col3 = u->GetName();
        std::string col4 = u->GetAddress();
        std::string col5 = std::to_string(u->GetContactNumber());
        std::string col6 = std::to_string(sellerCounts[uid]);

        std::string line = Utils::RightJustify(col1, w1) + gap +
                           Utils::LeftJustify(col2, w2) + gap +
                           Utils::LeftJustify(col3, w3) + gap +
                           Utils::LeftJustify(col4, w4) + gap +
                           Utils::RightJustify(col5, w5) + gap +
                           Utils::RightJustify(col6, w6);
        std::cout << line << "\n";
    }
}

double AdminActions::ShowTotalSalesInDuration(const std::vector<Transaction>& transactions,
                                              int startMonth, int startDay, int startYear,
                                              int endMonth, int endDay, int endYear) const {
    double total = 0.0;
    for (int i = 0; i < (int)transactions.size(); ++i) {
        const Transaction& t = transactions[i];
        if (DateInRange(t.GetDate(), startMonth, startDay, startYear, endMonth, endDay, endYear)) {
            total = total + t.GetTotalAmount();
        }
    }
    return total;
}

void AdminActions::ShowSellersSales(const std::vector<Transaction>& transactions,
                                    int startMonth, int startDay, int startYear,
                                    int endMonth, int endDay, int endYear) const {
    std::map<int, double> totals;
    for (int i = 0; i < (int)transactions.size(); ++i) {
        const Transaction& t = transactions[i];
        if (DateInRange(t.GetDate(), startMonth, startDay, startYear, endMonth, endDay, endYear)) {
            int sid = t.GetSellerID();
            double prev = 0.0;
            if (totals.find(sid) != totals.end()) {
                prev = totals[sid];
            }
            totals[sid] = prev + t.GetTotalAmount();
        }
    }

    std::string hdr1 = "SellerID";
    std::string hdr2 = "TotalSales";
    size_t w1 = hdr1.size();
    size_t w2 = hdr2.size();

    for (std::map<int,double>::const_iterator it = totals.begin(); it != totals.end(); ++it) {
        std::string s1 = std::to_string(it->first);
        if (s1.size() > w1) w1 = s1.size();
        std::string s2 = std::to_string(it->second);
        if (s2.size() > w2) w2 = s2.size();
    }

    std::string gap2 = Spaces(COLUMN_SPACING);
    std::string header2 = Utils::RightJustify(hdr1, w1) + gap2 + Utils::RightJustify(hdr2, w2);
    std::cout << header2 << "\n";
    size_t sepLen2 = w1 + w2 + (COLUMN_SPACING * 1);
    std::string sep2;
    for (size_t i = 0; i < sepLen2; ++i) sep2.push_back('-');
    std::cout << sep2 << "\n";

    for (std::map<int,double>::const_iterator it = totals.begin(); it != totals.end(); ++it) {
        std::string s1 = std::to_string(it->first);
        std::string s2 = std::to_string(it->second);
        std::string line = Utils::RightJustify(s1, w1) + gap2 + Utils::RightJustify(s2, w2);
        std::cout << line << "\n";
    }
}

void AdminActions::ShowShopaholics(const std::vector<Transaction>& transactions,
                                   int startMonth, int startDay, int startYear,
                                   int endMonth, int endDay, int endYear) const {
    std::map<int, double> totals;
    for (int i = 0; i < (int)transactions.size(); ++i) {
        const Transaction& t = transactions[i];
        if (DateInRange(t.GetDate(), startMonth, startDay, startYear, endMonth, endDay, endYear)) {
            int bid = t.GetBuyerID();
            double prev = 0.0;
            if (totals.find(bid) != totals.end()) {
                prev = totals[bid];
            }
            totals[bid] = prev + t.GetTotalAmount();
        }
    }

    std::string hdr1 = "BuyerID";
    std::string hdr2 = "TotalBought";
    size_t w1 = hdr1.size();
    size_t w2 = hdr2.size();

    for (std::map<int,double>::const_iterator it = totals.begin(); it != totals.end(); ++it) {
        std::string s1 = std::to_string(it->first);
        if (s1.size() > w1) w1 = s1.size();
        std::string s2 = std::to_string(it->second);
        if (s2.size() > w2) w2 = s2.size();
    }

    std::string gap3 = Spaces(COLUMN_SPACING);
    std::string header3 = Utils::RightJustify(hdr1, w1) + gap3 + Utils::RightJustify(hdr2, w2);
    std::cout << header3 << "\n";
    size_t sepLen3 = w1 + w2 + (COLUMN_SPACING * 1);
    std::string sep3;
    for (size_t i = 0; i < sepLen3; ++i) sep3.push_back('-');
    std::cout << sep3 << "\n";

    for (std::map<int,double>::const_iterator it = totals.begin(); it != totals.end(); ++it) {
        std::string s1 = std::to_string(it->first);
        std::string s2 = std::to_string(it->second);
        std::string line = Utils::RightJustify(s1, w1) + gap3 + Utils::RightJustify(s2, w2);
        std::cout << line << "\n";
    }
}