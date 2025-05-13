#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

class IS3Object {
public:
    virtual ~IS3Object() = default;
    virtual std::string getKey() const = 0;
    virtual std::vector<uint8_t> getData() const = 0;
};

class S3Object : public IS3Object {
public:
    S3Object(const std::string& key, const std::vector<uint8_t>& data);
    std::string getKey() const override;
    std::vector<uint8_t> getData() const override;

private:
    std::string key_;
    std::vector<uint8_t> data_;
};

class S3ObjectDecorator : public IS3Object {
public:
    explicit S3ObjectDecorator(std::shared_ptr<IS3Object> s3Object);
    std::string getKey() const override;
    std::vector<uint8_t> getData() const override;

protected:
    std::shared_ptr<IS3Object> s3Object_;
};

class VersionedObjectDecorator : public S3ObjectDecorator {
public:
    explicit VersionedObjectDecorator(std::shared_ptr<IS3Object> s3Object);
    void saveVersion();
    std::vector<uint8_t> getVersionData(int version) const;
    int getCurrentVersion() const;
    std::vector<uint8_t> getData() const override;

private:
    std::unordered_map<int, std::vector<uint8_t>> versions_;
    int currentVersion_ = 0;
};

class AccessControlledObjectDecorator : public S3ObjectDecorator {
public:
    explicit AccessControlledObjectDecorator(std::shared_ptr<IS3Object> s3Object);
    void grantReadPermission(const std::string& userId);
    void revokeReadPermission(const std::string& userId);
    void grantWritePermission(const std::string& userId);
    void revokeWritePermission(const std::string& userId);
    bool hasReadPermission(const std::string& userId) const;
    bool hasWritePermission(const std::string& userId) const;

private:
    std::unordered_set<std::string> readPermissions_;
    std::unordered_set<std::string> writePermissions_;
}; 