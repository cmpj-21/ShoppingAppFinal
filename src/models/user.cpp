#include "models/user.h"

User::User() {
    userID_ = 0;
    password_ = "";
    name_ = "";
    address_ = "";
    contactNumber_ = 0;
}

User::User(int userID, const std::string& password, const std::string& name,
           const std::string& address, long long contactNumber) {
    userID_ = userID;

    if ((int)password.size() > 10) {
        password_ = password.substr(0, 10);
    } else {
        password_ = password;
    }

    if ((int)name.size() > 20) {
        name_ = name.substr(0, 20);
    } else {
        name_ = name;
    }

    if ((int)address.size() > 30) {
        address_ = address.substr(0, 30);
    } else {
        address_ = address;
    }

    if (contactNumber < 0) {
        contactNumber_ = 0;
    } else {
        contactNumber_ = contactNumber;
    }
}

int User::GetUserID() const {
    return userID_;
}

const std::string& User::GetPassword() const {
    return password_;
}

const std::string& User::GetName() const {
    return name_;
}

const std::string& User::GetAddress() const {
    return address_;
}

long long User::GetContactNumber() const {
    return contactNumber_;
}

void User::SetUserID(int id) {
    userID_ = id;
}

void User::SetPassword(const std::string& password) {
    if ((int)password.size() > 10) {
        password_ = password.substr(0, 10);
    } else {
        password_ = password;
    }
}

void User::SetName(const std::string& name) {
    if ((int)name.size() > 20) {
        name_ = name.substr(0, 20);
    } else {
        name_ = name;
    }
}

void User::SetAddress(const std::string& address) {
    if ((int)address.size() > 30) {
        address_ = address.substr(0, 30);
    } else {
        address_ = address;
    }
}

void User::SetContactNumber(long long number) {
    if (number < 0) {
        contactNumber_ = 0;
    } else {
        contactNumber_ = number;
    }
}