#ifndef MENU_ADMIN_ADMIN_MENU_H
#define MENU_ADMIN_ADMIN_MENU_H

#include "menu/main_menu.h"
#include "menu/admin/actions/admin_actions.h"

class AdminMenu {
private:
    ShoppingApp& app_;
    AdminActions actions_;

public:
    AdminMenu(ShoppingApp& app);
    AdminMenu() = delete;
    void Show();
};

#endif