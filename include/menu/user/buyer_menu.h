#ifndef MENU_USER_BUYER_MENU_H
#define MENU_USER_BUYER_MENU_H

#include "menu/user/user_menu.h"
#include "menu/user/actions/buyer_actions.h"

class BuyerMenu {
private:
    ShoppingApp& app_;

    BuyerActions actions_;

    int loggedInUserId_;

public:
    BuyerMenu(ShoppingApp& app, int userId);

    BuyerMenu() = delete;

    void Show();
};

#endif