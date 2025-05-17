#pragma once
#include "File.hpp"

class StorageStrategy {
public:
    virtual ~StorageStrategy() = default;
    virtual void saveFile(File* file) = 0;
    virtual File* loadFile(const std::string& fileName) = 0;
}; 