#include "FileSystemManager.hpp"
#include "LocalStorageStrategy.hpp"
#include <memory>

FileSystemManager* FileSystemManager::instance = nullptr;

FileSystemManager::FileSystemManager()
    : root(std::make_unique<Folder>("root")),
      storageStrategy(std::make_unique<LocalStorageStrategy>()) {}

FileSystemManager& FileSystemManager::getInstance() {
    if (instance == nullptr) {
        instance = new FileSystemManager();
    }
    return *instance;
}

Folder* FileSystemManager::getRoot() {
    return root.get();
}

void FileSystemManager::setStorageStrategy(std::unique_ptr<StorageStrategy> strategy) {
    storageStrategy = std::move(strategy);
}

StorageStrategy* FileSystemManager::getStorageStrategy() {
    return storageStrategy.get();
} 