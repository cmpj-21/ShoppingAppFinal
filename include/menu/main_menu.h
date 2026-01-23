#ifndef MENU_MAIN_MENU_H
#define MENU_MAIN_MENU_H

#include <string>
#include "shopping_app.h"

class MainMenu {
private:
    ShoppingApp& app_;

public:
    MainMenu(ShoppingApp& app);

    MainMenu() = delete;

    void Show();
};

#endif