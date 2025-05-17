#include "LocalStorageStrategy.hpp"
#include <iostream>

void LocalStorageStrategy::saveFile(File* file) {
    std::cout << "Saving file locally: " << file->getName() << std::endl;
}

File* LocalStorageStrategy::loadFile(const std::string& fileName) {
    std::cout << "Loading file locally: " << fileName << std::endl;
    return new File(fileName);
} 