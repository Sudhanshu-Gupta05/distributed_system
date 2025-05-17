#include "File.hpp"
#include "PermissionsDecorator.hpp"
#include <iostream>

File::File(const std::string& name)
    : name(name), permissions(std::make_unique<PermissionsDecorator>()) {}

std::string File::getName() const {
    return name;
}

void File::setName(const std::string& name) {
    this->name = name;
}

void File::add(FileSystemComponent* component) {
    // Files are leaf nodes, they cannot have children
    std::cout << "Cannot add components to a file." << std::endl;
}

void File::remove(FileSystemComponent* component) {
    // Files are leaf nodes, they cannot have children
    std::cout << "Cannot remove components from a file." << std::endl;
}

FileSystemComponent* File::getChild(const std::string& name) {
    // Files are leaf nodes, they cannot have children
    return nullptr;
}

void File::display(const std::string& indent) const {
    std::cout << indent << "File: " << name << std::endl;
}

PermissionsDecorator* File::getPermissions() {
    return permissions.get();
}

void File::writeContent(const std::string& content) {
    this->content = content;
    // Create a new version with the current content
    versions.emplace_back(content);
}

std::string File::readContent() const {
    return content;
}

const std::vector<FileVersion>& File::getVersions() const {
    return versions;
} 