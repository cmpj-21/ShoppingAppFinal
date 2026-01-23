#ifndef MODELS_USER_H
#define MODELS_USER_H

#include <string>

class User {
private:
    int userID_;

    std::string password_;

    std::string name_;

    std::string address_;

    long long contactNumber_;

public:
    User();

    User(int userID, const std::string& password, const std::string& name, const std::string& address, long long contactNumber);

    int GetUserID() const;

    const std::string& GetPassword() const;

    const std::string& GetName() const;

    const std::string& GetAddress() const;

    long long GetContactNumber() const;

    void SetUserID(int id);

    void SetPassword(const std::string& password);

    void SetName(const std::string& name);

    void SetAddress(const std::string& address);

    void SetContactNumber(long long number);
};

#endif