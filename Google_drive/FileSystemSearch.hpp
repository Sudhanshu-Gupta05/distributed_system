#pragma once
#include "FileSystemComponent.hpp"
#include <string>

class FileSystemSearch {
public:
    FileSystemComponent* search(FileSystemComponent* component, const std::string& name);
}; 