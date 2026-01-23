#include "utils/utils.h"
#include "models/item.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>

static const size_t COLUMN_SPACING = 3;

static std::string Spaces(size_t n) {
    std::string s;
    for (size_t i = 0; i < n; ++i) s.push_back(' ');
    return s;
}

std::string Utils::RightJustify(const std::string& input, size_t width) {
    if (input.size() >= width) return input;
    size_t pad = width - input.size();
    return Spaces(pad) + input;
}

std::string Utils::LeftJustify(const std::string& input, size_t width) {
    if (input.size() >= width) return input;
    size_t pad = width - input.size();
    return input + Spaces(pad);
}

void Utils::PrintItemsTable(const std::vector<Item>& items) {
    const std::string hdr1 = "ProductID";
    const std::string hdr2 = "Name";
    const std::string hdr3 = "Category";
    const std::string hdr4 = "UnitPrice";
    const std::string hdr5 = "Qty";

    size_t w1 = hdr1.size();
    size_t w2 = hdr2.size();
    size_t w3 = hdr3.size();
    size_t w4 = hdr4.size();
    size_t w5 = hdr5.size();

    auto FormatPrice = [](double price) -> std::string {
        std::ostringstream oss;
        oss.setf(std::ios::fixed);
        oss.precision(2);
        oss << price;
        return oss.str();
    };

    for (size_t i = 0; i < items.size(); ++i) {
        const Item& it = items[i];
        std::string s1 = std::to_string(it.GetProductID());
        if (s1.size() > w1) w1 = s1.size();

        const std::string& s2 = it.GetItemName();
        if (s2.size() > w2) w2 = s2.size();

        const std::string& s3 = it.GetCategory();
        if (s3.size() > w3) w3 = s3.size();

        std::string s4 = FormatPrice(it.GetUnitPrice());
        if (s4.size() > w4) w4 = s4.size();

        std::string s5 = std::to_string(it.GetQuantity());
        if (s5.size() > w5) w5 = s5.size();
    }

    std::string gap = Spaces(COLUMN_SPACING);

    std::string header = Utils::RightJustify(hdr1, w1) + gap
                       + Utils::LeftJustify(hdr2, w2) + gap
                       + Utils::LeftJustify(hdr3, w3) + gap
                       + Utils::RightJustify(hdr4, w4) + gap
                       + Utils::RightJustify(hdr5, w5);

    std::cout << header << "\n";

    size_t sepLen = w1 + w2 + w3 + w4 + w5 + (COLUMN_SPACING * 4);
    std::string sep;
    for (size_t i = 0; i < sepLen; ++i) sep.push_back('-');
    std::cout << sep << "\n";

    for (size_t i = 0; i < items.size(); ++i) {
        const Item& it = items[i];
        std::string col1 = std::to_string(it.GetProductID());
        std::string col2 = it.GetItemName();
        std::string col3 = it.GetCategory();
        std::string col4 = FormatPrice(it.GetUnitPrice());
        std::string col5 = std::to_string(it.GetQuantity());

        std::string line = Utils::RightJustify(col1, w1) + gap
                         + Utils::LeftJustify(col2, w2) + gap
                         + Utils::LeftJustify(col3, w3) + gap
                         + Utils::RightJustify(col4, w4) + gap
                         + Utils::RightJustify(col5, w5);
        std::cout << line << "\n";
    }
}

bool Utils::ContainsIgnoreCase(const std::string& source, const std::string& searchTerm) {
    std::string s1;
    s1.reserve(source.size());
    for (size_t i = 0; i < source.size(); ++i) s1.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(source[i]))));

    std::string s2;
    s2.reserve(searchTerm.size());
    for (size_t i = 0; i < searchTerm.size(); ++i) s2.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(searchTerm[i]))));

    if (s2.empty()) return true; 
    if (s1.find(s2) != std::string::npos) return true;
    return false;
}