#pragma once
#include <string>
#include <chrono>

class FileVersion {
public:
    explicit FileVersion(const std::string& content);
    std::string getContent() const;
    std::chrono::system_clock::time_point getTimestamp() const;

private:
    std::string content;
    std::chrono::system_clock::time_point timestamp;
}; 