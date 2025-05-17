#pragma once
#include "FileSystemComponent.hpp"
#include "User.hpp"

class FileSystemProxy : public FileSystemComponent {
public:
    FileSystemProxy(FileSystemComponent* component, User* user);
    std::string getName() const override;
    void setName(const std::string& name) override;
    void add(FileSystemComponent* component) override;
    void remove(FileSystemComponent* component) override;
    FileSystemComponent* getChild(const std::string& name) override;
    void display(const std::string& indent) const override;
    PermissionsDecorator* getPermissions() override;

private:
    bool hasReadPermission() const;
    bool hasWritePermission() const;

    FileSystemComponent* realComponent;
    User* currentUser;
}; 