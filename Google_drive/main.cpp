#include "FileSystemManager.hpp"
#include "User.hpp"
#include "CreateFileOperation.hpp"
#include "FileSystemProxy.hpp"
#include "Subject.hpp"
#include "Observer.hpp"
#include "FileSystemSearch.hpp"
#include "LocalStorageStrategy.hpp"
#include <iostream>
#include <memory>

class UserObserver : public Observer {
public:
    explicit UserObserver(const std::string& username) : username(username) {}
    void update(const std::string& message) override {
        std::cout << username << " received notification: " << message << std::endl;
    }
private:
    std::string username;
};

int main() {
    // Create Users
    auto admin = std::make_unique<User>("admin", "admin123", User::Role::ADMIN);
    auto user1 = std::make_unique<User>("user1", "password1", User::Role::USER);
    auto user2 = std::make_unique<User>("user2", "password2", User::Role::USER);

    // Get FileSystemManager Instance
    auto& fsManager = FileSystemManager::getInstance();

    // Create Folders and Files
    auto root = fsManager.getRoot();
    root->getPermissions()->setPermission(admin.get(), PermissionsDecorator::Permission::WRITE);
    root->getPermissions()->setPermission(user1.get(), PermissionsDecorator::Permission::WRITE);

    // Create Files and Folders using Template Method Pattern
    auto createFolderOperation = std::make_unique<CreateFileOperation>(root, "Documents");
    createFolderOperation->execute();

    auto documents = dynamic_cast<Folder*>(root->getChild("Documents"));
    documents->getPermissions()->setPermission(user1.get(), PermissionsDecorator::Permission::WRITE);

    auto createFileOperation = std::make_unique<CreateFileOperation>(documents, "Resume.docx");
    createFileOperation->execute();

    // Use Proxy Pattern for Access Control
    auto user1Proxy = std::make_unique<FileSystemProxy>(documents, user1.get());
    user1Proxy->display("");

    // Version Control
    auto resume = dynamic_cast<File*>(documents->getChild("Resume.docx"));
    resume->writeContent("Version 1 of Resume");
    resume->writeContent("Version 2 of Resume");

    // Observer Pattern for Notifications
    auto subject = std::make_unique<Subject>();
    auto user2Observer = std::make_shared<UserObserver>("User2");
    subject->attach(user2Observer);
    subject->notifyObservers("Resume.docx has been updated.");

    // Search Functionality
    auto search = std::make_unique<FileSystemSearch>();
    if (auto found = search->search(root, "Resume.docx")) {
        std::cout << "Found: " << found->getName() << std::endl;
    } else {
        std::cout << "File not found." << std::endl;
    }

    // Storage Strategy
    fsManager.setStorageStrategy(std::make_unique<LocalStorageStrategy>());
    fsManager.getStorageStrategy()->saveFile(resume);

    return 0;
}