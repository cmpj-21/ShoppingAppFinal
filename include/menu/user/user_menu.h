#ifndef MENU_USER_USER_MENU_H
#define MENU_USER_USER_MENU_H

#include "menu/main_menu.h"
#include "menu/user/actions/user_actions.h"

class UserMenu {
private:
    ShoppingApp& app_;

    UserActions userActions_;

public:
    UserMenu(ShoppingApp& app);

    UserMenu() = delete;

    void Show();
};

#endif