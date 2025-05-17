#pragma once
#include <string>
#include <stdexcept>
#include "PermissionsDecorator.hpp"

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual std::string getName() const = 0;
    virtual void setName(const std::string& name) = 0;
    virtual void add(FileSystemComponent* component) = 0;
    virtual void remove(FileSystemComponent* component) = 0;
    virtual FileSystemComponent* getChild(const std::string& name) = 0;
    virtual void display(const std::string& indent) const = 0;
    virtual PermissionsDecorator* getPermissions() = 0;
}; 