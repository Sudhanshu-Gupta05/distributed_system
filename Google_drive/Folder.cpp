#include "Folder.hpp"
#include "PermissionsDecorator.hpp"
#include <iostream>

Folder::Folder(const std::string& name)
    : name(name), permissions(std::make_unique<PermissionsDecorator>()) {}

std::string Folder::getName() const {
    return name;
}

void Folder::setName(const std::string& name) {
    this->name = name;
}

void Folder::add(FileSystemComponent* component) {
    children[component->getName()] = component;
}

void Folder::remove(FileSystemComponent* component) {
    children.erase(component->getName());
}

FileSystemComponent* Folder::getChild(const std::string& name) {
    auto it = children.find(name);
    return (it != children.end()) ? it->second : nullptr;
}

void Folder::display(const std::string& indent) const {
    std::cout << indent << "Folder: " << name << std::endl;
    for (const auto& [name, component] : children) {
        component->display(indent + "    ");
    }
}

const std::unordered_map<std::string, FileSystemComponent*>& Folder::getChildren() const {
    return children;
}

PermissionsDecorator* Folder::getPermissions() {
    return permissions.get();
} 