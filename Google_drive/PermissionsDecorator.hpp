#pragma once
#include "User.hpp"
#include <unordered_map>

class PermissionsDecorator {
public:
    enum class Permission {
        READ,
        WRITE,
        NONE
    };

    PermissionsDecorator();
    void setPermission(User* user, Permission permission);
    Permission getPermission(User* user) const;

private:
    std::unordered_map<User*, Permission> userPermissions;
}; 