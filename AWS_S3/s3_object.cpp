#include "s3_object.hpp"

// S3Object implementation
S3Object::S3Object(const std::string& key, const std::vector<uint8_t>& data)
    : key_(key), data_(data) {}

std::string S3Object::getKey() const {
    return key_;
}

std::vector<uint8_t> S3Object::getData() const {
    return data_;
}

// S3ObjectDecorator implementation
S3ObjectDecorator::S3ObjectDecorator(std::shared_ptr<IS3Object> s3Object)
    : s3Object_(s3Object) {}

std::string S3ObjectDecorator::getKey() const {
    return s3Object_->getKey();
}

std::vector<uint8_t> S3ObjectDecorator::getData() const {
    return s3Object_->getData();
}

// VersionedObjectDecorator implementation
VersionedObjectDecorator::VersionedObjectDecorator(std::shared_ptr<IS3Object> s3Object)
    : S3ObjectDecorator(s3Object) {
    saveVersion();
}

void VersionedObjectDecorator::saveVersion() {
    currentVersion_++;
    versions_[currentVersion_] = s3Object_->getData();
}

std::vector<uint8_t> VersionedObjectDecorator::getVersionData(int version) const {
    auto it = versions_.find(version);
    if (it != versions_.end()) {
        return it->second;
    }
    return {};
}

int VersionedObjectDecorator::getCurrentVersion() const {
    return currentVersion_;
}

std::vector<uint8_t> VersionedObjectDecorator::getData() const {
    return versions_.at(currentVersion_);
}

// AccessControlledObjectDecorator implementation
AccessControlledObjectDecorator::AccessControlledObjectDecorator(std::shared_ptr<IS3Object> s3Object)
    : S3ObjectDecorator(s3Object) {}

void AccessControlledObjectDecorator::grantReadPermission(const std::string& userId) {
    readPermissions_.insert(userId);
}

void AccessControlledObjectDecorator::revokeReadPermission(const std::string& userId) {
    readPermissions_.erase(userId);
}

void AccessControlledObjectDecorator::grantWritePermission(const std::string& userId) {
    writePermissions_.insert(userId);
}

void AccessControlledObjectDecorator::revokeWritePermission(const std::string& userId) {
    writePermissions_.erase(userId);
}

bool AccessControlledObjectDecorator::hasReadPermission(const std::string& userId) const {
    return readPermissions_.find(userId) != readPermissions_.end();
}

bool AccessControlledObjectDecorator::hasWritePermission(const std::string& userId) const {
    return writePermissions_.find(userId) != writePermissions_.end();
} 