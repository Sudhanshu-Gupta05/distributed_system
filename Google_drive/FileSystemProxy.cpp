#include "FileSystemProxy.hpp"
#include <stdexcept>

FileSystemProxy::FileSystemProxy(FileSystemComponent* component, User* user)
    : realComponent(component), currentUser(user) {}

std::string FileSystemProxy::getName() const {
    return realComponent->getName();
}

void FileSystemProxy::setName(const std::string& name) {
    if (hasWritePermission()) {
        realComponent->setName(name);
    } else {
        throw std::runtime_error("No write permission for user: " + currentUser->getUsername());
    }
}

void FileSystemProxy::add(FileSystemComponent* component) {
    if (hasWritePermission()) {
        realComponent->add(component);
    } else {
        throw std::runtime_error("No write permission for user: " + currentUser->getUsername());
    }
}

void FileSystemProxy::remove(FileSystemComponent* component) {
    if (hasWritePermission()) {
        realComponent->remove(component);
    } else {
        throw std::runtime_error("No write permission for user: " + currentUser->getUsername());
    }
}

FileSystemComponent* FileSystemProxy::getChild(const std::string& name) {
    if (hasReadPermission()) {
        return realComponent->getChild(name);
    } else {
        throw std::runtime_error("No read permission for user: " + currentUser->getUsername());
    }
}

void FileSystemProxy::display(const std::string& indent) const {
    if (hasReadPermission()) {
        realComponent->display(indent);
    } else {
        throw std::runtime_error("No read permission for user: " + currentUser->getUsername());
    }
}

PermissionsDecorator* FileSystemProxy::getPermissions() {
    return realComponent->getPermissions();
}

bool FileSystemProxy::hasReadPermission() const {
    auto permission = realComponent->getPermissions()->getPermission(currentUser);
    return permission == PermissionsDecorator::Permission::READ || 
           permission == PermissionsDecorator::Permission::WRITE;
}

bool FileSystemProxy::hasWritePermission() const {
    auto permission = realComponent->getPermissions()->getPermission(currentUser);
    return permission == PermissionsDecorator::Permission::WRITE;
} 