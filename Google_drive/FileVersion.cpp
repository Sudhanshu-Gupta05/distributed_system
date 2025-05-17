#include "FileVersion.hpp"

FileVersion::FileVersion(const std::string& content)
    : content(content), timestamp(std::chrono::system_clock::now()) {}

std::string FileVersion::getContent() const {
    return content;
}

std::chrono::system_clock::time_point FileVersion::getTimestamp() const {
    return timestamp;
} 