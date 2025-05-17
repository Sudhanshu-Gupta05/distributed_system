#include "PermissionsDecorator.hpp"

PermissionsDecorator::PermissionsDecorator() {}

void PermissionsDecorator::setPermission(User* user, Permission permission) {
    userPermissions[user] = permission;
}

PermissionsDecorator::Permission PermissionsDecorator::getPermission(User* user) const {
    auto it = userPermissions.find(user);
    return (it != userPermissions.end()) ? it->second : Permission::NONE;
} 