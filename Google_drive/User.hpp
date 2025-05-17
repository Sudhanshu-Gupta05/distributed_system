#pragma once
#include <string>

class User {
public:
    enum class Role {
        ADMIN,
        USER
    };

    User(const std::string& username, const std::string& password, Role role);
    std::string getUsername() const;
    Role getRole() const;
    bool authenticate(const std::string& password) const;

private:
    std::string username;
    std::string password;
    Role role;
}; 