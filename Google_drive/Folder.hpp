#pragma once
#include "FileSystemComponent.hpp"
#include <unordered_map>
#include <memory>

class Folder : public FileSystemComponent {
public:
    explicit Folder(const std::string& name);
    std::string getName() const override;
    void setName(const std::string& name) override;
    void add(FileSystemComponent* component) override;
    void remove(FileSystemComponent* component) override;
    FileSystemComponent* getChild(const std::string& name) override;
    void display(const std::string& indent) const override;
    PermissionsDecorator* getPermissions() override;

    const std::unordered_map<std::string, FileSystemComponent*>& getChildren() const;

private:
    std::string name;
    std::unordered_map<std::string, FileSystemComponent*> children;
    std::unique_ptr<PermissionsDecorator> permissions;
}; 