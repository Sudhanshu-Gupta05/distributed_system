#pragma once
#include "StorageStrategy.hpp"

class LocalStorageStrategy : public StorageStrategy {
public:
    void saveFile(File* file) override;
    File* loadFile(const std::string& fileName) override;
}; 