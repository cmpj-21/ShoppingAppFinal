#ifndef MENU_USER_ACTIONS_USER_ACTIONS_H
#define MENU_USER_ACTIONS_USER_ACTIONS_H

#include <string>
#include <vector>
#include "models/user.h"

class UserActions {
public:
    UserActions();

    bool Login(const std::vector<User>& users, int userId, const std::string& password) const;
};

#endif