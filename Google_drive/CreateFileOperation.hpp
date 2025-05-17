#pragma once
#include "FileOperation.hpp"
#include "Folder.hpp"
#include <string>

class CreateFileOperation : public FileOperation {
public:
    CreateFileOperation(Folder* folder, const std::string& fileName);

protected:
    bool validate() override;
    void performOperation() override;

private:
    Folder* folder;
    std::string fileName;
}; 