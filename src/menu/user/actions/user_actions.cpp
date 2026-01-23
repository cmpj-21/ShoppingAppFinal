#include "menu/user/actions/user_actions.h"

UserActions::UserActions() {
}

bool UserActions::Login(const std::vector<User>& users, int userId, const std::string& password) const {
    for (int i = 0; i < (int)users.size(); ++i) {
        if (users[i].GetUserID() == userId) {
            if (users[i].GetPassword() == password) {
                return true;
            } else {
                return false; 
            }
        }
    }
    return false; 
}