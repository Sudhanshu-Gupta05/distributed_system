#pragma once
#include "FileSystemComponent.hpp"
#include "FileVersion.hpp"
#include <vector>
#include <memory>

class File : public FileSystemComponent {
public:
    explicit File(const std::string& name);
    std::string getName() const override;
    void setName(const std::string& name) override;
    void add(FileSystemComponent* component) override;
    void remove(FileSystemComponent* component) override;
    FileSystemComponent* getChild(const std::string& name) override;
    void display(const std::string& indent) const override;
    PermissionsDecorator* getPermissions() override;

    void writeContent(const std::string& content);
    std::string readContent() const;
    const std::vector<FileVersion>& getVersions() const;

private:
    std::string name;
    std::string content;
    std::vector<FileVersion> versions;
    std::unique_ptr<PermissionsDecorator> permissions;
}; 