#include "CreateFileOperation.hpp"
#include "File.hpp"

CreateFileOperation::CreateFileOperation(Folder* folder, const std::string& fileName)
    : folder(folder), fileName(fileName) {}

bool CreateFileOperation::validate() {
    return folder->getChild(fileName) == nullptr;
}

void CreateFileOperation::performOperation() {
    folder->add(new File(fileName));
} 