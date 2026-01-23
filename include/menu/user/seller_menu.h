#ifndef MENU_USER_SELLER_MENU_H
#define MENU_USER_SELLER_MENU_H

#include "menu/user/user_menu.h"
#include "menu/user/actions/seller_actions.h"

class SellerMenu {
private:
    ShoppingApp& app_;

    SellerActions actions_;

    int loggedInUserId_;

public:
    SellerMenu(ShoppingApp& app, int userId);

    SellerMenu() = delete;

    void Show();
};

#endif