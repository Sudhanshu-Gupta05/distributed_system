#pragma once
#include <iostream>

// Command Pattern
class FileOperation {
public:
    virtual ~FileOperation() = default;
    void execute();

protected:
    virtual bool validate() = 0;
    virtual void performOperation() = 0;
    virtual void logOperation();
}; 