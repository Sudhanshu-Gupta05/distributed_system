#pragma once
#include "Folder.hpp"
#include "StorageStrategy.hpp"
#include <memory>

class FileSystemManager {
public:
    static FileSystemManager& getInstance();
    Folder* getRoot();
    void setStorageStrategy(std::unique_ptr<StorageStrategy> strategy);
    StorageStrategy* getStorageStrategy();

private:
    FileSystemManager();
    static FileSystemManager* instance;
    std::unique_ptr<Folder> root;
    std::unique_ptr<StorageStrategy> storageStrategy;
}; 