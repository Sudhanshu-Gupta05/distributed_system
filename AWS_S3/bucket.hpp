#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "s3_object.hpp"

class User;

class Bucket {
public:
    Bucket(const std::string& name, const User& owner);
    const std::string& getName() const;
    const User& getOwner() const;
    void addObject(const std::string& key, const std::vector<uint8_t>& data);
    std::shared_ptr<IS3Object> getObject(const std::string& key) const;
    bool deleteObject(const std::string& key);
    std::vector<std::shared_ptr<IS3Object>> listObjects() const;

private:
    std::string name_;
    const User& owner_;
    std::unordered_map<std::string, std::shared_ptr<IS3Object>> objects_;
}; 