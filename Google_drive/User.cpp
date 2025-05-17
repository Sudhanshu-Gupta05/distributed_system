#include "User.hpp"

User::User(const std::string& username, const std::string& password, Role role)
    : username(username), password(password), role(role) {}

std::string User::getUsername() const {
    return username;
}

User::Role User::getRole() const {
    return role;
}

bool User::authenticate(const std::string& password) const {
    return this->password == password;
} 