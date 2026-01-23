#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <string>
#include <vector>
#include "models/item.h"

class Utils {
public:
    static std::string RightJustify(const std::string& input, size_t width);
    static std::string LeftJustify(const std::string& input, size_t width);

    static void PrintItemsTable(const std::vector<Item>& items);
    static bool ContainsIgnoreCase(const std::string& source, const std::string& searchTerm);
};

#endif