#include "FileOperation.hpp"
#include <iostream>

void FileOperation::execute() {
    if (validate()) {
        performOperation();
        logOperation();
    } else {
        std::cout << "Validation failed. Operation aborted." << std::endl;
    }
}

void FileOperation::logOperation() {
    std::cout << "Operation performed: " << typeid(*this).name() << std::endl;
} 